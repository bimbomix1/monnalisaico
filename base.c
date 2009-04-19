
#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include <string.h>

#define MAX(a, b) ((a) < (b) ? (b) : (a))
/* Creazione Albero Mosaico*/
rbtree *createrbtree()
{
	rbtree *t = (rbtree*) malloc(sizeof(rbtree));

	if(!t) {
		fprintf(stderr,"Errore di allocazione A\n");
        	exit(-1);
	}
	if(!(t->root = (rbnode*) malloc(sizeof(rbnode)))) {
		fprintf(stderr,"Errore di allocazione B\n");
        	exit(-2);
	}
	t->nil = t->root;
	t->nil->left = t->nil->right = t->nil->up = t->nil;
	t->nil->c = black;
	return t;
}

searchtree *createsearchtree()
{
	searchtree *t = (searchtree*) malloc(sizeof(searchtree));

	if(!t) {
		fprintf(stderr,"Errore di allocazione A\n");
        	exit(-1);
	}
	return t;
}

searchtree *insert(searchtree *p,int k) { 
	
	searchtree *q = malloc(sizeof(searchtree)); 
	searchtree *r = p; 
	searchtree *s = NULL; 
	if(!q) { /* errore */} 
	q->v = k; 
	q->left = q->right = NULL; 
	while(r) { 
		s = r; 
		if (k < r->v){
			// r = r->left;
		}
			// 
		else {
			
		}
		// r = r->right;
			
		// r = k < r->v ? r->left : r->right; 
	} 
	q->up = s; 
	if(!s) return q; 
	
	if(k < s->v) s->left = q; 
	else s->right = q; 
	
	
	return (searchtree*) p; 
} 

searchtree *searchbs(searchtree *p, int k) 
{ 
	if(!p || k == p->v) 
		return p; 
	return searchbs(k < p->v ? p->left : p->right, k); 
} 




/* Visita in ordine dell'albero per la stampa in ordine alfabetico */
void inorder(rbnode *p, rbnode *nil)
{
	if(p != nil) {
        	inorder(p->right,nil);
        	printf("(%d,%d) ", p->x, p->y);
        	// if(p->t == palazzo){
        	//                     printf("palazzo\n");
        	//                     } else {
        	//                            printf("giardino\n");
        	//                            }
        	inorder(p->left,nil);
	}
}

void visualizza_elementare(rbtree *p)
{
	inorder(p->root, p->nil);
}

/* Ricerca il nodo che ha come nome il nome passato come parametro */
rbnode *search(rbtree *r, int x, int y)
{
	rbnode *p = r->root;

	while(p != r->nil && is_lower_than(x,y, p->x,p->y) !=0)
	        if(is_lower_than(x,y, p->x,p->y) < 0)
	                  p = p->left;
                      else
                      p = p->right;
	return p == r->nil ? NULL : p;
}

/* Rotazione sinistra, per mantenere immutate le proprietà dell'albero */
void leftrotate(rbtree *r, rbnode *x)
{
	rbnode *y = x->right;
	
	x->right = y->left;
	if(y->left != r->nil)
		y->left->up = x;
    y->up = x->up;
    if(x->up == r->nil)
             r->root = y;
    else if(x == x->up->left)   
                     x->up->left = y;
                     else
                     x->up->right = y;
    y->left = x;
    x->up = y;
}

/* Rotazione destra, per mantenere immutate le proprietà dell'albero */
void rightrotate(rbtree *r, rbnode *x)
{
	rbnode *y = x->left;

	x->left = y->right;
	if(y->right != r->nil)
 	            y->right->up = x;
    y->up = x->up;
    if(x->up == r->nil)
             r->root = y;
    else if(x == x->up->right)
                 x->up->right = y;
                 else
                 x->up->left = y;
	y->right = x;
    x->up = y;
}				

/* Inserimento del singolo nodo, con valorizzazione di tutti i campi del nodo */
rbnode *simpleinsert(rbtree *tree, int x, int y)
{
	rbnode *q = (rbnode*) malloc(sizeof(rbnode));
	rbnode *r = tree->root;
	rbnode *s = tree->nil;

	if(!q) { 
		fprintf(stderr,"Errore di allocazione C\n");
        	exit(-4);
	}
	
	q->x = x;
	q->y = y;

	q->left = q->right = tree->nil;
	q->c = red;
	
	while(r != tree->nil) {                /* Controllo dove va inserito il nuovo nodo */
		
		s = r;
		if (is_lower_than(x,y, r->x, r->y) < 0){
		   r = r->left;
        }
		else{
			if (is_lower_than(x,y, r->x, r->y) == 0)
				return -1;
             r = r->right;
        }                  
      }
	   q->up = s;
  

	if(s == tree->nil)
		tree->root = q;
	else{
		
       if(is_lower_than(x,y, s->x, s->y) < 0)
           s->left = q;
		else{
			if (is_lower_than(x,y, s->x, s->y) == 0)
				return -1;
   	       s->right = q;
		}
	}
	
	tree->count=tree->count +1;
	
	int* positions = get_admitted_positions(x,y);
	int collisions = 0;
	for(size_t i = 0; i < 7; i = i+2 )
	{
		rbnode *rnode = search(tree,positions[i],positions[i+1]);
		if (rnode){
			// printf("trovata collisione il nodo (%d,%d) collide con (%d,%d) \n ",x,y, positions[i],positions[i+1]);
			collisions = collisions +1;
		}
	}
	
	
	if (x<0 && x< tree->xdown) tree->xdown = x;
	if (x>0 && x> tree->xup) tree->xup = x;
	if (y<0 && y< tree->ydown) tree->ydown = y;
	if (y>0 && y> tree->yup) tree->yup = y;
	tree->ordine = 1+ MAX(tree->xup - tree->xdown,tree->yup - tree->ydown);
	tree->perimetro= (tree->perimetro+4) -(collisions*2);
	return q;
}

