# TP2 - Organização de Arquivos e Índices (C++)

# Voce pode baixar os dados para teste nesse link https://drive.google.com/file/d/1EVoP0d9Wwzj1O6eoFIkel9I3cpe43Gbv/view

## Como compilar localmente
make build

## Como rodar via Docker (recomendado)
# construir imagem
make docker-build

# preparar pasta de dados
mkdir -p data db

# colocar o CSV de entrada em data/artigo.csv

# executar upload
docker run --rm -v $(pwd)/data:/data tp2 ./bin/upload /data/artigo.csv

# Buscar registro por ID (modo sequencial)
make docker-run-findrec ID=123

# Buscar registro por ID (índice primário)
make docker-run-seek1 ID=123

# Buscar registro por título (índice secundário)
make docker-run-seek2 TITULO="Um Título Exato"


