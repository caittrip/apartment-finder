//
// Created by derek on 11/3/2026.
//
#include "HeapSort.h"
#include <utility>
static void siftDown(std::vector<Apartment> &a, int parent, int heapSize, Compare comesBefore) {
    while (true) {
        int left = 2*parent + 1;
        int right = left + 1;
        int worst = parent;
        if (left < heapSize && comesBefore(a[worst], a[left])) worst = left;
        if ( right < heapSize && comesBefore(a[worst], a[right])) worst = right;
        if (worst == parent) return;

        std::swap(a[parent], a[worst]);
        parent = worst;
    }
}

void heapSort(std::vector<Apartment>& a, Compare comesBefore) {
    int n = static_cast<int>(a.size());
    for (int i = n/2 -1; i>=0; i--) {
        siftDown(a, i, n, comesBefore);
    }
    for (int end = n-1; end > 0; end--) {
        std::swap(a[0], a[end]);
        siftDown(a, 0, end, comesBefore);
    }
}