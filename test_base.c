#include "base.h"
#include "cgreen/cgreen.h"

void test_should_cretetree(){
	rbtree *t = (rbtree*) malloc(sizeof(rbtree));
	assert_not_equal(t,NULL);
	assert_equal(t->nil, t->root);
}

void test_should_insert_element(){
	rbtree *mosaico = createrbtree();
	rbinsert(mosaico,"ciao");
	assert_true(search(mosaico,"ciao"));
}

void test_should_order(){
	assert_true(is_lower_than(0,0,1,0));
	assert_true(is_lower_than(1,0,2,0));
	assert_false(is_lower_than(3,-4,0,-3));
	assert_true(is_lower_than(0,-2,0,-3));
	assert_true(is_lower_than(0,-3,0,-2));
	assert_true(is_lower_than(0,-4,1,-4));
	assert_true(is_lower_than(0,8,0,6));
	assert_false(is_lower_than(0,8,0,8));
	assert_true(is_lower_than(0,-3,2,-3));
	assert_true(is_lower_than(0,-4,4,-3));
	assert_true(is_lower_than(2,-4,2,-3));
	assert_true(is_lower_than(-1,0,0,0));
	assert_true(is_lower_than(0,-4,2,-2));
	assert_true(is_lower_than(2,-4,3,-4));
	assert_false(is_lower_than(3,-4,2,-4));
	// assert_false(is_lower_than(1,3,2,-3));
	
}

int main(int argc, char **argv) {
    TestSuite *suite = create_test_suite();
    add_test(suite, test_should_cretetree);
   	add_test(suite, test_should_insert_element);
    add_test(suite, test_should_order);

    return run_test_suite(suite, create_text_reporter());
}