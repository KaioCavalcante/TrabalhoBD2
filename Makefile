CXX = g++
CXXFLAGS = -O2 -std=c++17 -Iinclude
SRC = src
BIN = bin

.PHONY: all build clean docker-build docker-run-upload docker-run-findrec docker-run-seek1 docker-run-seek2

all: build

build: upload findrec seek1 seek2

$(BIN):
	mkdir -p $(BIN)

upload: $(BIN) $(SRC)/upload.cpp $(SRC)/registro.cpp $(SRC)/util.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN)/upload $(SRC)/upload.cpp $(SRC)/registro.cpp $(SRC)/util.cpp

findrec: $(BIN) $(SRC)/findrec.cpp $(SRC)/registro.cpp $(SRC)/util.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN)/findrec $(SRC)/findrec.cpp $(SRC)/registro.cpp $(SRC)/util.cpp

seek1: $(BIN) $(SRC)/seek1.cpp $(SRC)/registro.cpp $(SRC)/util.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN)/seek1 $(SRC)/seek1.cpp $(SRC)/registro.cpp $(SRC)/util.cpp

seek2: $(BIN) $(SRC)/seek2.cpp $(SRC)/registro.cpp $(SRC)/util.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN)/seek2 $(SRC)/seek2.cpp $(SRC)/registro.cpp $(SRC)/util.cpp

clean:
	rm -rf $(BIN)/*

docker-build:
	docker build -t tp2 .

docker-run-upload:
	docker run --rm -v $(PWD)/data:/data tp2 ./bin/upload /data/artigo.csv

docker-run-findrec:
	docker run --rm -v $(PWD)/data:/data tp2 ./bin/findrec $(ID)

docker-run-seek1:
	docker run --rm -v $(PWD)/data:/data tp2 ./bin/seek1 $(ID)

docker-run-seek2:
	docker run --rm -v $(PWD)/data:/data tp2 ./bin/seek2 "$(TITULO)"
