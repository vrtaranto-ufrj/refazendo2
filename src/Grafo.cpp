#include "Grafo.hpp"

#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#include <sstream>
#include <string>
#include <omp.h>
#include <limits>

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
    std::ifstream arquivo(nomeArquivo, std::ios::binary | std::ios::ate);
    if (!arquivo.is_open()) {
        throw "Não foi possível abrir o arquivo";
    }

    // Obter o tamanho do arquivo
    std::streamsize tamanhoArquivo = arquivo.tellg();
    arquivo.seekg(0, std::ios::beg);

    // Ler a primeira linha para obter o número de vértices
    arquivo >> numeroVertices;

    defineTamanho();

    // Saltar a linha de número de vértices
    arquivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Obter a posição atual (início das arestas)
    std::streamsize posInicioArestas = arquivo.tellg();

    // Ler o arquivo inteiro em um buffer
    std::vector<char> buffer(tamanhoArquivo - posInicioArestas);
    arquivo.read(buffer.data(), tamanhoArquivo - posInicioArestas);
    arquivo.close();

    // Dividir o trabalho entre os threads
    int numThreads = omp_get_max_threads();
    std::vector<std::vector<std::pair<uint32_t, uint32_t>>> threadArestas(numThreads);

    #pragma omp parallel
    {
        int threadId = omp_get_thread_num();
        std::istringstream localStream(std::string(buffer.data(), buffer.size()));
        
        // Calcular a posição de início e fim para cada thread
        std::streamsize chunkSize = buffer.size() / numThreads;
        std::streamsize posInicio = threadId * chunkSize;
        std::streamsize posFim = (threadId == numThreads - 1) ? buffer.size() : (threadId + 1) * chunkSize;

        // Ajustar a posição de início para o começo da próxima linha, se não for o primeiro thread
        if (threadId != 0) {
            localStream.seekg(posInicio);
            std::string linha;
            std::getline(localStream, linha);
            posInicio = localStream.tellg();
        }

        // Ajustar a posição de fim para o final da linha, se não for o último thread
        if (threadId != numThreads - 1) {
            localStream.seekg(posFim);
            std::string linha;
            std::getline(localStream, linha);
            posFim = localStream.tellg();
        }

        // Processar o trecho do buffer
        localStream.seekg(posInicio);
        uint32_t origem, destino;
        while (localStream.tellg() < posFim && localStream >> origem >> destino) {
            threadArestas[threadId].emplace_back(--origem, --destino);
            // Ignorar o resto da linha (caso haja algo além dos dois inteiros)
            localStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // Combinar as arestas processadas por todas as threads
    std::vector<std::pair<uint32_t, uint32_t>> arestas;
    for (const auto& tArestas : threadArestas) {
        arestas.insert(arestas.end(), tArestas.begin(), tArestas.end());
    }

    // Adicionar as arestas ao grafo
    #pragma omp parallel for
    for (size_t i = 0; i < arestas.size(); ++i) {
        std::pair<uint32_t, uint32_t> a = arestas[i];
        adicionaAresta(a.first, a.second);
        if (!direcionado) {
            adicionaAresta(a.second, a.first);
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
