#include "GrafoMatriz.hpp"
#include <iostream>
#include <omp.h>

void GrafoMatriz::finalizaCriacao() {

}

void GrafoMatriz::defineTamanho() {
    std::cout << "numVertice: " << numeroVertices << '\n';
    uint64_t tamMatriz = numeroVertices*numeroVertices;
    u_int64_t tamRealMatriz = tamMatriz/8 + ((tamMatriz % 8) ? 1 : 0);
    std::cout << "Matriz irá ocupar: " << tamRealMatriz << "B, " << tamRealMatriz/1024/1024 << "MB" << '\n';
    matriz.resize(tamRealMatriz);
    std::cout << "era pra ser: " << tamMatriz << ", virou size: " << matriz.size() << '\n';
    
}

void GrafoMatriz::adicionaAresta(uint32_t origem, uint32_t destino) {
    uint64_t pos = origem + numeroVertices*destino;
    matriz[pos / 8] |= (1 << (pos % 8));
    
}

bool GrafoMatriz::posicao(uint32_t x, uint32_t y) {
    uint64_t pos = x + numeroVertices*y;
    return matriz[pos / 8] & (1 << (pos % 8));
}

void GrafoMatriz::percorreVizinhos(uint32_t atual, std::vector<uint32_t>& altura, std::queue<uint32_t>& fila) {
	#pragma omp parallel for
	for (uint32_t vizinho = 0; vizinho < numeroVertices; vizinho++) {
		if (!altura[vizinho] && posicao(atual, vizinho)) {
			altura[vizinho] = altura[atual] + 1;
			#pragma omp critical
			fila.push(vizinho);
		}
	}
}
