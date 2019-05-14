#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector> 
#include <fstream> 
#include <string>         

#include "list.h"

using namespace std; 

namespace graph {

typedef string Label;
typedef int Weight;

struct AdjNode {
  VertexNode* p;
  Weight weight;
  AdjNode* next;
};

typedef AdjNode* AdjList;

struct VertexNode {
  Label label;
  AdjList adjList;
  bool visited;
  VertexNode* next;
};

typedef VertexNode* Graph; // un grafo e' identificato dal puntatore al primo vertice inserito

const AdjList noAdjNode = nullptr;
const Graph noVertexNode = nullptr;
const int invalidPath = -1;

// createEmptyGraph restituisce il grafo vuoto 
Graph createEmptyGraph();

// Aggiunge nuovo vertice con etichetta la stringa. Fallisce se gia' presente
bool addVertex(Label, Graph&);

// Cerca e restituisce il vertice corrispondente a label
VertexNode* getVertex (Label, Graph&);

// Aggiunge nuovo arco tra i due nodi con etichette le due stringe e peso
// l'intero. Fallisce se non sono presenti tutti e due i nodi o se l'arco
// tra i due e' gia' presente.
bool addEdge(Label, Label, Weight, Graph&);

// Restituisce true se il grafo e' vuoto, false altrimenti
bool isEmpty(const Graph&);

// Ritorna il numero di vertici del grafo
int numVertices(const Graph&);

// Ritorna il numero di archi del grafo
int numEdges(const Graph&);

// Calcola e ritorna (nel secondo parametro) il grado del nodo.
// Fallisce se il nodo non esiste
bool nodeDegree(Label, int&, const Graph&);

// Verifica se due vertici sono adiacenti (ovvero se esiste un arco)
bool areAdjacent(Label, Label, const Graph&); 

// Ritorna la lista di adiacenza di un vertice
list::List adjacentList(Label, Graph&);

// Calcola, se esiste, un cammino tra due vertici
void findPath(Label, Label, list::List &, int &, const Graph& g);
}


/* Funzioni che non caratterizzano il TDD Graph, ma che servono per input/output */
//tree::Tree readFromFile(string);
void printGraph(const graph::Graph&);
