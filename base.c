
#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include <string.h>

#define MAX(a, b) ((a) < (b) ? (b) : (a))
int xup,xdown,yup,ydown,ordine,currentLine = NULL;
bst adm_positions;
int *grid;



/* crea nuovo record nell'albero */
bst BSTinit( void ) { return NULL; }

bst NEW( int x,int y, bst sx, bst dx ) { 
  bst b = malloc( sizeof( struct BST ) );
b->x = x;b->y = y; b->sx = sx; b->dx = dx;
  return b;
}


int BSTcount( bst b ) {
  if ( b == NULL ) return 0;
  return 1 + BSTcount( b->sx ) + BSTcount( b->dx );
}

bst rotDX( bst b ) {
  bst x = b->sx; b->sx = x->dx; x->dx = b;
  return x;
}

bst rotSX( bst b ) {
  bst x = b->dx; b->dx = x->sx; x->sx = b;
  return x;
}

bst BSTinsertInRoot( bst b, int x, int y ) {
  if ( b == NULL ) return NEW( x,y, NULL, NULL );
 
  if (is_lower_than(x,y, b->x, b->y) <0) {
    b->sx = BSTinsertInRoot( b->sx, x ,y );
    b = rotDX( b );
  }
  else {
    b->dx = BSTinsertInRoot( b->dx, x,y);
    b = rotSX( b );
  }
  return b;
}

/* Inserimento versione Randomizzata  Esegue inserimento standar o in radice */
bst BSTinsert( bst b, int x, int y ) {
  if ( b == NULL ) return NEW( x,y, NULL, NULL );
  if (is_lower_than(x,y,b->x, b->y) == 0){

	return b;
  }
		
  if (rand() < RAND_MAX/(BSTcount( b )+1)){
  			return BSTinsertInRoot(b,x,y);
  }
  if (is_lower_than(x,y, b->x, b->y) <0)
		b->sx = BSTinsert( b->sx, x,y );
  if (is_lower_than(x,y, b->x, b->y) >0)
	    b->dx = BSTinsert( b->dx, x,y );	
  return b;
}



int BSTsearch( bst b, int x, int y ) {
  if ( b == NULL )
    return 0; 
  if ( b->x == x && b->y == y)
	return 1;
	
    if ( is_lower_than(x,y, b->x,b->y) < 0) {	
		return BSTsearch( b->sx, x,y );
    }else{
	 	return BSTsearch( b->dx, x,y );
	
	}
}



bst removeNode( bst b, bst f ) {
  bst v;
  if ( b->sx != NULL ) v = b->sx;
  else v = b->dx;
  if ( f ) {
    if ( f->sx == b ) f->sx = v;
    else f->dx = v;
  }
  free( b );
  return v;
} 


bst deleteNode( bst b, int x,int y , bst father ) {
  if ( b == NULL ) return b;
  if ( is_lower_than(x,y,b->x,b->y ) < 0 ) b->sx = deleteNode( b->sx, x,y, b );
  if ( is_lower_than(x,y,b->x,b->y ) > 0) b->dx = deleteNode( b->dx, x,y, b );
  if ( is_lower_than(x,y,b->x,b->y ) == 0) {
    if ( ( b->sx == NULL ) || ( b->dx == NULL ) ) b = removeNode( b, father );
    else {
      bst m = b->sx, f = b;
      while ( m->dx ) { f = m; m = m->dx; }
      b->x = m->x;
	  b->y = m->y;
      m = removeNode( m, f );
    }
  }
  return b;
}

bst BSTdelete( bst b, int x, int y ) { return deleteNode( b, x,y, NULL ); }

int BSTGetRootX(bst b){
	return b->x;
}
int BSTGetRootY(bst b){
	return b->y;
}

void BSTdisplay( bst b ) {
  int i;
  static int prof = 0;
  if ( b == NULL ) return ;
  prof++;
  BSTdisplay( b->sx );
  for ( i = 0; i < prof; i++ ) printf( "    " );
  printf("(%d,%d)", b->x, b->y );
  printf( "\n" );
  BSTdisplay( b->dx );
  prof--;
}

void BSTdisplayInOrder( bst b ) {

  if ( b == NULL ) return ;
  BSTdisplayInOrder( b->sx );
  printf("(%d,%d)", b->x, b->y );
  BSTdisplayInOrder( b->dx );
}


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



/* Visita in ordine dell'albero per la stampa in ordine alfabetico */
void inorder(rbnode *p, rbnode *nil)
{
	if(p != nil) {
        	inorder(p->left,nil);
			printf("(%d,%d) ", p->x, p->y);
            inorder(p->right,nil);
	}
}

void visualizza_elementare(rbtree *p)
{
	inorder(p->root, p->nil);
}


