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

int main() {
    // Load the cleaned apartment data
    vector<Apartment> apartments = loadApartments("data/apartment_data.csv");
    cout << "Apartments loaded: " << apartments.size() << endl;

    FilterConditions conditions;


    // Leaving either answer blank skips that location filter.
    cout << "Enter a state abbreviation (e.g., FL, or press Enter for any state): ";
    getline(cin, conditions.state);

    cout << "Enter a city (or press Enter for any city): ";
    getline(cin, conditions.city);

    while (true) {
        cout << "Enter your maximum monthly rent: ";

        string answer;
        if (!getline(cin, answer)) {
            return 0;
        }

        istringstream input(answer);
        double rent;
        char extra;

        if (input >> rent && isfinite(rent) && rent > 0 && !(input >> extra)) {
            conditions.maxRent = rent;
            break;
        }

        cout << "Please enter a positive amount like 1500 or 1500.50.\n";
    }
    
    int minBedrooms;
    if (!readNonnegative("Enter minimum bedrooms (whole number): ", minBedrooms)) {
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
        return 0;
    }

    scoreApartments(filtered, prefs);

    //heapSort(filtered, ranksBefore);
    mergeSort(filtered, ranksBefore);

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
        cout << "\nEnter n for next, p for previous, d for details, or q to quit: ";
        string choice;
        if (!getline(cin, choice) || choice == "q") {
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
                break;
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
                 << "Match score: " << apt.score << "/100\n";

            cout << "\nPress Enter to return to the results.";
            string answer;
            if (!getline(cin, answer)) {
                break;
            }
                } else if (choice == "d") {
            int listingNumber;
            if (!readIntInRange("Enter a listing number from this page: ",
                                listingNumber,
                                static_cast<int>(pageStart + 1),
                                static_cast<int>(pageEnd))) {
                break;
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
                 << "Match score: " << apt.score << "/100\n";

            cout << "\nPress Enter to return to the results.";
            string answer;
            if (!getline(cin, answer)) {
                break;
            }
            } else if (choice == "d") {
            int listingNumber;
            if (!readIntInRange("Enter a listing number from this page: ",
                                listingNumber,
                                static_cast<int>(pageStart + 1),
                                static_cast<int>(pageEnd))) {
                break;
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
                 << "Match score: " << apt.score << "/100\n";

            cout << "\nPress Enter to return to the results.";
            string answer;
            if (!getline(cin, answer)) {
                break;
            }
        } else {
            cout << "That option is unavailable on this page.\n";
        }
    }

    return 0;
}