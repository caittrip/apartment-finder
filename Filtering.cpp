#include "Filtering.h"

using namespace std;

vector<Apartment> filteringApartments(
    const vector<Apartment>& apartments,
    const FilterConditions& conditions) {

    vector<Apartment> filtered;

    for (const Apartment& apt : apartments) {

        //Max rent
        if (apt.price > conditions.maxRent) {
            continue;
        }

        //Min Bedrooms
        if (apt.bedrooms < conditions.minBedrooms) {
            continue;
        }

        //Min Bathrooms
        if (apt.bathrooms < conditions.minBathrooms) {
            continue;
        }

        //State
        if (!conditions.state.empty() && apt.state != conditions.state) {
            continue;
        }

        //City
        if (!conditions.city.empty() && apt.city != conditions.city) {
            continue;
        }

        filtered.push_back(apt);

    }
    return filtered;
}