void inorderadv(rbnode *p, rbnode *nil){
	if(p != nil) {
	inorderadv(p->left,nil);
	int cordx = xdown <0 ? p->x -xdown : p->x;
	int cordy = ydown <0 ? p->y -ydown : p->y;
	 if (currentLine == NULL)
	 		currentLine = cordy; 	
	 	 if (cordy != currentLine){
	 	 		currentLine = cordy;
				for(size_t i = 0; i < ordine; ++i){
					if (grid[i] == 1){
						printf("x");
					}else{
						if (grid[i] == 2)
							printf("0");
						else
						   printf(" ");
					}
					grid[i] = 0;
				}
				printf("\n");
	 	}
			if (p->x == 0 && p->y == 0){
				grid[cordx] = 2;
			}else{
				grid[cordx] = 1;
			}
	inorderadv(p->right,nil);
	}
}
void visualizza_avanzata(rbtree *p){
	
	// inizializza variabili utili per la visualizzazione
	xup = p->xup;
	xdown = p->xdown;
	yup = p->yup;
	ydown = p->ydown;
	ordine = p->ordine;
	
	// alloca struttura temporanea per la riga da stampare
	grid = malloc(ordine * sizeof(int));
	
	// stampa ultima riga
	inorderadv(p->root, p->nil);
		for(size_t i = 0; i < ordine; ++i){
		 if (grid[i] == 1){ printf("x");}
		 else{
			if (grid[i] == 2)
					printf("0");
			else
				   printf(" ");
			}
		}
		printf("\n");
		free(grid); // libera lo spazio occupato dalla struttura temporanea per la visualizzazione
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
	// controlla se la tessera nelle posizioni x, y è ammessa
	if (BSTsearch(adm_positions,x,y)!= 1){
		return NULL;
	}
	// cancella la tessera dalle posizioni ammesse
	adm_positions = BSTdelete(adm_positions,x,y);	   
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
				return NULL;
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
				return NULL;
   	       s->right = q;
		}
	}
	// aumenta il numero nodi presenti
	tree->count=tree->count +1;
	// ottiene le posizioni ammissibili del nuovo nodo
	int* positions = get_admitted_positions(x,y);
	int collisions = 0;
	for(size_t i = 0; i < 7; i = i+2 )
	{
		rbnode *rnode = search(tree,positions[i],positions[i+1]);
		if (rnode){
			collisions = collisions +1;
		}else{
			adm_positions = BSTinsert( adm_positions, positions[i],positions[i+1] );
		}
	}
	
	/// caricamento variabili di utilità
	if (x<0 && x< tree->xdown) tree->xdown = x;
	if (x>0 && x> tree->xup) tree->xup = x;
	if (y<0 && y< tree->ydown) tree->ydown = y;
	if (y>0 && y> tree->yup) tree->yup = y;
	// generazione del perimetro e dell'ordine
	tree->ordine = 1+ MAX(tree->xup - tree->xdown,tree->yup - tree->ydown);
	tree->perimetro= (tree->perimetro+4) -(collisions*2);
	return q;
}

/* Inserimento di un nuovo elemento nell'albero */
int rbinsert(rbtree *tree, int xa, int ya)
{
	
	rbnode *x = simpleinsert(tree, xa, ya);
	if (x == NULL)
			return -1;
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
 
/*

FUNZIONI RICHIESTE 

*/


rbtree* nuovo(){
	rbtree* mosaico = createrbtree();
	adm_positions = BSTinit();
	mosaico->count = 0;
	mosaico->xdown=0;
	mosaico->yup=0;
	mosaico->ydown=0;
	mosaico->yup=0;
	mosaico->ordine = 1;
	adm_positions = BSTinsert( adm_positions, 0, 0 );
	rbinsert(mosaico,0,0);
	mosaico->perimetro = 4;
	return mosaico;
}

int get_perimetro(rbtree *p){
	return p->perimetro;
}

int get_ordine(rbtree* p){
	return p->ordine;
}

void inserisci_a_caso(rbtree* p){
	int x,y;
	x = BSTGetRootX(adm_positions);
	y = BSTGetRootY(adm_positions);
	rbinsert(p,x,y);
    adm_positions = BSTdelete(adm_positions,x,y);
}

rbtree* costruisci(rbtree* p, int *n){

	for(int i = 1; i < *n; ++i)
	{
		inserisci_a_caso(p);	
	}
	return p;
}

void statistica (rbtree* p, int n, int k){
  float a = 0, b = 0; 
  int h; int per;
  printf( "prova %d %d\n", n, k );
  for ( int i = 0; i < k; i++ ) {
    // printf( "prova\n" );
    rbtree *m = nuovo();
	costruisci(m,&n);
	h = get_ordine(m);
	per = get_perimetro(m);
	a += (h * h) / n;
	b += per / n;
  }
  printf(" a = %f b = %f \n", a / k, b / k);
}

bst getAdmpositions(){
	return adm_positions;
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