/* Inserimento di un nuovo elemento nell'albero */
void rbinsert(rbtree *tree, int xa, int ya)
{
	rbnode *x = simpleinsert(tree, xa, ya);
	if (!x){
		
	while(x != tree->root && x->up->c == red) {     /* Finchè x non è la radice e il padre è red */
		if(x->up == x->up->up->left) {              /* Se il padre di x è uguale al figlio sinistro di suo nonno, cioè il padre di x */
			rbnode *y = x->up->up->right;           /* y è uguale allo zio di x */
            if(y->c == red) {                       /* se il colore di y è red */
				x->up->c = black;                   /* il colore del padre di x è black */
				y->c = black;                       /* il colore di y è balck */
				x->up->up->c = red;                 /* il colore del nonno di x è red */
				x = x->up->up;                      /* x è uguale a suo nonno */
			} else {
				if(x == x->up->right){              /* se x è uguale a suo fratello */
                     x = x->up;              
					 leftrotate(tree,x);            /* leftrotate con x */
                     }            				
				x->up->c = black;                   /* il colore del padre di x è black */
				x->up->up->c = red;                 /* il colore del nonno di x è red */
				rightrotate(tree, x->up->up);       /* rightrotate con il nonno di x */
			}
		} else {                                    
			rbnode *y = x->up->up->left;            /* y è uguale al figlio sinistro del nonno di x */
			if(y->c == red) {                       /* se il colore di y è red */
				x->up->c = black;                   /* il colore del padre di x è black */
				y->c = black;                       /* il colore di y è black */
				x->up->up->c = red;                 /* il colore del nonno di x è red */
				x = x->up->up;                      /* x è uguale a suo nonno */
			} else {
				if(x == x->up->left){               /* se x è uguale a suo fratello */
                     x = x->up;                     /* x è uguale a suo padre */        
					 rightrotate(tree,x);           /* rightrotate con x */ 
                     }   					
				x->up->c = black;                   /* il colore del padre di x è black */      
				x->up->up->c = red;                 /* il colore del nonno di x è red */
				leftrotate(tree, x->up->up);        /* leftrotate con il nonno di x */
			}
		}
	}
	tree->root->c = black;                          /* il colore della root è black */
	}
}

/* Controllo se le proprietà dopo la cancellazione vanno bene */
void fixup(rbtree *tree, rbnode *x)
{
	while(x != tree->root && x->c == black) {                   /* Finchè x non è la radice e il padre è black */
		if(x == x->up->left) {                                  
             rbnode *w = x->up->right;                             
			 if(w->c == red) {
                     w->c = black;                                 
				     x->up->c = red;                               
     				 leftrotate(tree, x->up);                       
                     w = x->up->right;                             
			}
			if(w->left->c == black && w->right->c == black) {
				w->c = red;                                   
				x = x->up;                                    
			} else {
				if(w->right->c == black) {
					w->left->c = black;                       
					w->c = red;                               
					rightrotate(tree, w);                      
					w = x->up->right;                         
				}
				w->c = x->up->c;                              
				x->up->c = black;                             
				w->right->c = black;                          
				leftrotate(tree, x->up);                       
				x = tree->root;                               
			}
		} else {          
               rbnode *w = x->up->left;                                    
			   if(w->c == red) {  
                       w->c = black;                                 
  				       x->up->c = red;                              
  				       rightrotate(tree, x->up);                     
  				       w = x->up->left;                              
                }
			if(w->right->c == black && w->left->c == black) {
				w->c = red;                                   
				x = x->up;                                    
			} else {
				if(w->left->c == black) {
					w->right->c = black;                      
					w->c = red;                               
					leftrotate(tree, w);                     
					w = x->up->left;                          
				}
				w->c = x->up->c;                              
				x->up->c = black;                             
				w->left->c = black;                          
				rightrotate(tree, x->up);                     
				x = tree->root;                              
			}
		}
	}
	x->c = black;
}
 
/*

FUNZIONI RICHIESTE 

*/


rbtree* nuovo(){
	rbtree* mosaico = createrbtree();
	mosaico->count = 0;
	mosaico->xdown=0;
		mosaico->yup=0;
			mosaico->ydown=0;
				mosaico->yup=0;
	rbinsert(mosaico,0,0);
	mosaico->perimetro = 4;
	return mosaico;
}

int perimetro(rbtree *p){
	return p->perimetro;
}

int ordine(rbtree* p){
	return p->ordine;
}
/*

FUNZIONI DI UTILTIA

*/

int* get_admitted_positions(int x, int y){
	int* positions = (int*) calloc(8, sizeof(int));
	positions[0] = x;
	positions[1] = y+1;
	positions[2] = x-1;
	positions[3] = y;
	positions[4] = x+1;
	positions[5] = y;
	positions[6] = x;
	positions[7] = y-1;
	
	return positions;
}
int is_lower_than(int xa, int ya, int xb, int yb){
	if(ya > yb)
		return -1;
	if(ya == yb && xa < xb)
		return -1;
	if(ya > yb)
		return 0;
	if((ya == yb && xa > xb) || ya < yb)
		return 1;
	return 0; // sono uguali
}




void inorderforTest(rbnode *p, rbnode *nil)
{

	if(p != nil) {
        	inorderforTest(p->left,nil);
				
        	inorderforTest(p->right,nil);
	}
}
