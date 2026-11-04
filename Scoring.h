//
// Created by derek on 11/3/2026.
//

#ifndef APARTMENT_FINDER_SCORING_H
#define APARTMENT_FINDER_SCORING_H
#include "Apartment.h"
#include <vector>
struct UserPreferences {
    double maxRent;
    int desiredSqft;
    int affordabilityWeight;
    int spaceWeight;
};

void scoreApartments(std::vector<Apartment>& apartments, const UserPreferences& prefs);
#endif //APARTMENT_FINDER_SCORING_H
