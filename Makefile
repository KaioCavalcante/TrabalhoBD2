CXX = g++
CXXFLAGS = -O2 -std=c++17 -Iinclude
SRC = src
BIN = bin

all: build

build: upload findrec seek1 seek2

# cria bin se não existir antes de compilar
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
