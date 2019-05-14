#include "graph.h"

using namespace graph;


/*******************************************************************************************************/
// Grafo
/*******************************************************************************************************/

// Restituisce il grafo vuoto
Graph graph::createEmptyGraph() {
  return noVertexNode;
}

// Aggiunge nuovo vertice con etichetta la stringa. Fallisce se gia' presente
bool graph::addVertex(Label l, Graph& g) {
  if (isEmpty(g)) {
    VertexNode* vn = new VertexNode;
    vn->label = l;
    vn->next = (VertexNode*)noVertexNode;
    vn->adjList = noAdjNode;

    g = vn;

    return true;
  }
  
  if (g->label == l)
    return false;
  
  return addVertex(l, g->next);
}


VertexNode* graph::getVertex (Label l, Graph& g) {
  if (g == noVertexNode) // Se il grafo e' vuoto
    return (VertexNode*)noVertexNode; // Restituisco nessuno vertice

  if (g->label == l) // Se ho trovato il vertice
    return g; // Lo restituisco
  
  return getVertex(l, g->next); // Continuo la ricerca al prossimo vertice
}

bool adjAddBack (VertexNode* v, AdjList &l, Weight w) { // Aggiunge v in coda a l con peso w
  if (l == noAdjNode) {
    l = new AdjNode;
    l->p = v;
    l->weight = w;
    l->next = (AdjNode*)noAdjNode;

    return true;
  }

  if (l->p == v)
    return false;

  return adjAddBack(v, l->next, w);
}

// Aggiunge un arco di peso "w" tra i nodi con etichetta "f" e "t". Fallisce se esiste gia' l'arco
// se i nodi non esistono nel grafo e se si tenta di inserire un arco tra un nodo ed esso stesso
bool graph::addEdge(Label from, Label to, Weight w, Graph& g) {
  VertexNode* fromVertex = getVertex(from, g); // Ottengo il vertice from
  if (fromVertex == noVertexNode)
    return false;

  VertexNode* toVertex = getVertex(to, g); // Ottengo il vertice to
  if (toVertex == noVertexNode)
    return false;

  if (fromVertex == toVertex) // Se il vertice e' lo stesso
    return false;

  bool fromSuccesss = adjAddBack(toVertex, fromVertex->adjList, w); // Aggiungo l'adiacenza a from
  if (!fromSuccesss)
    return false;
  
  bool toSuccesss = adjAddBack(fromVertex, toVertex->adjList, w); // Aggiungo l'adiacenza a to
  if (!toSuccesss)
    return false;

  return true;
}

// Restituisce true se il grafo e' vuoto, false altrimenti
bool graph::isEmpty(const Graph& g) {
  return g == noVertexNode;
}

// Ritorna il numero di vertici del grafo
int graph::numVertices(const Graph& g){
  if (g == noVertexNode) // Se non esiste il vertice
    return 0; // Sono arrivato in fondo (e inizio a contare)
  
  return numVertices(g->next) + 1; // Restituisco il numero di vertici contati fin'ora + 1
}

int adjSize (AdjList n) {
  if (n == noAdjNode) // Se non esiste l'adiacenza
    return 0; // Sono arrivato in fondo (e inizio a contare)

  return adjSize(n->next) + 1; // Restituisco il numero di adiacenze contate fin'ora + 1
}

int numEdgesAux (const Graph& g) {
  if (g == noVertexNode) // Se non esiste il vertice
    return 0; // Sono arrivato in fondo (e inizio a contare le adiacenze)
  
  return adjSize(g->adjList) + numEdgesAux(g->next); // Restituisco il numero di adianceze del nodo corrente piu' quello dei successivi (gia' visitati dalla ricorsione)
}

// Ritorna il numero di archi del grafo
int graph::numEdges(const Graph& g){
  return numEdgesAux(g) / 2; // Calcolo il numero di adiancenze totali / 2
}

// Calcola e ritorna (nel secondo parametro) il grado del nodo. Fallisce
// se il nodo non esiste
bool graph::nodeDegree(Label l, int& degree, const Graph& g) {
  VertexNode* vertex = getVertex(l, (Graph&)g); // Ottengo il vertice

  if (vertex == noVertexNode) // Se non esiste
    return false; // Non esiste

  degree = adjSize(vertex->adjList); // Ottengo il grado (numero delle adiacenze)
  return true; // Esiste
}

