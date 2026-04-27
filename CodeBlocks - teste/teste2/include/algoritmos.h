#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <vector>

// Algoritmos de Ordenação
void bubbleSort(std::vector<int>& arr, long long& comps, long long& swaps);
void insertionSort(std::vector<int>& arr, long long& comps, long long& swaps);
void selectionSort(std::vector<int>& arr, long long& comps, long long& swaps);
void shellSort(std::vector<int>& arr, long long& comps, long long& swaps);
void quickSort(std::vector<int>& arr, long long& comps, long long& swaps);
void mergeSort(std::vector<int>& arr, long long& comps, long long& swaps);
void radixSort(std::vector<int>& arr, long long& comps, long long& swaps);
void heapsort(std::vector<int>& arr, long long& comps, long long& swaps);

#endif // ALGORITMOS_H
