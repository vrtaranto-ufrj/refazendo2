#include "GrafoListaDupla.hpp"

void GrafoListaDupla::finalizaCriacao() {

}

void GrafoListaDupla::defineTamanho() {
    lista.resize(numeroVertices);
}

void GrafoListaDupla::adicionaAresta(uint32_t origem, uint32_t destino) {
    lista[origem].push_front(destino);
}

void GrafoListaDupla::percorreVizinhos(uint32_t atual, std::vector<uint32_t>& altura, std::queue<uint32_t>& fila) {
    for (auto& vizinho : lista[atual]) {
        if (!altura[vizinho]) {
            altura[vizinho] = altura[atual] + 1;
            fila.push(vizinho);
        }
    }
}