#include "ApartmentLoader.h"
#include "Scoring.h"
#include "Filtering.h"
#include "HeapSort.h"
#include "MergeSort.h"
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <limits>
#include <chrono>
using namespace std;

template <typename Number>
bool readNonnegative(const string& prompt, Number& value) {
    while (true) {
        cout << prompt;
        string answer;
        if (!getline(cin, answer)) {
            return false;
        }
        istringstream input(answer);
        Number number;
        char extra;
        if ((input >> number) && isfinite(number) && number >= 0
            && !(input >> extra)) {
            value = number;
            return true;
        }
        cout << "Please enter a valid number of 0 or more.\n";
    }
}

bool readIntInRange(const string& prompt, int& value, int minimum, int maximum) {
    while (readNonnegative(prompt, value)) {
        if (value >= minimum && value <= maximum) {
            return true;
        }

        cout << "Please enter a whole number from "
             << minimum << " to " << maximum << ".\n";
    }

    return false;
}

//sorts data and returns time in ms
template <typename SortFunction>
double timeSort(vector<Apartment>& data, SortFunction sortFunction,
                bool (*comesBefore)(const Apartment&, const Apartment&)) {
    auto start = chrono::steady_clock::now();
    sortFunction(data, comesBefore);
    auto end = chrono::steady_clock::now();
    return chrono::duration<double, milli>(end - start).count();
}

bool sameOrder(const vector<Apartment>& a, const vector<Apartment>& b) {
    if (a.size() != b.size()) {
        return false;
    }

    for (size_t i = 0; i < a.size(); i++) {
        if (a[i].id != b[i].id) {
            return false;
        }
    }

    return true;
}

