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

/*   PROTOTIPI PROCEDURE RICHIESTE   */
rbtree* nuovo();
int get_ordine(rbtree* p);
int get_perimetro(rbtree* p);
void visualizza_elementare(rbtree *p);
void visualizza_avanzata(rbtree *p);


/*   STRUTTURA MOSAICO : ALBERO REDBLACK   */


rbtree *createrbtree();
rbnode *search(rbtree *p, int x, int y);
int rbinsert(rbtree *p, int x, int y);
void rbdelete(rbtree *r, rbnode *q);
void stampa(rbtree *p);


/* STRUTTURA POSIZIONI AMMISSIBILI : ALBERO BST RANDOMIZZATO */

struct BST {
  int x,y;
  struct BST *sx, *dx;
};
typedef struct BST *bst;
bst BSTinsert( bst, int, int );                    /* inserisce un nuovo nodo nel BST */
bst BSTinit( void );                           /* inizializza un BST vuoto */
bst BSTfree( bst );                            /* cancella tutti gli elementi dal BST */
int BSTcount( bst );                           /* conta gli elementi di un BST */
void BSTdisplay( bst );                        /* visualizza in bella forma il contenuto e la struttura del BST */

/* Procedure di utilità*/

int is_lower_than(int xa, int ya, int xb, int yb);
int* get_admitted_positions(int x, int y);


