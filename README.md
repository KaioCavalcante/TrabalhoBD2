# TP2 - Organização de Arquivos e Índices (C++)

## Como compilar localmente
make build

## Como rodar via Docker (recomendado)
# construir imagem
make docker-build

# preparar pasta de dados
mkdir -p data db
# colocar o CSV de entrada em data/input.csv

# executar upload
docker run --rm -v $(pwd)/data:/data tp2 ./bin/upload /data/input.csv

# procurar registros
docker run --rm -v $(pwd)/data:/data tp2 ./bin/findrec 123
docker run --rm -v $(pwd)/data:/data tp2 ./bin/seek1 123
docker run --rm -v $(pwd)/data:/data tp2 "./bin/seek2 Título Exato"

## Local (sem Docker)
./bin/upload data/input.csv
./bin/findrec 123
./bin/seek1 123
./bin/seek2 "Título Exato"
