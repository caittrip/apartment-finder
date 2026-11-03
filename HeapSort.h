//
// Created by derek on 11/3/2026.
//

#ifndef APARTMENT_FINDER_HEAPSORT_H
#define APARTMENT_FINDER_HEAPSORT_H
#include "Apartment.h"
#include <vector>

using Compare = bool (*)(const Apartment&, const Apartment&);
void heapSort(std::vector<Apartment>& apartments, Compare comesBefore);
#endif //APARTMENT_FINDER_HEAPSORT_H
