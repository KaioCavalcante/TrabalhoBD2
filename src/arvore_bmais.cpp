#include "arvore_bmais.hpp"
#include <fstream>
#include <iostream>

ArvoreBMais::ArvoreBMais(const std::string &arquivo, int o) : caminho_arquivo(arquivo), ordem(o) {
    std::ofstream arq(caminho_arquivo, std::ios::binary | std::ios::trunc);
}

void ArvoreBMais::inserir(int chave, long posicao) {
    std::ofstream arq(caminho_arquivo, std::ios::binary | std::ios::app);
    arq.write((char*)&chave, sizeof(chave));
    arq.write((char*)&posicao, sizeof(posicao));
}

long ArvoreBMais::buscar(int chave) {
    std::ifstream arq(caminho_arquivo, std::ios::binary);
    int c; long pos;
    while (arq.read((char*)&c, sizeof(c))) {
        arq.read((char*)&pos, sizeof(pos));
        if (c == chave) return pos;
    }
    return -1;
}
