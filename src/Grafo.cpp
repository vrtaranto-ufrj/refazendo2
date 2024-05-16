#include "Grafo.hpp"

#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#include <sstream>

Grafo::~Grafo() {

}

void Grafo::loadGrafo(const std::string& nomeArquivo, bool direcionado) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        throw "Arquivo não pode ser aberto";
    }

    uint32_t origem, destino;

    // Ler primeiro a quantidade de vértices
    if (!(arquivo >> numeroVertices)) {
        throw "Arquivo inválido";
    }

    defineTamanho();

    // Ler todas as arestas diretamente do arquivo
    while (arquivo >> origem >> destino) {
        origem--; // Ajustar para índice baseado em zero
        destino--; // Ajustar para índice baseado em zero
        adicionaAresta(origem, destino);
        if (!direcionado) {
            adicionaAresta(destino, origem);
        }
    }

    arquivo.close();

    finalizaCriacao();
}


void Grafo::loadGrafoOMP(const std::string& nomeArquivo, bool direcionado) {
    std::ifstream arquivo(nomeArquivo);
    std::string conteudo((std::istreambuf_iterator<char>(arquivo)),
                         std::istreambuf_iterator<char>());
    arquivo.close();

    std::istringstream stream(conteudo);
    uint32_t origem, destino;
    std::vector<std::pair<uint32_t, uint32_t>> arestas;

    // Ler primeiro a quantidade de vértices
    if (!(stream >> numeroVertices)) {
        throw "Arquivo inválido";
    }

    defineTamanho();

    // Ler todas as arestas do buffer
    while (stream >> origem >> destino) {
        arestas.emplace_back(--origem, --destino);
    }

    // Processar as arestas em paralelo
    #pragma omp parallel for
    for (size_t i = 0; i < arestas.size(); ++i) {
        auto [o, d] = arestas[i];
        adicionaAresta(o, d);
        if (!direcionado) {
            adicionaAresta(d, o);
        }
    }

	finalizaCriacao();
}

uint32_t Grafo::distancia(uint32_t origem, uint32_t destino) {
	origem--;
	destino--;
	if (origem > numeroVertices || destino > numeroVertices) {
		return -1;
	}
	
	std::vector<uint32_t> altura(numeroVertices, 0);
	std::queue<uint32_t> fila;

	fila.push(origem);
	altura[origem] = 1;

	while(!fila.empty()) {
		uint32_t atual = fila.front();
		fila.pop();

		if (atual == destino) {
			return altura[atual] - 1;
		}
        
		percorreVizinhos(atual, altura, fila);
	}
	return -1;
}
