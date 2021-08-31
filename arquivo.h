#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

struct GrafoMatrizAdj {
    int** arestas;
    char** rotuloVertices;
    int verticesInseridos;
    int maxNumVertices;
    //faz mais sentido ser apenas numVertices (consertar para a prox turma)
};

/**
 * Se o grafo for ponderado, inicializamos cada posicao da matriz com INT_MAX.
 * Se o grafo for não ponderado, inicializamos cada posicao da matriz com 0.
 **/
struct GrafoMatrizAdj* inicializar(int numVertices, bool ponderado) {
    GrafoMatrizAdj* grf = (struct GrafoMatrizAdj*)malloc(sizeof(struct GrafoMatrizAdj));
    grf->maxNumVertices = numVertices;
    grf->rotuloVertices = (char**)malloc(numVertices * sizeof(char*));
    grf->verticesInseridos = 0;
    grf->arestas = (int**)malloc(numVertices * sizeof(int*));
    
    if (ponderado == true) { 
        for (int i = 0; i < grf->maxNumVertices; i++) {
            for (int j = 0; j < grf->maxNumVertices; j++) {
                grf->arestas[i][j] = INT_MAX;
            }
        }
    }
    else {
        for (int i = 0; i < grf->maxNumVertices; i++) {
            for (int j = 0; j < grf->maxNumVertices; j++) {
                grf->arestas[i][j] = 0;
            }
        }
    }
    return grf;
}

/**
 * A principio nao temos nenhuma ordenacao usando os rotulos.
 * Portanto, usaremos busca linear
 **/
int obterIndiceVertice(struct GrafoMatrizAdj* grafo, char* rotuloVertice) {
    for (int i = 0; i < grafo->maxNumVertices; i++) {
        if (grafo->rotuloVertices[i] == rotuloVertice) {
            return i;
        }
        else {
            std::cout << "Não contém o Vertice " << rotuloVertice << " ";
            return -1;
        }
    }
}

/**
 * Se o grafo for ponderado, usamos a variavel peso para especificar o peso da aresta.
 * Se o grafo for não ponderado, passaremos o valor 1 para a variavel peso, de modo que represente existência da aresta.
 * Se um dos rotulos dos vertices nao existir, simplesmente nao faremos nada.
 **/
void inserirAresta(struct GrafoMatrizAdj* grafo, char* rotuloVOrigem, char* rotuloVDestino, int peso) {
    int Origem = obterIndiceVertice(grafo, rotuloVOrigem);
    int Destino = obterIndiceVertice(grafo, rotuloVDestino);
    
    if (Origem != -1 && Destino != -1) {
        grafo->arestas[Origem][Destino] = peso;
        grafo->arestas[Destino][Origem] = peso;
    }
    else {
        return;
    }
}

/**
 * Usamos a variavel grafo->verticesInseridos para controlar a quantidade de vertices que ja foi inserido no grafo.
 * Logo, ela pode/deve ser usada para especificar em qual posicao o vertice a ser inserido sera alocado.
 **/
void inserirVertice(struct GrafoMatrizAdj* grafo, char* rotuloVertice) {
    if(grafo->verticesInseridos < grafo->maxNumVertices){
       grafo->rotuloVertices[grafo->verticesInseridos] = rotuloVertice;
       grafo->verticesInseridos++;
    }
    else {
        return;
    }
}

/**
 * Tomar cuidado com as diferenças semânticas entre haver conexão entre dois vertices em um grafo ponderado,
 * e haver conexão entre dois vertices em um grafo nao-ponderado.
 **/
bool saoConectados(struct GrafoMatrizAdj* grafo, char* rotuloVOrigem, char* rotuloVDestino) {
    int Origem = obterIndiceVertice(grafo, rotuloVOrigem);
    int Destino = obterIndiceVertice(grafo, rotuloVDestino);
    
    if (Origem != -1 && Destino != -1) {
        return grafo->arestas[Origem][Destino];
    }
    else {
        return false;
    }
}
