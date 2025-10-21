// seek1.cpp
// Uso: ./bin/seek1 <ID>
// Procura no indice primario (arquivo de pares id->offset), conta blocos lidos no indice e depois lê datafile por offset.
#include <iostream>
#include <fstream>
#include <string>
#include "util.hpp"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Uso: seek1 <ID>\n";
        return 1;
    }
    int id_busca = stoi(argv[1]);
    string dados_path = "/data/db/dados.csv";
    string idx_prim = "/data/db/indice_primario.dat";

    ifstream fidx(idx_prim, ios::binary);
    if (!fidx.is_open()) {
        cerr << "[ERRO] Não foi possível abrir índice primário: " << idx_prim << "\n";
        return 2;
    }

    const long bloco = 4096;
    long idx_bytes_lidos = 0;
    bool achou = false;
    int32_t id32;
    int64_t off64 = -1;

    while (fidx.read(reinterpret_cast<char*>(&id32), sizeof(id32))) {
        fidx.read(reinterpret_cast<char*>(&off64), sizeof(off64));
        idx_bytes_lidos += sizeof(id32) + sizeof(off64);
        if (id32 == id_busca) {
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
        cout << "[RESULTADO] Chave nao encontrada no indice primario: " << id_busca << "\n";
        cout << "[ESTATÍSTICA] Blocos lidos (indice primario): " << idx_blocos_lidos << "\n";
        cout << "[ESTATÍSTICA] Blocos totais (indice primario): " << idx_blocos_total << "\n";
        return 0;
    }

    // Lê do arquivo de dados por offset
    ifstream fdados(dados_path, ios::binary);
    if (!fdados.is_open()) {
        cerr << "[ERRO] Não foi possível abrir dados: " << dados_path << "\n";
        return 3;
    }
    fdados.seekg(off64);
    string linha;
    std::getline(fdados, linha); // linha do registro
    auto campos = dividir_csv(linha);
    Registro r = campos_para_registro(campos);

    // calcular blocos lidos no datafile: assumimos que lemos até a linha (off64 + linha.size())
    long linha_tamanho_tentativa = 0;
    long data_bytes_lidos = 0;
    // Aproximação: lemos 1 bloco se offset dentro de 1 bloco e eventualmente mais dependendo do tamanho da linha.
    long bytes_ate_offset = off64;
    long linha_bytes = linha.size() + 1;
    long data_bl_lidos = bytes_para_blocos(bytes_ate_offset + linha_bytes, bloco) - bytes_para_blocos(bytes_ate_offset, bloco);
    if (data_bl_lidos <= 0) data_bl_lidos = 1;

    cout << "[RESULTADO] Registro encontrado via indice primario:\n";
    cout << "ID: " << r.id << "\n";
    cout << "Titulo: " << r.titulo << "\n";
    cout << "Ano: " << r.ano << "\n";
    cout << "Autores: " << r.autores << "\n";
    cout << "Citacoes: " << r.citacoes << "\n";
    cout << "Atualizacao: " << r.data_atualizacao << "\n";
    cout << "Snippet: " << r.snippet << "\n";

    cout << "[ESTATÍSTICA] Blocos lidos (indice primario): " << idx_blocos_lidos << "\n";
    cout << "[ESTATÍSTICA] Blocos totais (indice primario): " << idx_blocos_total << "\n";
    cout << "[ESTATÍSTICA] Blocos lidos (datafile) aprox.: " << data_bl_lidos << "\n";

    return 0;
}
