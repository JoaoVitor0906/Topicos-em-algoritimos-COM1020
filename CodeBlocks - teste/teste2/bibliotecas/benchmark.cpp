#include "../include/benchmark.h"
#include "../include/gerador.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>

using namespace std;
using namespace std::chrono;

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

void imprimirCabecalho() {
    imprimirSeparador();
    cout << left << setw(16) << "Algoritmo"
         << right << setw(10) << "Tamanho"
         << right << setw(15) << "Ordem"
         << right << setw(14) << "Tempo (ms)"
         << right << setw(16) << "Comparacoes"
         << right << setw(16) << "Trocas"
         << right << setw(18) << "Total Operacoes" << "\n";
    imprimirSeparador();
}

void imprimirMaquina() {
    cout << "========================================================\n";
    cout << "CARACTERISTICAS DA MAQUINA:\n";
    cout << "-> CPU: Intel(R) Core(TM) i5-14500T (1.70 GHz)\n";
    cout << "-> RAM: 16GB\n";
    cout << "-> SO:  Windows 11\n";
    cout << "========================================================\n\n";
}

void executarBenchmark(string nomeAlgoritmo, 
                       function<void(vector<int>&, long long&, long long&)> algoritmo, 
                       int tamanho, 
                       TipoOrdem ordem) {
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
