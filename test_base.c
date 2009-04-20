#include "base.h"
#include "cgreen/cgreen.h"
/// BST

enum { false = 0, true = 1 };

typedef int key_type;                           /* TO ADJUST */
typedef int rest_type;

typedef struct data_set
{
  key_type key;
  rest_type rest_data;
}
data_set;


typedef struct bs_node
{
  int x;                               /* data in node */
  struct bs_node* bs_lchild;               /* pointer to left and */
  struct bs_node* bs_rchild;                      /*  right child */
}
bs_node;

typedef bs_node* bs_tree;
    

int size=0;          
/******************************************************************/

int is_equal(key_type s1, key_type s2)
{
  if (s1 == s2)
    return true;
  else
    return false;
}

/******************************************************************/

int is_less(int x, int y)
{
  if (x < y)
    return true;
  else
    return false;
}
/******************************************************************/

// bs_tree bs_search(key_type s, bs_tree t)
// { 
//   /* searches in the binary search tree t for a node with key
//      s and returns a pointer to the first node found;
//      if there in no such node, it returns NULL                   */
// 
//   if (t == NULL)                 /* stop searching, key not there */
//     return NULL; 
//   else
//     if (is_equal(t->bs_data.key, s))                 /* key found */
//       return t;
//     else                     /* not found yet; continue searching */
//       if (is_less(s, t->bs_data.key))
// 	return bs_search(s, t->bs_lchild);
//       else
// 	return bs_search(s, t->bs_rchild);
// }

/******************************************************************/
bs_node* rotR(bs_node* h){
	bs_node* x = h->bs_lchild;
	h->bs_lchild = x->bs_rchild;
	x->bs_rchild = h;
	return x;
}
bs_node* rotL(bs_node* h){
	bs_node* x = h->bs_rchild;
	h->bs_rchild = x->bs_lchild;
	x->bs_lchild = h;
	return x;
}


s_node* bs_insert(int x, bs_tree* t)
{
}
bs_node* bs_insert(int x, bs_tree* t)
{
  /* inserts a data set d into the binary search tree t */
     
  if (*t == NULL)                  /* positon for insertion found */
    {
      *t = (bs_tree)malloc(sizeof(bs_node));
      (*t)->x = x;
      (*t)->bs_lchild = NULL;
      (*t)->bs_rchild = NULL;
    } 
  else{
	if (rand() < RAND_MAX/(size+1)){
		printf("inserimento in radice per numero %d size %d \n",x,size);
		return bs_insert(x,t);
		}
                       /* not found yet; continue searching */
    if (is_less(x, (*t)->x)){
      bs_insert(x, &(*t)->bs_lchild);
	(*t) = rotR(*t);
    }else{
      bs_insert(x, &(*t)->bs_rchild);
	  (*t) = rotL(*t);
	
	}
	
	}
	size++;
	return t;
}


/******************************************************************/ 

void delete_minimum( bs_tree *t, bs_tree *minimum)
{
 
  /* provides a pointer pointing at the node with minimal
     key in the binary search tree t and deletes this 
     node from  t                                                 */ 
 
  if (*t == NULL) 
    printf("error in delete_minimum : t = NULL\n");
  else
    if ((*t)->bs_lchild == NULL)
      {                                          /* minimum found */
	*minimum = *t;
	*t = (*t)->bs_rchild;                      /* delete node */
      }
    else             /* minimum not found yet; continue searching */
      delete_minimum(&(*t)->bs_lchild, minimum);
}

/******************************************************************/

