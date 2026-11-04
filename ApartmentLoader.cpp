#include "ApartmentLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

// Splits one line of the CSV into different fields
vector<string> getDataLine(const string &line) {
    vector<string> fields;
    string field;
    stringstream ss(line);

    while (getline(ss, field, ',')) {
        fields.push_back(field);
    }
    return fields;
}

// Loads apartments and fields from CSV file
vector<Apartment> loadApartments(const string &fileName) {
    vector<Apartment> apartments;
    ifstream file(fileName);
    string line;

    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return apartments;
    }

    getline(file, line); // Skips headers

    while (getline(file, line)) {
        vector<string> fields = getDataLine(line);

        // 10 columns are expected
        if (fields.size() != 10) {
            continue;
        }
        Apartment apartment;

        // Maps each column name in the CSV to a different field
        apartment.id = fields[0];
        apartment.price = stod(fields[1]);
        apartment.bedrooms = stod(fields[2]);
        apartment.bathrooms = stod(fields[3]);
        apartment.square_feet = stoi(fields[4]);
        apartment.address = fields[5];
        apartment.city = fields[6];
        apartment.state = fields[7];
        apartment.latitude = stod(fields[8]);
        apartment.longitude = stod(fields[9]);
        apartment.address.erase(remove(apartment.address.begin(), apartment.address.end(), '"'), apartment.address.end());
        apartment.city.erase(remove(apartment.city.begin(), apartment.city.end(), '"'), apartment.city.end());
        apartment.state.erase(remove(apartment.state.begin(), apartment.state.end(), '"'), apartment.state.end());


        apartments.push_back(apartment);
    }

    file.close();

    return apartments;
}
