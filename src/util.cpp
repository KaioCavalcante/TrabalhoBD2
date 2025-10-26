#include "util.hpp"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <limits>

std::vector<std::string> dividir_csv(const std::string &linha_inicial, std::istream *stream_restante) {
    std::string linha = linha_inicial;
    bool entre_aspas = false;
    auto conta_aspas = [](const std::string &s) {
        int count = 0;
        for (char c : s) if (c == '"') count++;
        return count;
    };
    int aspas_abertas = conta_aspas(linha) % 2;
    while (aspas_abertas && stream_restante && !stream_restante->eof()) {
        std::string extra;
        std::getline(*stream_restante, extra);
        linha += '\n' + extra;
        aspas_abertas = conta_aspas(linha) % 2;
    }
    std::vector<std::string> campos;
    std::string atual;
    entre_aspas = false;
    for (size_t i = 0; i < linha.size(); ++i) {
        char c = linha[i];

        if (c == '"') {
            if (entre_aspas && i + 1 < linha.size() && linha[i + 1] == '"') {
                atual.push_back('"');
                ++i;
            } else {
                entre_aspas = !entre_aspas;
            }
        } else if (c == ';' && !entre_aspas) {
            campos.push_back(atual);
            atual.clear();
        } else {
            atual.push_back(c);
        }
    }

    campos.push_back(atual);
    return campos;
}

Registro campos_para_registro(const std::vector<std::string> &campos) {
    Registro r;
    r.id = campos.size() > 0 ? safe_stoi(campos[0], 0) : 0;
    r.titulo = campos.size() > 1 ? campos[1] : "";
    r.ano = campos.size() > 2 ? safe_stoi(campos[2], 0) : 0;
    r.autores = campos.size() > 3 ? campos[3] : "";
    r.citacoes = campos.size() > 4 ? safe_stoi(campos[4], 0) : 0;
    r.data_atualizacao = campos.size() > 5 ? campos[5] : "";
    r.snippet = campos.size() > 6 ? campos[6] : "";
    return r;
}

std::string registro_para_csvline(const Registro &r) {
    std::ostringstream ss;
    auto escape = [](const std::string &s){
        bool aspas = s.find_first_of(";\n\"") != std::string::npos;
        std::string out;
        if (aspas) out.push_back('"');
        for(char c : s){
            if(c=='"'){ out += "\"\""; } else { out += c; }
        }
        if (aspas) out.push_back('"');
        return out;
    };
    ss << r.id << ";"
       << escape(r.titulo) << ";"
       << r.ano << ";"
       << escape(r.autores) << ";"
       << r.citacoes << ";"
       << escape(r.data_atualizacao) << ";"
       << escape(r.snippet);
    return ss.str();
}

long bytes_para_blocos(long bytes, long tam_bloco) {
    if (bytes <= 0) return 0;
    return (bytes + tam_bloco - 1) / tam_bloco;
}