void bs_delete(key_type s, bs_tree *t)
{
  /* deletes a node with key s from the binary search tree t.
     If there is not such a node, the tree remains unchanged.     */
       
  bs_node *minimum; /* points at the minimum in the right subtree */
  if (*t != NULL) 
    {
      if (is_equal((*t)->x, s))
	{        /* otherwise there is no key s in the tree; done */
	  if ((*t)->bs_lchild == NULL) 
	    /*      at most one right child; simply delete node   */
	    *t = (*t)->bs_rchild;
	  else if ((*t)->bs_rchild == NULL)  
	    /*            only one left child; simply delete node */
	    *t = (*t)->bs_lchild;
	  else       /*           two children; replace node with
			             minimum of the right subtree */
	    { 
	      delete_minimum(&((*t)->bs_rchild), &minimum);
	      minimum->bs_lchild = (*t)->bs_lchild;
	      minimum->bs_rchild = (*t)->bs_rchild;
	      *t = minimum;
	    }
	}
      else                        /* i.e. (*t)->bs_data.key != s */
	{       /* continue searching for the node to be deleted */
	  if (is_less(s, (*t)->x))
	    bs_delete(s, &((*t)->bs_lchild));
	  else
	    bs_delete(s, &((*t)->bs_rchild));
	}
    }
}

/******************************************************************/

void display(bs_tree t, char direction)
{
  /* prints a whole tree (root on the left, smallest node on top) */
  /* direction in {l, r, t} is the last direction
     (left, right, top=root)                                      */

  static int depth = -1;             /* depth of a node, root = 0 */
  int i;
  
  depth++;
  if (t != NULL)
    {
      display(t->bs_lchild, 'r');
      for (i = 0; i <= depth; i++)
	printf("   ");
      switch (direction)
	{
	  case 'l': printf("`--"); break;
	  case 't': printf("-->"); break;
	  case 'r': printf(",--"); break;
	}
      printf("%i\n", t->x);
      display(t->bs_rchild, 'l');
    }
  depth--;
}

/******************************************************************/
















void test_should_cretetree(){
	rbtree *t = (rbtree*) malloc(sizeof(rbtree));
	assert_not_equal(t,NULL);
	assert_equal(t->nil, t->root);
}


void test_should_insert_element_and_find_it(){
	rbtree *mosaico = createrbtree();
	rbinsert(mosaico,3,1);
	rbinsert(mosaico,1,3);
	rbinsert(mosaico,9,9);
	rbnode * nodo = search(mosaico,3,1);
	assert_equal(3,nodo->x);
	assert_equal(1,nodo->y);
	nodo = search(mosaico,9,9);
	assert_equal(9,nodo->x);
	assert_equal(9,nodo->y);
	nodo = search(mosaico,1,3);
	assert_equal(1,nodo->x);
	assert_equal(3,nodo->y);
}

// TDD nuovo()
void test_get_nuovo(){
	rbtree *mosaico = nuovo();
	assert_not_equal(NULL,search(mosaico,0,0));
	//visualizza_elementare(mosaico);
}

// TDD Inserisci()
void test_should_insert_new_elemnt(){
	rbtree *mosaico = nuovo();
	rbinsert(mosaico,0,1);
	rbinsert(mosaico,2,3);
	assert_not_equal(NULL,search(mosaico,0,1));
	assert_not_equal(NULL,search(mosaico,2,3));
	assert_equal(NULL,search(mosaico,3,3));
	//visualizza_elementare(mosaico);
}

void test_should_not_insert_same_item(){
	rbtree *mosaico = nuovo();
	assert_equal(1,mosaico->count);
	rbinsert(mosaico,1,0);
	assert_equal(2,mosaico->count);
	rbinsert(mosaico,1,0);
	assert_equal(2,mosaico->count);
	rbinsert(mosaico,2,0);
	rbinsert(mosaico,-1,0);
	assert_equal(4,mosaico->count);
}


// TDD perimetro()
void test_should_get_perimetro(){
	rbtree *mosaico = nuovo();
	assert_equal(4,perimetro(mosaico));
	rbinsert(mosaico,1,0);
	assert_equal(6,perimetro(mosaico));
	rbinsert(mosaico,0,1);
	assert_equal(8,perimetro(mosaico));
	rbinsert(mosaico,0,2);
	assert_equal(10,perimetro(mosaico));
	rbinsert(mosaico,1,2);
	rbinsert(mosaico,2,2);
	rbinsert(mosaico,2,1);
	rbinsert(mosaico,2,0);
	assert_equal(16,perimetro(mosaico));
	rbinsert(mosaico,1,1);
	assert_equal(12,perimetro(mosaico));
}

