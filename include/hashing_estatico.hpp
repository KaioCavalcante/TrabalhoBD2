#ifndef HASHING_ESTATICO_HPP
#define HASHING_ESTATICO_HPP

#include "registro.hpp"
#include <string>

class HashingEstatico {
private:
    int qtd_buckets;
    int tamanho_bucket;
    std::string caminho_arquivo;
public:
    HashingEstatico(const std::string &arquivo, int qtd, int tam);
    int funcao_hash(int chave);
    void inserir(const Registro &reg);
    Registro buscar(int chave);
};

#endif
