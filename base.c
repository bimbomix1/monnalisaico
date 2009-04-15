
#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include <string.h>

/* Creazione dell'albero red-black */
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

/* Visita in ordine dell'albero per la stampa in ordine alfabetico */
void inorder(rbnode *p, rbnode *nil)
{
	if(p != nil) {
        	inorder(p->left,nil);
        	printf("%s %d", p->nome, p->c);
        	// if(p->t == palazzo){
        	//                     printf("palazzo\n");
        	//                     } else {
        	//                            printf("giardino\n");
        	//                            }
        	inorder(p->right,nil);
	}
}

void stampa(rbtree *p)
{
	inorder(p->root, p->nil);
}

/* Ricerca il nodo che ha come nome il nome passato come parametro */
rbnode *search(rbtree *r, char *nome)
{
	rbnode *p = r->root;

	while(p != r->nil && strcmp(nome, p->nome) !=0)
	        if(strcmp(nome, p->nome) < 0)
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
rbnode *simpleinsert(rbtree *tree, char *nome)
{
	rbnode *q = (rbnode*) malloc(sizeof(rbnode));
	rbnode *r = tree->root;
	rbnode *s = tree->nil;

	if(!q) { 
		fprintf(stderr,"Errore di allocazione C\n");
        	exit(-4);
	}
	q->nome = (char*) malloc(sizeof(nome));
	sprintf(q->nome, "%s", nome);
	// q->coord[0] = coord[0];
	//     q->coord[1] = coord[1];
	//     q->coord[2] = coord[2];
	//     q->coord[3] = coord[3];
	//     q->coord[4] = coord[4];
	//     q->coord[5] = coord[5];
	//     q->t = t;
	q->left = q->right = tree->nil;
	q->c = red;
	while(r != tree->nil) {                /* Controllo dove va inserito il nuovo nodo */
		s = r;
		if (strcmp(nome, r->nome) < 0){
		   r = r->left;
        }
		else {
             r = r->right;                  
             }
        }
	q->up = s;
	if(s == tree->nil)
		tree->root = q;
	else{
       if(strcmp(nome, s->nome) < 0)
           s->left = q;
	   else
   	       s->right = q;
	}return q;
}

/* Inserimento di un nuovo elemento nell'albero */
void rbinsert(rbtree *tree, char *nome)
{
	rbnode *x = simpleinsert(tree, nome);
	
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
// 
// /* Cancellazione di un elemento dell'albero */
// void rbdelete(rbtree *tree, rbnode *q)
// {
// 	rbnode *r, *s;
//     
// 	if(q->left == tree->nil || q->right == tree->nil)
// 		r = q;
// 	else {
//          r = q->right;
//          while (r->left != tree->nil)
//                         r = r->left;
//          }
// 	if(r->left != tree->nil)
// 	           s = r->left;
//     else
//         s = r->right;
//     s->up = r->up;
// 	if(r->up)
//              if(r == r->up->left)
//          r->up->left = s;
//              else
// 			      r->up->right = s;
// 	else
//         tree->root = s;		      
// 	if(r != q)
// 	    q->nome = (char*) malloc(sizeof(r->nome)); 
// 		sprintf(q->nome, "%s", r->nome);
//         // q->coord[0] = r->coord[0];
//         //  q->coord[1] = r->coord[1];
//         //  q->coord[2] = r->coord[2];
//         //  q->coord[3] = r->coord[3];
//         //  q->coord[4] = r->coord[4];
//         //  q->coord[5] = r->coord[5];
//         //  q->t = r->t;
// 	if(r->c == black)
// 		fixup(tree, s);
// 	free(r);
// }
// 
int is_lower_than(int xa, int ya, int xb, int yb){
	if(ya > yb){
	
		return 1;
	}else 
	if((ya == yb)){
	
		if (xa < xb){
			
		    return 1;	
		}else {
			return 0;
		}
		
	} else {
		if (xa <= xb){

		    return 1;	
		}

    }
	return 0;
}
