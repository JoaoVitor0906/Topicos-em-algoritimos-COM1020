#include "../include/algoritmos.h"
#include <algorithm>

void bubbleSort(std::vector<int>& arr, long long& comps, long long& swaps) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comps++;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swaps++;
            }
        }
    }
}

void insertionSort(std::vector<int>& arr, long long& comps, long long& swaps) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        comps++;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            swaps++;
            j--;
            if(j >= 0) comps++;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(std::vector<int>& arr, long long& comps, long long& swaps) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            comps++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(arr[i], arr[min_idx]);
            swaps++;
        }
    }
}

void shellSort(std::vector<int>& arr, long long& comps, long long& swaps) {
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;

            for (j = i; j >= gap; j -= gap) {
                comps++;
                if (arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    swaps++;
                } else {
                    break;
                }
            }
            arr[j] = temp;
        }
    }
}

// QuickSort com contagem de comparacoes e trocas
void quickSortHelper(std::vector<int>& arr, int low, int high, long long& comps, long long& swaps) {
    if (low < high) {
        // Escolhe o pivô como o elemento do meio para evitar Stack Overflow em vetores já ordenados
        int mid = low + (high - low) / 2;
        std::swap(arr[mid], arr[high]);
        swaps++;

        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            comps++;
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
                swaps++;
            }
        }
        std::swap(arr[i + 1], arr[high]);
        swaps++;
        
        int pi = i + 1;
        quickSortHelper(arr, low, pi - 1, comps, swaps);
        quickSortHelper(arr, pi + 1, high, comps, swaps);
    }
}

void quickSort(std::vector<int>& arr, long long& comps, long long& swaps) {
    if (arr.empty()) return;
    comps = 0;
    swaps = 0;
    quickSortHelper(arr, 0, arr.size() - 1, comps, swaps);
}
