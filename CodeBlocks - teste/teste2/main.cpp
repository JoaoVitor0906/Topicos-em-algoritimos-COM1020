#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <functional>

using namespace std;
using namespace std::chrono;

// 1. ALGORITMOS DE ORDENAÇÃO

void bubbleSort(vector<int>& arr, long long& comps, long long& swaps) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comps++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swaps++;
            }
        }
    }
}

void insertionSort(vector<int>& arr, long long& comps, long long& swaps) {
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

void selectionSort(vector<int>& arr, long long& comps, long long& swaps) {
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
            swap(arr[i], arr[min_idx]);
            swaps++;
        }
    }
}

void shellSort(vector<int>& arr, long long& comps, long long& swaps) {
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

// 2. FUNÇÕES GERADORAS

vector<int> gerarCrescente(int tamanho) {
    vector<int> v(tamanho);
    iota(v.begin(), v.end(), 1);
    return v;
}

vector<int> gerarDecrescente(int tamanho) {
    vector<int> v = gerarCrescente(tamanho);
    reverse(v.begin(), v.end());
    return v;
}

vector<int> gerarAleatorio(int tamanho) {
    vector<int> v = gerarCrescente(tamanho);
    random_device rd;
    mt19937 g(rd());
    shuffle(v.begin(), v.end(), g);
    return v;
}

// 3. ESTRUTURA DE BENCHMARKING (TABELA)

enum TipoOrdem { CRESCENTE, DECRESCENTE, ALEATORIA };

string obterNomeOrdem(TipoOrdem tipo) {
    switch(tipo) {
        case CRESCENTE: return "Crescente";
        case DECRESCENTE: return "Decrescente";
        case ALEATORIA: return "Aleatoria";
    }
    return "";
}

void imprimirSeparador() {
    cout << string(105, '-') << "\n";
}

void executarBenchmark(string nomeAlgoritmo, function<void(vector<int>&, long long&, long long&)> algoritmo, int tamanho, TipoOrdem ordem) {
    long long totalComps = 0, totalSwaps = 0;
    double totalTempoMs = 0.0;
    int numRodadas = 3;

    for (int rodada = 0; rodada < numRodadas; ++rodada) {
        vector<int> vetor;
        if (ordem == CRESCENTE) vetor = gerarCrescente(tamanho);
        else if (ordem == DECRESCENTE) vetor = gerarDecrescente(tamanho);
        else if (ordem == ALEATORIA) vetor = gerarAleatorio(tamanho);

        long long comps = 0, swaps = 0;

        auto start = high_resolution_clock::now();
        algoritmo(vetor, comps, swaps);
        auto end = high_resolution_clock::now();

        duration<double, milli> tempoExecucao = end - start;

        totalComps += comps;
        totalSwaps += swaps;
        totalTempoMs += tempoExecucao.count();
    }

    long long mediaComps = totalComps / numRodadas;
    long long mediaSwaps = totalSwaps / numRodadas;
    long long totalOperacoes = mediaComps + mediaSwaps;
    double mediaTempoMs = totalTempoMs / numRodadas;

    cout << left << setw(16) << nomeAlgoritmo
         << right << setw(10) << tamanho
         << right << setw(15) << obterNomeOrdem(ordem)
         << right << setw(14) << fixed << setprecision(3) << mediaTempoMs
         << right << setw(16) << mediaComps
         << right << setw(16) << mediaSwaps
         << right << setw(18) << totalOperacoes << "\n";
}

// 4. FUNÇÃO PRINCIPAL

int main() {
    vector<int> tamanhos = {500, 1000, 2000, 5000, 10000, 20000};
    vector<TipoOrdem> ordens = {DECRESCENTE, CRESCENTE, ALEATORIA};

    cout << "========================================================\n";
    cout << "CARACTERISTICAS DA MAQUINA:\n";
    cout << "-> CPU: Intel(R) Core(TM) i5-14500T (1.70 GHz)\n";
    cout << "-> RAM: 16GB\n";
    cout << "-> SO:  Windows 11\n";
    cout << "========================================================\n\n";

    imprimirSeparador();
    cout << left << setw(16) << "Algoritmo"
         << right << setw(10) << "Tamanho"
         << right << setw(15) << "Ordem"
         << right << setw(14) << "Tempo (ms)"
         << right << setw(16) << "Comparacoes"
         << right << setw(16) << "Trocas"
         << right << setw(18) << "Total Operacoes" << "\n";
    imprimirSeparador();

    for (int tamanho : tamanhos) {
        for (TipoOrdem ordem : ordens) {
            executarBenchmark("BubbleSort", bubbleSort, tamanho, ordem);
            executarBenchmark("SelectionSort", selectionSort, tamanho, ordem);
            executarBenchmark("InsertionSort", insertionSort, tamanho, ordem);
            executarBenchmark("ShellSort", shellSort, tamanho, ordem);
        }
        imprimirSeparador(); // Separa os blocos por tamanho de vetor
    }

    return 0;
}
