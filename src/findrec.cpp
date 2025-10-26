#include <iostream>
#include <fstream>
#include <string>
#include "util.hpp"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Uso: findrec <ID>\n";
        return 1;
    }
    int id_busca = stoi(argv[1]);
    string dados_path = "/data/db/dados.csv";

    ifstream fin(dados_path, ios::binary);
    if (!fin.is_open()) {
        cerr << "[ERRO] Não foi possível abrir " << dados_path << "\n";
        return 2;
    }

    const long bloco = 4096;
    long bytes_lidos = 0;
    string linha;
    bool achou = false;
    Registro r;

    while (std::getline(fin, linha)) {
        bytes_lidos += linha.size() + 1;
        auto campos = dividir_csv(linha);
        if (campos.size() >= 1) {
            int id = campos[0].empty() ? 0 : stoi(campos[0]);
            if (id == id_busca) {
                r = campos_para_registro(campos);
                achou = true;
                break;
            }
        }
    }

    fin.clear();
    fin.seekg(0, ios::end);
    long total_bytes = fin.tellg();
    long blocos_lidos = bytes_para_blocos(bytes_lidos, bloco);
    long blocos_total = bytes_para_blocos(total_bytes, bloco);

    if (!achou) {
        cout << "[RESULTADO] Registro não encontrado para ID=" << id_busca << "\n";
    } else {
        cout << "[RESULTADO] Registro encontrado (busca direta):\n";
        cout << "ID: " << r.id << "\n";
        cout << "Titulo: " << r.titulo << "\n";
        cout << "Ano: " << r.ano << "\n";
        cout << "Autores: " << r.autores << "\n";
        cout << "Citacoes: " << r.citacoes << "\n";
        cout << "Atualizacao: " << r.data_atualizacao << "\n";
        cout << "Snippet: " << r.snippet << "\n";
    }

    cout << "[ESTATÍSTICA] Blocos lidos (datafile): " << blocos_lidos << "\n";
    cout << "[ESTATÍSTICA] Blocos totais (datafile): " << blocos_total << "\n";
    return 0;
}
