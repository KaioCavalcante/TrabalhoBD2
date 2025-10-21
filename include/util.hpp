#pragma once
#include <string>
#include <vector>

struct Registro {
    int id;
    std::string titulo;
    int ano;
    std::string autores;
    int citacoes;
    std::string data_atualizacao;
    std::string snippet;
};

std::vector<std::string> dividir_csv(const std::string &linha);
Registro campos_para_registro(const std::vector<std::string> &campos);
std::string registro_para_csvline(const Registro &r);
long bytes_para_blocos(long bytes, long tam_bloco);
