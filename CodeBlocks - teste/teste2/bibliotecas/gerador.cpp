#include "../include/gerador.h"
#include <algorithm>
#include <random>
#include <numeric>

std::vector<int> gerarCrescente(int tamanho) {
    std::vector<int> v(tamanho);
    std::iota(v.begin(), v.end(), 1);
    return v;
}

std::vector<int> gerarDecrescente(int tamanho) {
    std::vector<int> v = gerarCrescente(tamanho);
    std::reverse(v.begin(), v.end());
    return v;
}

std::vector<int> gerarAleatorio(int tamanho) {
    std::vector<int> v = gerarCrescente(tamanho);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);
    return v;
}
