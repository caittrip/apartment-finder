#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include "Apartment.h"


using MergeCompare = bool (*)(const Apartment&, const Apartment&);
void mergeSort(std::vector<Apartment>& apartments, MergeCompare comesBefore);

#endif //MERGESORT_H
