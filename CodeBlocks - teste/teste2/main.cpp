#include <iostream>
#include <vector>
#include <cstdlib>
#include "include/algoritmos.h"
#include "include/benchmark.h"
#include "include/tipos.h"

using namespace std;

int main() {
    vector<int> tamanhos = {500, 1000, 2000, 5000, 10000, 20000};
    vector<TipoOrdem> ordens = {DECRESCENTE, CRESCENTE, ALEATORIA};

    imprimirMaquina();
    imprimirCabecalho();

    for (int tamanho : tamanhos) {
        for (TipoOrdem ordem : ordens) {
            executarBenchmark("BubbleSort", bubbleSort, tamanho, ordem);
            executarBenchmark("SelectionSort", selectionSort, tamanho, ordem);
            executarBenchmark("InsertionSort", insertionSort, tamanho, ordem);
            executarBenchmark("ShellSort", shellSort, tamanho, ordem);
            executarBenchmark("QuickSort", quickSort, tamanho, ordem);
            executarBenchmark("MergeSort", mergeSort, tamanho, ordem);
            executarBenchmark("RadixSort", radixSort, tamanho, ordem);
        }
        imprimirSeparador();
    }

    system("pause");
    return 0;
}
