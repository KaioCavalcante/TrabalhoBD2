#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>
#include "registro.hpp"

// CSV parsing robustinho (aspas, vírgulas internas)
std::vector<std::string> dividir_csv(const std::string &linha);

// Converte vetor de campos em Registro (assume ordem do enunciado)
Registro campos_para_registro(const std::vector<std::string> &campos);

// Serializa um Registro para linha CSV segura (usado ao escrever dados)
std::string registro_para_csvline(const Registro &r);

// Funções utilitárias de tempo / blocos
long bytes_para_blocos(long bytes, long tam_bloco = 4096);

#endif // UTIL_HPP
