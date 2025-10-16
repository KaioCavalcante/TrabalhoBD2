// seek2.cpp
// Uso: ./bin/seek2 "Titulo Exato"
// Procura no índice secundário (titulo->offset)
#include <iostream>
#include <fstream>
#include <string>
#include "util.hpp"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Uso: seek2 <Titulo exato>\n";
        return 1;
    }
    string titulo_busca = argv[1];
    // se título contiver espaços/aspas ao chamar do shell, passe entre aspas

    string dados_path = "/data/db/dados.csv";
    string idx_sec = "/data/db/indice_secundario.dat";

    ifstream fidx(idx_sec, ios::binary);
    if (!fidx.is_open()) {
        cerr << "[ERRO] Não foi possível abrir índice secundário: " << idx_sec << "\n";
        return 2;
    }

    const long bloco = 4096;
    long idx_bytes_lidos = 0;
    bool achou = false;
    int32_t tlen;
    int64_t off64;

    while (fidx.read(reinterpret_cast<char*>(&tlen), sizeof(tlen))) {
        if (tlen < 0 || tlen > 10*1024*1024) break; // proteção
        string titulo(tlen, '\0');
        fidx.read(&titulo[0], tlen);
        fidx.read(reinterpret_cast<char*>(&off64), sizeof(off64));
        idx_bytes_lidos += sizeof(tlen) + tlen + sizeof(off64);

        if (titulo == titulo_busca) {
            achou = true;
            break;
        }
    }

    fidx.clear();
    fidx.seekg(0, ios::end);
    long idx_total_bytes = fidx.tellg();
    long idx_blocos_lidos = bytes_para_blocos(idx_bytes_lidos, bloco);
    long idx_blocos_total = bytes_para_blocos(idx_total_bytes, bloco);

    if (!achou) {
        cout << "[RESULTADO] Título não encontrado no índice secundário: " << titulo_busca << "\n";
        cout << "[ESTATÍSTICA] Blocos lidos (indice secundario): " << idx_blocos_lidos << "\n";
        cout << "[ESTATÍSTICA] Blocos totais (indice secundario): " << idx_blocos_total << "\n";
        return 0;
    }

    ifstream fdados(dados_path, ios::binary);
    if (!fdados.is_open()) {
        cerr << "[ERRO] Não foi possível abrir dados: " << dados_path << "\n";
        return 3;
    }
    fdados.seekg(off64);
    string linha;
    getline(fdados, linha);
    auto campos = dividir_csv(linha);
    Registro r = campos_para_registro(campos);

    cout << "[RESULTADO] Registro encontrado via indice secundario (titulo):\n";
    cout << "ID: " << r.id << "\n";
    cout << "Titulo: " << r.titulo << "\n";
    cout << "Ano: " << r.ano << "\n";
    cout << "Autores: " << r.autores << "\n";
    cout << "Citacoes: " << r.citacoes << "\n";
    cout << "Atualizacao: " << r.data_atualizacao << "\n";
    cout << "Snippet: " << r.snippet << "\n";

    cout << "[ESTATÍSTICA] Blocos lidos (indice secundario): " << idx_blocos_lidos << "\n";
    cout << "[ESTATÍSTICA] Blocos totais (indice secundario): " << idx_blocos_total << "\n";

    return 0;
}
