#pragma once

#include "Grafo.hpp"
#include <list>
#include <vector>


class GrafoListaDupla : public Grafo {
    private:
        std::vector<std::list<uint32_t>> lista;

        virtual void finalizaCriacao();        
        virtual void defineTamanho();
        virtual void adicionaAresta(uint32_t origem, uint32_t destino);
	    virtual void percorreVizinhos(uint32_t atual, std::vector<uint32_t>& altura, std::queue<uint32_t>& fila);
};