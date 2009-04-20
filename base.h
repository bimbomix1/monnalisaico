#include <stdio.h>

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









// procedure richieste
rbtree* nuovo();
int ordine(rbtree* p);



void visualizza_elementare(rbtree *p);



rbtree *createrbtree();
void stampa(rbtree *p);
void rbinsert(rbtree *p, int x, int y);
int perimetro(rbtree *p);
int ordine(rbtree *p);
// void rbinsert(rbtree *p, char *nome);
// void rbdelete(rbtree *r, rbnode *q);
rbnode *search(rbtree *p, int x, int y);

//procedure di utilità

int is_lower_than(int xa, int ya, int xb, int yb);
int* get_admitted_positions(int x, int y);


///TEST STRUCTURES
typedef struct {
	int x;
    int y;
} element;