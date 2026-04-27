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

void merge(std::vector<int>& arr, int left, int mid, int right, std::vector<int>& temp, long long& comps, long long& swaps) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        comps++;
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
        swaps++;
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
        swaps++;
    }

    while (j <= right) {
        temp[k++] = arr[j++];
        swaps++;
    }

    for (int idx = left; idx <= right; ++idx) {
        arr[idx] = temp[idx];
        swaps++;
    }
}

void mergeSortHelper(std::vector<int>& arr, int left, int right, std::vector<int>& temp, long long& comps, long long& swaps) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSortHelper(arr, left, mid, temp, comps, swaps);
    mergeSortHelper(arr, mid + 1, right, temp, comps, swaps);
    merge(arr, left, mid, right, temp, comps, swaps);
}

void mergeSort(std::vector<int>& arr, long long& comps, long long& swaps) {
    if (arr.empty()) return;
    comps = 0;
    swaps = 0;

    std::vector<int> temp(arr.size());
    mergeSortHelper(arr, 0, static_cast<int>(arr.size()) - 1, temp, comps, swaps);
}

void radixSort(std::vector<int>& arr, long long& comps, long long& swaps) {
    if (arr.empty()) return;

    comps = 0;
    swaps = 0;

    int maxValue = *std::max_element(arr.begin(), arr.end());
    std::vector<int> output(arr.size());

    for (int exp = 1; maxValue / exp > 0; exp *= 10) {
        int count[10] = {0};

        for (int value : arr) {
            count[(value / exp) % 10]++;
            comps++;
        }

        for (int i = 1; i < 10; ++i) {
            count[i] += count[i - 1];
        }

        for (int i = static_cast<int>(arr.size()) - 1; i >= 0; --i) {
            int digit = (arr[i] / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
            swaps++;
        }

        for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
            arr[i] = output[i];
            swaps++;
        }
    }
}

// Função auxiliar para heapify (peneirar para baixo)
void heapify(std::vector<int>& arr, int n, int i, long long& comps, long long& swaps) {
    int largest = i;
    int left = 2 * i + 1;      // Filho esquerdo
    int right = 2 * i + 2;     // Filho direito

    // Comparar com filho esquerdo
    if (left < n) {
        comps++;
        if (arr[left] > arr[largest]) {
            largest = left;
        }
    }

    // Comparar com filho direito
    if (right < n) {
        comps++;
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }

    // Se o maior não é o nó atual, trocar e continuar heapificando
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        swaps++;
        heapify(arr, n, largest, comps, swaps);
    }
}

// Implementação do Heapsort
void heapsort(std::vector<int>& arr, long long& comps, long long& swaps) {
    if (arr.empty()) return;

    comps = 0;
    swaps = 0;

    int n = arr.size();

    // Fase 1: Construir o max heap (operação de heapify de baixo para cima)
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapify(arr, n, i, comps, swaps);
    }

    // Fase 2: Extrair elementos do heap um a um
    for (int i = n - 1; i > 0; i--) {
        // Mover a raiz (maior elemento) para o final
        std::swap(arr[0], arr[i]);
        swaps++;

        // Heapificar a raiz reduzida
        heapify(arr, i, 0, comps, swaps);
    }
}
