#pragma once

#include "Grafo.hpp"
#include <list>

class GrafoVetor : public Grafo {
    private:
        std::vector<std::vector<uint32_t>> vetor;
        std::vector<std::list<uint32_t>> listaAuxiliar;

        virtual void finalizaCriacao();
        virtual void defineTamanho();
        virtual void adicionaAresta(uint32_t origem, uint32_t destino);
	    virtual void percorreVizinhos(uint32_t atual, std::vector<uint32_t>& altura, std::queue<uint32_t>& fila);
};