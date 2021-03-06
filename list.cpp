////////////////////////////////////////////////////
//
//  Questa serve per realizzare le liste che vengono fuori come risultato di
//  operazioni quali il percorso tra due citta' (che viene rappresentato come
//  lista di nomi di citta') e l'elenco delle citta' adiacenti a una certa
//  citta' (anch'esso rappresentato come lista di nomi di citta').
//  Non serve invece per le liste dei vertici nel grafo, ne' per le liste di
//  adiacenza di ciascun vertice.
//
////////////////////////////////////////////////////

#include "list.h"

using namespace list;


/****************************************************************/
void list::clear(List& l){
   
}


/****************************************************************/
void list::set(int pos, Elem e, List& l) // "set" nel senso di "assegna un valore", non nel senso di "insieme"! E' una terminologia standard, non fate confusione con gli insiemi
{
   
}


/****************************************************************/
void list::add(int pos, Elem e, List& l) // aggiunge e nella posizione pos
{
  
}

/****************************************************************/
bool list::addBack (Elem e, List& l) // aggiunge e in coda
{
  if (l == nullptr) {
    l = new ListNode;
    l->elem = e;
    l->next = nullptr;

    return true;
  }

  if (l->elem == e)
    return false;

  return addBack(e, l->next);
}


/****************************************************************/
void list::addFront(Elem e, List& l) // aggiunge e in coda
{
  ListNode* n = new ListNode;
  n->elem = e;
  n->next = l;
  l = n;
}

/****************************************************************/
void list::removePos(int pos, List& l)
{
  
}


List list::createEmpty()
{
  return nullptr;
}

/****************************************************************/
Elem list::get(int pos, const List& l)
{
  if (pos == 0)
    return l->elem;

  return get(pos - 1, l->next);
}

/****************************************************************/
bool list::isEmpty(const List& l)
{
  return l == nullptr;
}

/****************************************************************/
int list::size(const List& l)
{
  if (l == nullptr)
    return 0;

  return size(l->next) + 1;
}


/****************************************************************/
void printList(const List& l, int indent)
{
  if (l == nullptr)
    return;

  Elem elem = l->elem;

  for (int i=0; i<indent; i++)
    cout << " ";

  cout << elem << endl;

  printList(l->next, indent);
}
