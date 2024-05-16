#include "GrafoVetor.hpp"

void GrafoVetor::finalizaCriacao() {
    for (uint32_t i = 0; i < numeroVertices; i++) {
        vetor[i].assign(listaAuxiliar[i].begin(), listaAuxiliar[i].end());
    }
    listaAuxiliar.clear();
}

void GrafoVetor::defineTamanho() {
    listaAuxiliar.resize(numeroVertices);
    vetor.resize(numeroVertices);
}

void GrafoVetor::adicionaAresta(uint32_t origem, uint32_t destino) {
    listaAuxiliar[origem].push_front(destino);
}

void GrafoVetor::percorreVizinhos(uint32_t atual, std::vector<uint32_t>& altura, std::queue<uint32_t>& fila) {
    for (auto& vizinho : vetor[atual]) {
        if (!altura[vizinho]) {
            altura[vizinho] = altura[atual] + 1;
            fila.push(vizinho);
        }
    }
}