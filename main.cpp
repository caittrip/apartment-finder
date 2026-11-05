#include "ApartmentLoader.h"
#include "Scoring.h"
#include "Filtering.h"
#include "HeapSort.h"
#include "MergeSort.h"
#include <vector>
#include <iostream>
#include <chrono>
using namespace std;
//sorts a copy of data and returns time in ms
template <typename SortFunction>
double timeSort(vector<Apartment>& data, SortFunction sortFunction, bool (*comesBefore)(const Apartment&, const Apartment&)) {
    auto start = chrono::steady_clock::now();
    sortFunction(data, comesBefore);
    auto end = chrono::steady_clock::now();
    return chrono::duration<double, milli>(end-start).count();
}
bool sameOrder(const vector<Apartment>& a, const vector<Apartment>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i<a.size(); i++) {
        if (a[i].id != b[i].id) return false;
    }
    return true;
}
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

    vector<Apartment> heapResults = filtered;
    vector<Apartment> mergeResults = filtered;

    double heapTime = timeSort(heapResults, heapSort, ranksBefore);
    double mergeTime = timeSort(mergeResults, mergeSort, ranksBefore);

    cout <<"Heap sort time: " << heapTime << " ms\n";
    cout <<"Merge sort time: "<< mergeTime << " ms\n";
    cout <<"Results match: " << (sameOrder(heapResults, mergeResults) ? "Yes" : "No") << endl;

    filtered = heapResults;

    vector<Apartment> heapByRent = apartments;
    vector<Apartment> mergeByRent = apartments;

    double heapRentTime = timeSort(heapByRent, heapSort, rentBefore);
    double mergeRentTime = timeSort(mergeByRent, mergeSort, rentBefore);

    cout << "\nAll " << apartments.size() << " records by rent:\n";
    cout << "Heap sort time: " << heapRentTime << " ms\n";
    cout << "Merge sort time: " << mergeRentTime << " ms\n";
    cout << "Results match: " << (sameOrder(heapByRent, mergeByRent) ? "Yes" : "No") << endl;

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