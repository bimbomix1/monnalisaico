#include <stdio.h>
#define nullItem NULL
typedef enum {red, black} colore;
struct rbnode {
	int x,y;
	colore c;                          /* Colore del nodo */
	struct rbnode *left, *right, *up;  /* Puntatori ai due figli e al padre */
}; 

typedef struct rbnode rbnode;

typedef struct {
	rbnode *root, *nil;
	int perimetro,ordine, count;
	int xdown, xup, ydown, yup;
}rbtree;



typedef struct BST *bst;

bst BSTinit( void );                           /* inizializza un BST vuoto */
int BSTcount( bst );                           /* conta gli elementi di un BST */
int BSTdeep( bst  );                            /* calcola la profondità massima dell'albero */
// bst BSTinsert( bst, item );                    /* inserisce un nuovo nodo nel BST */
// item BSTsearch( bst, Key );                    /* cerca un record di data chiave nel BST */
// bst BSTdelete( bst, Key );                     /* cancella un record di data chiava, se presente nel BST */
bst BSTfree( bst );                            /* cancella tutti gli elementi dal BST */
// void BSTsort( bst, void ( *visit )( item ) );  /* applica la funzione visit ai nodi del BST, in ordine */
void BSTdisplay( bst );                        /* visualizza in bella forma il contenuto e la struttura del BST */

struct BST {
  int x,y;
  struct BST *sx, *dx;
};


// procedure richieste
rbtree* nuovo();
int ordine(rbtree* p);



void visualizza_elementare(rbtree *p);

rbtree *createrbtree();
void stampa(rbtree *p);
int rbinsert(rbtree *p, int x, int y);
int perimetro(rbtree *p);
int ordine(rbtree *p);
// void rbinsert(rbtree *p, char *nome);
// void rbdelete(rbtree *r, rbnode *q);
rbnode *search(rbtree *p, int x, int y);

//procedure di utilità

int is_lower_than(int xa, int ya, int xb, int yb);
int* get_admitted_positions(int x, int y);


