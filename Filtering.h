#ifndef FILTERING_H
#define FILTERING_H

#include "Apartment.h"
#include <vector>
#include <string>

struct FilterConditions {
    double maxRent;
    double minBedrooms;
    double minBathrooms;
    std::string state;
    std::string city;
};

std::vector<Apartment> filteringApartments(
    const std::vector<Apartment>& apartments,
    const FilterConditions& conditions
    );

#endif //FILTERING_H
