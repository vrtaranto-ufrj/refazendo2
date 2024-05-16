#include "GrafoMatriz.hpp"
#include "GrafoListaDupla.hpp"
#include "GrafoVetor.hpp"
#include <iostream>
#include <string>
#include <chrono>

int main(int argc, char* argv[]) {
    Grafo* grafo;
    std::string tipo = argv[2];
    
    if (tipo == "m") {
        grafo = new GrafoMatriz;
    }
    else if (tipo == "l") {
        grafo = new GrafoListaDupla;
    }
    else if (tipo == "v") {
        grafo = new GrafoVetor;
    }
    else {
        return 1;
    }
    
    
    std::string myString = argv[1];
    grafo->loadGrafoOMP("./grafos/grafo_" + myString + ".txt");
    std::cout << "Alocou a memoria\n";

    auto start = std::chrono::high_resolution_clock::now();
    
    std::cout << "distancia de 10 ate 20 = " << grafo->distancia(10, 20) << '\n';
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Tempo de execucao: " << duration.count() << " microseconds\n";

    //int a;
    //std::cin >> a;
    //delete grafo;
    return 0;
}
