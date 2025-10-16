// upload.cpp
// Uso: ./bin/upload /data/input.csv
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include "util.hpp"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Uso: upload <arquivo.csv>\n";
        return 1;
    }
    string csv_path = argv[1];
    string db_dir = "/data/db";
    filesystem::create_directories(db_dir);

    string dados_path = db_dir + "/dados.csv";
    string idx_prim_path = db_dir + "/indice_primario.dat";
    string idx_sec_path = db_dir + "/indice_secundario.dat";

    cout << "[UPLOAD] CSV de entrada: " << csv_path << "\n";
    cout << "[UPLOAD] Arquivo de dados: " << dados_path << "\n";
    cout << "[UPLOAD] Indice primario: " << idx_prim_path << "\n";
    cout << "[UPLOAD] Indice secundario: " << idx_sec_path << "\n";

    ifstream fin(csv_path);
    if (!fin.is_open()) {
        cerr << "[ERRO] Não foi possível abrir o CSV de entrada.\n";
        return 2;
    }

    ofstream fout_dados(dados_path, ios::binary | ios::trunc);
    ofstream fout_idx_prim(idx_prim_path, ios::binary | ios::trunc);
    ofstream fout_idx_sec(idx_sec_path, ios::binary | ios::trunc);

    if (!fout_dados || !fout_idx_prim || !fout_idx_sec) {
        cerr << "[ERRO] Falha ao criar arquivos de saída.\n";
        return 3;
    }

    string linha;
    long total_reg = 0;
    auto t0 = chrono::high_resolution_clock::now();

    // lê CSV (assume que cada linha tem o registro completo; parser cuida de vírgulas/aspas)
    while (std::getline(fin, linha)) {
        if (linha.empty()) continue;
        auto campos = dividir_csv(linha);
        // simples validação
        if (campos.size() < 7) {
            // pula linhas incompletas
            continue;
        }
        Registro r = campos_para_registro(campos);
        string csvline = registro_para_csvline(r) + "\n";

        // offset antes de escrever
        long offset = fout_dados.tellp();
        fout_dados << csvline;
        fout_dados.flush();

        // índice primário: id (int32) + offset (int64)
        int32_t id32 = static_cast<int32_t>(r.id);
        int64_t off64 = static_cast<int64_t>(offset);
        fout_idx_prim.write(reinterpret_cast<char*>(&id32), sizeof(id32));
        fout_idx_prim.write(reinterpret_cast<char*>(&off64), sizeof(off64));

        // índice secundário: title_len (int32) + title bytes + offset (int64)
        int32_t tlen = static_cast<int32_t>(r.titulo.size());
        fout_idx_sec.write(reinterpret_cast<char*>(&tlen), sizeof(tlen));
        fout_idx_sec.write(r.titulo.data(), tlen);
        fout_idx_sec.write(reinterpret_cast<char*>(&off64), sizeof(off64));

        total_reg++;
        if (total_reg % 100000 == 0) {
            cout << "[UPLOAD] Registros processados: " << total_reg << "\n";
        }
    }

    fin.close();
    fout_dados.close();
    fout_idx_prim.close();
    fout_idx_sec.close();

    auto t1 = chrono::high_resolution_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();

    cout << "[UPLOAD] Finalizado. Registros processados: " << total_reg << "\n";
    cout << "[UPLOAD] Tempo (ms): " << ms << "\n";
    cout << "[UPLOAD] Arquivos gravados em /data/db\n";
    return 0;
}
