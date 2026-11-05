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
using namespace std;


int main() {
    // Load the cleaned apartment data
    vector<Apartment> apartments = loadApartments("data/apartment_data.csv");
    cout << "Apartments loaded: " << apartments.size() << endl;

    FilterConditions conditions;
    conditions.minBedrooms = 1;
    conditions.minBathrooms = 1;

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

    vector<Apartment> filtered =
        filteringApartments(apartments, conditions);

    cout << "Apartments after Filtering: " << filtered.size() << endl;

    UserPreferences prefs;
    prefs.maxRent = conditions.maxRent;
    prefs.desiredSqft = 1000;
    prefs.affordabilityWeight = 50;
    prefs.spaceWeight = 50;

    scoreApartments(filtered, prefs);

    //heapSort(filtered, ranksBefore);
    mergeSort(filtered, ranksBefore);

    for (int i = 0; i < 10 && i < filtered.size(); i++) {
        cout << "ID: " << filtered[i].id
        << " | Rent: $" << filtered[i].price
        << " | Bedrooms: " << filtered[i].bedrooms
        << " | Bathrooms: " << filtered[i].bathrooms
        << " | Address: " << filtered[i].address
        << " | City: " << filtered[i].city
        << " | State: " << filtered[i].state
        << " | Square Feet: " << filtered[i].square_feet
        << " | Score: " << filtered[i].score << endl;
    }

    return 0;
}