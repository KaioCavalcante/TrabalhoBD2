#ifndef ARVORE_BMAIS_HPP
#define ARVORE_BMAIS_HPP

#include <string>
#include <vector>

struct NoBMais {
    bool folha;
    std::vector<int> chaves;
    std::vector<long> ponteiros;
};

class ArvoreBMais {
private:
    std::string caminho_arquivo;
    int ordem;
public:
    ArvoreBMais(const std::string &arquivo, int ordem);
    void inserir(int chave, long posicao);
    long buscar(int chave);
};

#endif