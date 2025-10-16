#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include <string>

struct Registro {
    int id;
    std::string titulo;
    int ano;
    std::string autores;
    int citacoes;
    std::string data_atualizacao;
    std::string snippet;
};

#endif 
