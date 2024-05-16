#pragma once

#include <string>
#include <vector>
#include <queue>
#include <inttypes.h>

class Grafo {
    public:
        virtual ~Grafo();
        void loadGrafo(const std::string& nomeArquivo, bool direcionado = false);
        void loadGrafoOMP(const std::string& nomeArquivo, bool direcionado = false);
	    uint32_t distancia(uint32_t origem, uint32_t destino);
    protected:
	    uint64_t numeroVertices = 0;
        virtual void finalizaCriacao() = 0;
        virtual void defineTamanho() = 0;
        virtual void adicionaAresta(uint32_t origem, uint32_t destino) = 0;
	    virtual void percorreVizinhos(uint32_t atual, std::vector<uint32_t>& altura, std::queue<uint32_t>& fila) = 0;
	  
};
