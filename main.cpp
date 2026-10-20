#include "ApartmentLoader.h"
#include <vector>
#include <iostream>
using namespace std;

int main() {
    // Load the cleaned apartment data
    vector<Apartment> apartments = loadApartments("data/apartment_data.csv");
    cout << "Apartments loaded: " << apartments.size() << endl;
}