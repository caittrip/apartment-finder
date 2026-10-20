//
// Created by Caitlyn Tripician on 10/19/26.
//

#ifndef APARTMENT_FINDER_APARTMENT_H
#define APARTMENT_FINDER_APARTMENT_H

#include <string>

struct Apartment {
    std::string id;
    double price;
    double bedrooms;
    double bathrooms;
    int square_feet;
    std::string city;
    std::string state;
    double latitude;
    double longitude;
};
#endif //APARTMENT_FINDER_APARTMENT_H