void test_should_get_perimetro_with_spec_example(){
	rbtree *mosaico = nuovo();
	rbinsert(mosaico,1,0);
	rbinsert(mosaico,2,0);
	rbinsert(mosaico,3,0);
	rbinsert(mosaico,4,0);
	rbinsert(mosaico,4,1);
	rbinsert(mosaico,4,2);
	rbinsert(mosaico,3,2);
	rbinsert(mosaico,2,2);
	rbinsert(mosaico,1,2);
	rbinsert(mosaico,1,1);
	assert_equal(11,mosaico->count);
	assert_equal(22,perimetro(mosaico));
}

// TDD ordine()
void should_get_order(){
	rbtree *mosaico = nuovo();
	rbinsert(mosaico,0,-1);
	assert_equal(2,ordine(mosaico));
	rbinsert(mosaico,1,0);
	assert_equal(2,ordine(mosaico));
	rbinsert(mosaico,0,1);
	assert_equal(3,ordine(mosaico));
	rbinsert(mosaico,-1,0);
	assert_equal(3,ordine(mosaico));
}

void should_get_order_from_spec(){
	rbtree *mosaico = nuovo();
	rbinsert(mosaico,1,0);
	rbinsert(mosaico,2,0);
	rbinsert(mosaico,2,-1);
	rbinsert(mosaico,1,1);
	rbinsert(mosaico,1,2);
	assert_equal(4,ordine(mosaico));
	rbinsert(mosaico,1,3);
	assert_equal(5,ordine(mosaico));
	rbinsert(mosaico,-1,0);
	assert_equal(5,ordine(mosaico));
	rbinsert(mosaico,-2,0);
	assert_equal(5,ordine(mosaico));
	rbinsert(mosaico,-3,0);
	assert_equal(6,ordine(mosaico));
	rbinsert(mosaico,2,-2);
	assert_equal(6,ordine(mosaico));
	rbinsert(mosaico,2,-3);
	assert_equal(7,ordine(mosaico));
	rbinsert(mosaico,1,-2);
	rbinsert(mosaico,1,-3);
	rbinsert(mosaico,1,-4);
	assert_equal(8,ordine(mosaico));		
}

/// TEST TOOLS
void test_admitted_positions(){
	int* positions = get_admitted_positions(0,0);
	assert_equal(positions[0],0);
	assert_equal(positions[1],1);
	assert_equal(positions[2],-1);
	assert_equal(positions[3],0);
	assert_equal(positions[4],1);
	assert_equal(positions[5],0);
	assert_equal(positions[6],0);
	assert_equal(positions[7],-1);
	positions = get_admitted_positions(1,0);
	assert_equal(positions[0],1);
	assert_equal(positions[1],1);
	assert_equal(positions[2],0);
	assert_equal(positions[3],0);
	assert_equal(positions[4],2);
	assert_equal(positions[5],0);
	assert_equal(positions[6],1);
	assert_equal(positions[7],-1);	
}



