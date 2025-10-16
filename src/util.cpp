#include "util.hpp"
#include <sstream>
#include <iomanip>

std::vector<std::string> dividir_csv(const std::string &linha) {
    std::vector<std::string> campos;
    std::string cur;
    bool in_quotes = false;
    for (size_t i = 0; i < linha.size(); ++i) {
        char c = linha[i];
        if (c == '"') {
            // se aspas duplas aparecendo duas vezes, é escapado -> incluir uma e pular
            if (in_quotes && i + 1 < linha.size() && linha[i+1] == '"') {
                cur.push_back('"');
                ++i;
            } else {
                in_quotes = !in_quotes;
            }
        } else if (c == ',' && !in_quotes) {
            campos.push_back(cur);
            cur.clear();
        } else {
            cur.push_back(c);
        }
    }
    campos.push_back(cur);
    return campos;
}

Registro campos_para_registro(const std::vector<std::string> &campos) {
    Registro r;
    // proteger se campos faltantes
    r.id = campos.size() > 0 && !campos[0].empty() ? std::stoi(campos[0]) : 0;
    r.titulo = campos.size() > 1 ? campos[1] : "";
    r.ano = campos.size() > 2 && !campos[2].empty() ? std::stoi(campos[2]) : 0;
    r.autores = campos.size() > 3 ? campos[3] : "";
    r.citacoes = campos.size() > 4 && !campos[4].empty() ? std::stoi(campos[4]) : 0;
    r.data_atualizacao = campos.size() > 5 ? campos[5] : "";
    r.snippet = campos.size() > 6 ? campos[6] : "";
    return r;
}

static std::string escape_csv_field(const std::string &s) {
    bool need_quotes = s.find_first_of(",\"\n") != std::string::npos;
    std::string out;
    if (need_quotes) out.push_back('"');
    for (char c : s) {
        if (c == '"') {
            out.push_back('"'); // escape
            out.push_back('"');
        } else {
            out.push_back(c);
        }
    }
    if (need_quotes) out.push_back('"');
    return out;
}

std::string registro_para_csvline(const Registro &r) {
    std::ostringstream ss;
    ss << r.id << ",";
    ss << escape_csv_field(r.titulo) << ",";
    ss << r.ano << ",";
    ss << escape_csv_field(r.autores) << ",";
    ss << r.citacoes << ",";
    ss << escape_csv_field(r.data_atualizacao) << ",";
    ss << escape_csv_field(r.snippet);
    return ss.str();
}

long bytes_para_blocos(long bytes, long tam_bloco) {
    if (bytes <= 0) return 0;
    return (bytes + tam_bloco - 1) / tam_bloco;
}
