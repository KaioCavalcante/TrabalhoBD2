#pragma once
#include <string>
#include <vector>
#include <istream>
#include <cctype>
#include <limits>

struct Registro {
    int id;
    std::string titulo;
    int ano;
    std::string autores;
    int citacoes;
    std::string data_atualizacao;
    std::string snippet;
};

std::vector<std::string> dividir_csv(const std::string &linha_inicial, std::istream *stream_restante = nullptr);
Registro campos_para_registro(const std::vector<std::string> &campos);
std::string registro_para_csvline(const Registro &r);
long bytes_para_blocos(long bytes, long tam_bloco);

inline int safe_stoi(const std::string &s, int default_value = 0) {
    if (s.empty()) return default_value;
    size_t i = 0;
    while (i < s.size() && std::isspace(s[i])) i++;
    if (i == s.size()) return default_value;
    bool negative = false;
    if (s[i] == '+' || s[i] == '-') {
        negative = (s[i] == '-');
        i++;
    }
    if (i == s.size() || !std::isdigit(s[i])) return default_value;
    long long result = 0;
    for (; i < s.size(); i++) {
        if (!std::isdigit(s[i])) break;
        int digit = s[i] - '0';
        result = result * 10 + digit;
        if (!negative && result > std::numeric_limits<int>::max()) return default_value;
        if (negative && -result < std::numeric_limits<int>::min()) return default_value;
    }

    return negative ? -static_cast<int>(result) : static_cast<int>(result);
}
