#include "hashing_estatico.hpp"
#include <fstream>
#include <iostream>

HashingEstatico::HashingEstatico(const std::string &arquivo, int qtd, int tam)
    : caminho_arquivo(arquivo), qtd_buckets(qtd), tamanho_bucket(tam) {}

int HashingEstatico::funcao_hash(int chave) {
    return chave % qtd_buckets;
}

void HashingEstatico::inserir(const Registro &r) {
    std::ofstream arq(caminho_arquivo, std::ios::binary | std::ios::app);
    if (!arq) { std::cerr << "Erro ao abrir arquivo de dados.\n"; return; }
    arq.write((char *)&r, sizeof(r));
}

Registro HashingEstatico::buscar(int chave) {
    std::ifstream arq(caminho_arquivo, std::ios::binary);
    Registro r;
    while (arq.read((char *)&r, sizeof(r))) {
        if (r.id == chave) return r;
    }
    throw std::runtime_error("Registro não encontrado.");
}
