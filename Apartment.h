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
    double score = 0;
};
inline bool ranksBefore(const Apartment &a, const Apartment &b) {
    if (a.score != b.score) {
        return a.score > b.score;
    }
    return a.id < b.id;
}
inline bool rentBefore(const Apartment &a, const Apartment &b) {
    if (a.price != b.price) {
        return a.price < b.price;
    }
    return a.id < b.id;
}
#endif //APARTMENT_FINDER_APARTMENT_H
