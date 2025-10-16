CXX = g++
CXXFLAGS = g++ -O2 -std=c++17 -Iinclude src/*.cpp -o bin/upload
SRC = src
BIN = bin

.PHONY: all build docker-build clean

all: build

build:
	mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $(SRC)/upload.cpp -o $(BIN)/upload
	$(CXX) $(CXXFLAGS) $(SRC)/findrec.cpp -o $(BIN)/findrec
	$(CXX) $(CXXFLAGS) $(SRC)/seek1.cpp -o $(BIN)/seek1
	$(CXX) $(CXXFLAGS) $(SRC)/seek2.cpp -o $(BIN)/seek2
	@echo "Build concluído. Binários em $(BIN)/"

clean:
	rm -rf $(BIN)/*
	@echo "Limpo."

docker-build:
	docker build -t tp2 .

docker-run-upload:
	docker run --rm -v $(PWD)/data:/data tp2 ./bin/upload /data/input.csv

docker-run-findrec:
	docker run --rm -v $(PWD)/data:/data tp2 ./bin/findrec 123

docker-run-seek1:
	docker run --rm -v $(PWD)/data:/data tp2 ./bin/seek1 123

docker-run-seek2:
	docker run --rm -v $(PWD)/data:/data tp2 ./bin/seek2 "Um Título Exato"
