#pragma once

#include "Grafo.hpp"

class GrafoMatriz : public Grafo {
    public:
        bool posicao(uint32_t x, uint32_t y);
	    std::vector<uint8_t> matriz;
    private:
        virtual void finalizaCriacao();
        virtual void defineTamanho();
        virtual void adicionaAresta(uint32_t origem, uint32_t destino);
	    virtual void percorreVizinhos(uint32_t atual, std::vector<uint32_t>& altura, std::queue<uint32_t>& fila);        
};
