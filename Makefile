ARQUIVOS = main.cpp Grafo.cpp GrafoMatriz.cpp GrafoListaDupla.cpp GrafoVetor.cpp
OBJETOS = $(ARQUIVOS:.cpp=.o)
SAIDA = programa

DIRSRC = src
DIRBIN = bin
DIROBJ = obj
DIRGRAFOS = grafos

CC = g++
CFLAGS = -Wall -O3

all: $(SAIDA)

$(SAIDA): $(addprefix $(DIROBJ)/, $(OBJETOS))
	$(CC) $(CFLAGS) -o $(DIRBIN)/$@ $^

$(DIROBJ)/%.o: $(DIRSRC)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

omp: CFLAGS += -fopenmp
omp: $(SAIDA)

run: $(SAIDA)
	./$(DIRBIN)/$(SAIDA) $(DIRGRAFOS)/$(GRAFO)

clean:
	rm -f $(DIROBJ)/*.o $(DIRBIN)/$(SAIDA)
