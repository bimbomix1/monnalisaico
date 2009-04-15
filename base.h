


typedef enum {red, black} colore;
struct rbnode {
	char* nome;
	colore c;                          /* Colore del nodo */
	struct rbnode *left, *right, *up;  /* Puntatori ai due figli e al padre */
}; 

typedef struct rbnode rbnode;

typedef struct {
	rbnode *root, *nil;
} rbtree;


rbtree *createrbtree();
void stampa(rbtree *p);
void rbinsert(rbtree *p, char *nome);
void rbinsert(rbtree *p, char *nome);
// void rbdelete(rbtree *r, rbnode *q);
// rbnode *search(rbtree *p, char *nome);

//procedure di utilità

int is_lower_than(int xa, int ya, int xb, int yb);