#include "MergeSort.h"

using namespace std;

void merge(vector<Apartment>& apartments,
    int left, int middle, int right,
    MergeCompare comesBefore) {
    vector<Apartment> temp;

    int i = left;
    int j = middle + 1;

    while (i <= middle && j <= right) {
        if (comesBefore(apartments[i], apartments[j])) {
            temp.push_back(apartments[i]);
            i++;
        }
        else {
            temp.push_back(apartments[j]);
            j++;
        }
    }
    while (i <= middle) {
        temp.push_back(apartments[i]);
        i++;
    }
    while (j <= right) {
        temp.push_back(apartments[j]);
        j++;
    }
    for (int k = 0; k < temp.size(); k++) {
        apartments[left + k] = temp[k];
    }
}

void mergeHelper(vector<Apartment>& apartments,
    int left, int right,
    MergeCompare comesBefore) {

    if (left >= right) {
        return;
    }

    int middle = left + (right - left) / 2;

    mergeHelper(apartments, left, middle, comesBefore);
    mergeHelper(apartments, middle + 1, right, comesBefore);
    merge(apartments, left, middle, right, comesBefore);
}

void mergeSort(vector<Apartment>& apartments,
    MergeCompare comesBefore) {

    if (apartments.empty()) {
        return;
    }

    mergeHelper(apartments, 0, apartments.size() - 1, comesBefore);
}
