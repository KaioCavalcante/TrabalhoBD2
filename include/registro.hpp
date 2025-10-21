#ifndef REGISTRO_HPP
#define REGISTRO_HPP
#include <vector>
#include <string>

struct Registro {
    int id;
    std::string titulo;
    int ano;
    std::string autores;
    int citacoes;
    std::string data_atualizacao;
    std::string snippet;
    std::vector<char> serializar() const;
    static Registro desserializar_from_buffer(const char* buf, size_t size);
};

#endif 
