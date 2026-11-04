#include "ApartmentLoader.h"
#include "Scoring.h"
#include "Filtering.h"
#include "HeapSort.h"
#include "MergeSort.h"
#include <vector>
#include <iostream>
using namespace std;

int main() {
    // Load the cleaned apartment data
    vector<Apartment> apartments = loadApartments("data/apartment_data.csv");
    cout << "Apartments loaded: " << apartments.size() << endl;

    // Filtering example, remove later
    FilterConditions conditions;
    conditions.maxRent = 3000;
    conditions.minBedrooms = 1;
    conditions.minBathrooms = 1;
    conditions.state = "FL";
    conditions.city = "Gainesville";

    vector<Apartment> filtered =
        filteringApartments(apartments, conditions);

    cout << "Apartments after Filtering: " << filtered.size() << endl;

    UserPreferences prefs;
    prefs.maxRent = 3000;
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