void test_should_order(){
	assert_equal(0, is_lower_than(0,0,0,0));
	assert_equal(-1, is_lower_than(0,0,1,0));
	assert_equal(-1, is_lower_than(1,0,2,0));
	assert_equal(1, is_lower_than(3,-4,0,-3));
	assert_equal(-1, is_lower_than(0,-2,0,-3));
	assert_equal(1, is_lower_than(0,-3,0,-2));
	assert_equal(-1, is_lower_than(0,-4,1,-4));
	assert_equal(-1, is_lower_than(0,8,0,6));
	assert_equal(0, is_lower_than(0,8,0,8));
	assert_equal(-1,is_lower_than(0,-3,2,-3));
	assert_equal(1,is_lower_than(0,-4,4,-3));
	assert_equal(1,is_lower_than(2,-4,2,-3));
	assert_equal(-1,is_lower_than(-1,0,0,0));
	assert_equal(1,is_lower_than(0,-4,2,-2));
	assert_equal(-1,is_lower_than(2,-4,3,-4));
	assert_equal(1,is_lower_than(3,-4,2,-4));
	assert_equal(1,is_lower_than(0,-4,0,-2));
	assert_equal(1,is_lower_than(0,-4,4,-1));
	assert_equal(-1,is_lower_than(0,0,0,-1)); // MUST FALSE
	assert_equal(-1,is_lower_than(0,1,1,1));
	assert_equal(1,is_lower_than(1,1,0,1));
	assert_equal(-1,is_lower_than(2,1,3,1));
	assert_equal(1,is_lower_than(3,1,2,1));
	assert_equal(1,is_lower_than(0,0,-1,0));
	assert_equal(-1,is_lower_than(3,0,0,-1));
	assert_equal(1,is_lower_than(0,-1,3,0));
	assert_equal(-1,is_lower_than(2,0,2,-1));
	assert_equal(-1,is_lower_than(1,3,2,-3));
}
//visualizza avanzato oly show

void should_visualizza_avanzata(){
	rbtree *mosaico = nuovo();
	rbinsert(mosaico,0,1);
	rbinsert(mosaico,0,2);
	rbinsert(mosaico,-1,0);
	rbinsert(mosaico,1,0);
	rbinsert(mosaico,0,-1);
	rbinsert(mosaico,1,1);
	rbinsert(mosaico,1,-1);
	rbinsert(mosaico,2,1);
	rbinsert(mosaico,3,1);
	rbinsert(mosaico,3,0);
	rbinsert(mosaico,2,-1);
	rbinsert(mosaico,1,2);
	rbinsert(mosaico,2,0);
	rbinsert(mosaico,8,0);
	// printf("beccatelo il primo %d \n",mosaico->xup);
//	visualizza_avanzata(mosaico);
}
//// TESTING BST 
void should_test_bst(){
	bs_tree t = NULL;
	  bs_node* pointer;
	  key_type s;
	  data_set d;
	  bs_insert(1, &t);
	 bs_insert(2, &t);
		bs_insert(3, &t);
	bs_insert(4, &t);
		bs_insert(6, &t); 
	bs_insert(7, &t);	
	
	// bs_insert(5, &t);
	 // bs_insert(16, &t);
	 // bs_insert(3, &t);
	 // 	
	 // bs_insert(8, &t);
	// 	bs_insert(9, &t);
	// bs_insert(2, &t);
	// bs_insert(3, &t);
	// 	bs_insert(4, &t);
	// 	bs_insert(5, &t);
	// 	bs_insert(6, &t);
	// 	
	// 	
	// 			bs_insert(7, &t);
	// 					bs_insert(8, &t);
	
		// bs_insert(d, "a");
		// bs_insert(d, "c");
		// 
		display(t, 't');

// 
// 		            assert_true(bs_search('z', t));
// 
}
int main(int argc, char **argv) {
    TestSuite *suite = create_test_suite();
	
	    add_test(suite, test_should_cretetree);
	add_test(suite, test_should_insert_new_elemnt);
	 add_test(suite, test_should_order);
	add_test(suite, test_should_not_insert_same_item);
	add_test(suite,test_should_get_perimetro);
		add_test(suite, test_admitted_positions);
	add_test(suite,should_get_order_from_spec);
		add_test(suite, should_get_order);
	add_test(suite, test_get_nuovo);
	add_test(suite,should_test_bst);
	add_test(suite,should_visualizza_avanzata);
	add_test(suite, test_should_get_perimetro_with_spec_example);


    return run_test_suite(suite, create_text_reporter());
}