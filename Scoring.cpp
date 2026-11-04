//
// Created by derek on 11/3/2026.
//
#include "Scoring.h"
#include <algorithm>

void scoreApartments(std::vector<Apartment>& apartments, const UserPreferences& prefs) {
    double totalWeight = prefs.affordabilityWeight + prefs.spaceWeight;
    for (Apartment& apt : apartments) {
        double affordability = 100.0 * (prefs.maxRent - apt.price) / prefs.maxRent;
        double space = 100.0 * std::min(static_cast<double>(apt.square_feet) / prefs.desiredSqft, 1.0);
        apt.score = (prefs.affordabilityWeight * affordability + prefs.spaceWeight * space) / totalWeight;
    }
}