// Verifica se i due vertici v1 e v2 sono adiacenti (ovvero se esiste un arco)
bool graph::areAdjacent(Label v1, Label v2, const Graph& g) {
  VertexNode* vertex = getVertex(v1, (Graph&)g); // Ottengo il vertice 1

  if (vertex == noVertexNode) // Se non esiste
    return false; // Non sono adiacenti

  AdjNode* adjNode = vertex->adjList; // Ottengo la prima adiacenza

  while (adjNode != noAdjNode) { // FInche' ne esistono
    if (adjNode->p->label == v2) // Se e' il vertice 2
      return true; // Sono adiacenti

    adjNode = adjNode->next; // Passo alla successiva
  }

  return false; // Se non ho ancora ritornato fin'ora vuol dire che non sono adiacenti
}

// Restituisce la lista di adiacenza di un vertice
list::List graph::adjacentList(Label v1, Graph& g) {
  list::List l = list::createEmpty(); // Creo una lista vuota

  VertexNode* vertex = getVertex(v1, g); // Ottengo il vertice
  if (vertex != noVertexNode) { // Se esiste
    AdjNode* adjNode = vertex->adjList; // Ottengo la prima adianceza
    
    while (adjNode != noAdjNode) { // Finche' esiste un'adiacenza
      list::addBack(adjNode->p->label, l); // La aggiungo alla lista
      adjNode = adjNode->next; // Passo alla prossima
    }
  }

  return l; // Restituisco la lista
}


// Funzione ricorsiva che arriva fino a destinazione e calcola strada e percorso a partire dalla fine
int findPathAux (VertexNode* v, Label l2, list::List &path, const Graph& g) {
  if (v->label == l2) { // Se sono arrivato a destinazione
    path = list::createEmpty(); // Inizializzo la lista delle citta'
    return 0; // Ritorno 0 come lunghezza iniziale (perche' non ho ancora percorso niente)
  }

  if (v->visited) // Se ho gia' visitato la citta'
    return invalidPath; // Ritorno percorso non valido

  v->visited = true; // Segno la citta' come gia' visitata

  AdjNode* adjNode = v->adjList; // Ottengo il primo nodo adiacente
  
  while (adjNode != noAdjNode) { // Finche' ne esistono
    int w = findPathAux(adjNode->p, l2, path, g); // Proseguo la ricerca passando per quel nodo
    if (w >= 0) { // Se la strada e' valida (e arrivata in fondo, perche' ha ritornato)
      list::addFront(adjNode->p->label, path); // Aggiungo la citta' alla lista
      v->visited = false; // Resetto la flag visited
      return adjNode->weight + w; // Restituisco la distanza percorsa fin'ora
    }
    adjNode = adjNode->next; // Passo al prossimo nodo
  }

  v->visited = false; // Resetto la flag visited

  return -1; // Restituisco path non valida
}

// Ritorna un cammino tra una citta' ed un altra
// Il cammino da "v1" a "v2" alla fine sara' in "path"
// e la lunghezza sara' in "len".
// Si assume che il chiamante fornisca inizialmente un cammino vuoto.
//
// La funzione rappresenta una variante della visita DFS

void graph::findPath (Label v1, Label v2, list::List &path, int &len, const Graph& g) {
  VertexNode* start = getVertex(v1, (Graph&)g); // Ottiene il vertice di partenza

  len = findPathAux(start, v2, path, g); // Chiama la funzione ricorsiva

  return;
}
/*******************************************************************************************************/
// Stampa il grafo
void printGraph(const graph::Graph& g) {
  VertexNode* vn = g; // Ottengo il primo nodo
  while (vn != noVertexNode) { // Finche' ne esistono
    cout << vn->label << endl; // Stampo il nome del primo nodo

    list::ListNode* l = adjacentList(vn->label, vn); // Ottengo la lista delle adiacenze
    printList(l, 2); // Stampo la lista delle adianceze (con indentazione 2)

    cout << endl;

    vn = vn->next; // Passo al prossimo nodo
  }
}
