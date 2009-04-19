#include "cgreen/cgreen.h"
#include "structure.h"



void test_should_create_mosaico(){
	mosaico* m = (mosaico*) createmosaico();
	assert_not_equal(m,NULL);
}

void test_should_create_tessera(){
	tessera* t = (tessera*) malloc(sizeof(tessera));
	assert_not_equal(t,NULL);
}

void test_should_get_nuovo(){
	mosaico* m = nuovo();
	assert_not_equal(m, NULL);
}

void test_should_insert_tessera(){
	mosaico* m = nuovo();
	inserisci(m,0,1);
}


int main(int argc, char **argv) {
    TestSuite *suite = create_test_suite();
    add_test(suite, test_should_create_mosaico);
    add_test(suite, test_should_create_tessera);
	add_test(suite, test_should_get_nuovo);
    return run_test_suite(suite, create_text_reporter());
}

