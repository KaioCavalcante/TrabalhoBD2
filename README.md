# TP2 - Organização de Arquivos e Índices (C++)

# Voce pode baixar os dados para teste nesse link https://drive.google.com/file/d/1EVoP0d9Wwzj1O6eoFIkel9I3cpe43Gbv/view

# preparar pasta de dados
mkdir -p data/db

# colocar o CSV de entrada em data/artigo.csv

## Como compilar localmente
make build

# Isso criará os executáveis em bin/:
upload
findrec
seek1
seek2

## Como rodar via Docker (recomendado)
# construir imagem
make docker-build

# executar upload
docker run --rm -v $(pwd)/data:/data tp2 ./bin/upload /data/artigo.csv

# Buscar registro por ID (modo sequencial)
make docker-run-findrec ID=123

# Buscar registro por ID (índice primário)
make docker-run-seek1 ID=123

# Buscar registro por título (índice secundário)
make docker-run-seek2 TITULO="Um Título Exato"

# Layout dos arquivos gerados em /data/db 

# Após o upload, são criados três arquivos:

# Contém todos os registros completos em formato CSV normalizado.
dados.csv

# Índice binário que associa id → offset no arquivo de dados.
indice_primario.dat

# Índice binário que associa titulo → offset no arquivo de dados.
indice_secundario.dat

# Exemplo de execução

# Upload
docker run --rm -v $(pwd)/data:/data tp2 ./bin/upload /data/artigo.csv

# Saída esperada:
[UPLOAD] CSV de entrada: /data/artigo.csv \
[UPLOAD] Arquivo de dados: /data/db/dados.csv \
[UPLOAD] Indice primario: /data/db/indice_primario.dat \
[UPLOAD] Indice secundario: /data/db/indice_secundario.dat \
[UPLOAD] Cabeçalho detectado: "1";"Poster: 3D sketching and flexible input for surface design..." \
[UPLOAD] Registros processados: 100000 \
[UPLOAD] Registros processados: 200000 \
... \
[UPLOAD] Finalizado. Registros processados: 1021438 \
[UPLOAD] Tempo (ms): 24751 \
[UPLOAD] Arquivos gravados em /data/db


# Busca por ID (sequencial)
make docker-run-findrec ID=123

# Saída esperada:
[RESULTADO] Registro encontrado (busca direta): \
ID: 123 \
Titulo: Spatially-multiplexed MIMO markers. \
Ano: 2015 \
Autores: Hideaki Uchiyama|Shinichiro Haruyama|Atsushi Shimada|Hajime Nagahara|Rin-ichiro Taniguchi \
Citacoes: 0 \
Atualizacao: 2016-07-28 09:36:59 \
Snippet: Spatially-multiplexed MIMO markers. H Uchiyama, S Haruyama, A Shimada - 3D User Interfaces, 2015 - ieeexplore.ieee.org. \
[ESTATÍSTICA] Blocos lidos (datafile): 18 \
[ESTATÍSTICA] Blocos totais (datafile): 131778


# Buscar registro por ID (índice primário)
make docker-run-seek1 ID=36

# Saída esperada:
[RESULTADO] Registro encontrado via indice primario: \
ID: 36 \
Titulo: An evaluation of two simple methods for representing heaviness in immersive virtual environments. \
Ano: 2013 \
Autores: Johannes Hummel|Janki Dodiya|Robin Wolff|Andreas Gerndt|Torsten Kuhlen \
Citacoes: 5 \
Atualizacao: 2016-10-03 20:57:09 \
Snippet: An evaluation of two simple methods for representing heaviness in immersive virtual environments. J Hummel, J Dodiya, R Wolff, A Gerndt - 3D User Interfaces, 2013 - ieeexplore.ieee.org. ABSTRACT ... \
[ESTATÍSTICA] Blocos lidos (indice primario): 1 \
[ESTATÍSTICA] Blocos totais (indice primario): 2993 \
[ESTATÍSTICA] Blocos lidos (datafile) aprox.: 1



# Busca por título (índice secundário)
make docker-run-seek2 TITULO="Spatially-multiplexed MIMO markers."

# Saída esperada:
[RESULTADO] Registro encontrado via indice secundario (titulo): \
ID: 123 \
Titulo: Spatially-multiplexed MIMO markers. \
Ano: 2015 \
Autores: Hideaki Uchiyama|Shinichiro Haruyama|Atsushi Shimada|Hajime Nagahara|Rin-ichiro Taniguchi \
Citacoes: 0 \
Atualizacao: 2016-07-28 09:36:59 \
Snippet: Spatially-multiplexed MIMO markers. H Uchiyama, S Haruyama, A Shimada - 3D User Interfaces, 2015 - ieeexplore.ieee.org. \
[ESTATÍSTICA] Blocos lidos (indice secundario): 3 \
[ESTATÍSTICA] Blocos totais (indice secundario): 21183


# Documentação do trabalho
[Baixar documentação (PDF)] (TP2_Documentacao.pdf)


