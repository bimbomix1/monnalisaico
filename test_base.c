#include "base.h"
#include "cgreen/cgreen.h"


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
	// visualizza_elementare(mosaico);
}

// TDD Inserisci()
void test_should_insert_new_elemnt(){
	rbtree *mosaico = nuovo();
	rbinsert(mosaico,0,1);
	rbinsert(mosaico,2,3);
	assert_not_equal(NULL,search(mosaico,0,1));
	assert_not_equal(NULL,search(mosaico,2,3));
	assert_equal(NULL,search(mosaico,3,3));
	visualizza_elementare(mosaico);
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

//// TESTING BST 
void should_test_bst(){
	searchtree* ammessi = createsearchtree();
	insert(ammessi,9);
	// searchbs(ammessi,9);
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
	add_test(suite, test_should_get_perimetro_with_spec_example);
	add_test(suite, test_should_insert_element_and_find_it);

    return run_test_suite(suite, create_text_reporter());
}