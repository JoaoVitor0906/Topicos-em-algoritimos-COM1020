#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <string>
#include <functional>
#include <vector>
#include "tipos.h"

// Funções de Benchmark
std::string obterNomeOrdem(TipoOrdem tipo);
void imprimirSeparador();
void imprimirCabecalho();
void imprimirMaquina();
void executarBenchmark(std::string nomeAlgoritmo, 
                       std::function<void(std::vector<int>&, long long&, long long&)> algoritmo, 
                       int tamanho, 
                       TipoOrdem ordem);

#endif // BENCHMARK_H