int main() {
    //load the cleaned apartment data
    vector<Apartment> apartments = loadApartments("data/apartment_data.csv");
    cout << "Apartments loaded: " << apartments.size() << endl;

    while (true) {
        FilterConditions conditions;

        //leaving either answer blank skips that location filter
        cout << "Enter a state abbreviation (e.g., FL, or press Enter for any state): ";
        if (!getline(cin, conditions.state)) {
            return 0;
        }

        cout << "Enter a city (or press Enter for any city): ";
        if (!getline(cin, conditions.city)) {
            return 0;
        }

        while (true) {
            cout << "Enter your maximum monthly rent: ";

            string answer;
            if (!getline(cin, answer)) {
                return 0;
            }

            istringstream input(answer);
            double rent;
            char extra;

            if ((input >> rent) && isfinite(rent) && rent > 0
                && !(input >> extra)) {
                conditions.maxRent = rent;
                break;
            }

            cout << "Please enter a positive amount like 1500 or 1500.50.\n";
        }

        int minBedrooms;
        if (!readNonnegative("Enter minimum bedrooms (whole number): ",
                             minBedrooms)) {
            return 0;
        }
        conditions.minBedrooms = minBedrooms;

        if (!readNonnegative("Enter minimum bathrooms (e.g., 1.5): ",
                             conditions.minBathrooms)) {
            return 0;
        }

        vector<Apartment> filtered =
            filteringApartments(apartments, conditions);
        cout << "Apartments after Filtering: " << filtered.size() << endl;

        UserPreferences prefs;
        prefs.maxRent = conditions.maxRent;

        if (!readIntInRange("Enter desired square footage: ", prefs.desiredSqft,
                            1, numeric_limits<int>::max())) {
            return 0;
        }
        if (!readIntInRange("How important is affordability (1-5)? ",
                            prefs.affordabilityWeight, 1, 5)) {
            return 0;
        }
        if (!readIntInRange("How important is space (1-5)? ",
                            prefs.spaceWeight, 1, 5)) {
            return 0;
        }

        if (filtered.empty()) {
            cout << "\nNo apartments matched your search. "
                 << "Try a higher budget or fewer filters.\n";
            cout << "Enter r to search again, or press Enter to quit: ";

            string choice;
            if (getline(cin, choice) && choice == "r") {
                continue;
            }

            return 0;
        }

        scoreApartments(filtered, prefs);

        vector<Apartment> heapResults = filtered;
        vector<Apartment> mergeResults = filtered;

        double heapTime = timeSort(heapResults, heapSort, ranksBefore);
        double mergeTime = timeSort(mergeResults, mergeSort, ranksBefore);

        cout << "Heap sort time: " << heapTime << " ms\n";
        cout << "Merge sort time: " << mergeTime << " ms\n";
        cout << "Results match: "
             << (sameOrder(heapResults, mergeResults) ? "Yes" : "No")
             << endl;

        filtered = heapResults;

        vector<Apartment> heapByRent = apartments;
        vector<Apartment> mergeByRent = apartments;

        double heapRentTime = timeSort(heapByRent, heapSort, rentBefore);
        double mergeRentTime = timeSort(mergeByRent, mergeSort, rentBefore);

        cout << "\nAll " << apartments.size() << " records by rent:\n";
        cout << "Heap sort time: " << heapRentTime << " ms\n";
        cout << "Merge sort time: " << mergeRentTime << " ms\n";
        cout << "Results match: "
             << (sameOrder(heapByRent, mergeByRent) ? "Yes" : "No")
             << endl;

        const size_t pageSize = 10;
        size_t pageStart = 0;

        while (true) {
            size_t pageEnd = pageStart + pageSize;
            if (pageEnd > filtered.size()) {
                pageEnd = filtered.size();
            }

            cout << "\nShowing matches " << pageStart + 1 << " to " << pageEnd
                 << " of " << filtered.size() << "\n";

            for (size_t i = pageStart; i < pageEnd; i++) {
                const Apartment& apt = filtered[i];
                cout << i + 1
                     << " | Rent: $" << apt.price
                     << " | Bedrooms: " << apt.bedrooms
                     << " | Bathrooms: " << apt.bathrooms
                     << " | City: " << apt.city
                     << " | State: " << apt.state
                     << " | Square Feet: " << apt.square_feet
                     << " | Score: " << apt.score << '\n';
            }

            cout << "\nEnter n for next, p for previous, d for details, "
                 << "r for a new search, or q to quit: ";

            string choice;

            // Exit if input closes or the user chooses q.
            if (!getline(cin, choice) || choice == "q") {
                return 0;
            }

            // Leave the results loop to start a new search.
            if (choice == "r") {
                break;
            }

            if (choice == "n" && pageEnd < filtered.size()) {
                pageStart += pageSize;
            } else if (choice == "p" && pageStart > 0) {
                pageStart -= pageSize;
            } else if (choice == "d") {
                int listingNumber;
                if (!readIntInRange("Enter a listing number from this page: ",
                                    listingNumber,
                                    static_cast<int>(pageStart + 1),
                                    static_cast<int>(pageEnd))) {
                    return 0;
                }

                const Apartment& apt = filtered[listingNumber - 1];

                cout << "\nListing #" << listingNumber << '\n'
                     << "Listing ID: " << apt.id << '\n'
                     << "Location: " << apt.city << ", " << apt.state << '\n'
                     << "Address: "
                     << (apt.address.empty() || apt.address == "NA"
                             ? "Unavailable" : apt.address)
                     << '\n'
                     << "Monthly rent: $" << apt.price << '\n'
                     << "Bedrooms: " << apt.bedrooms << '\n'
                     << "Bathrooms: " << apt.bathrooms << '\n'
                     << "Square feet: " << apt.square_feet << '\n'
                     << "Match score: " << apt.score << "/100\n";

                cout << "\nPress Enter to return to the results.";

                string answer;
                if (!getline(cin, answer)) {
                    return 0;
                }
            } else {
                cout << "That option is unavailable on this page.\n";
            }
        } //results loop
    } // search loop

    return 0;
}