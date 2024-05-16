#include "GrafoMatriz.hpp"
#include "GrafoListaDupla.hpp"
#include "GrafoVetor.hpp"
#include <iostream>
#include <string>

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
    grafo->loadGrafo("./grafos/grafo_" + myString + ".txt");
    std::cout << "Alocou a memoria\n";

    std::cout << "distancia de 10 ate 20 = " << grafo->distancia(10, 20) << '\n';

    //int a;
    //std::cin >> a;
    //delete grafo;
    return 0;
}
