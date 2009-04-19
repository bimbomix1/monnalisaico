#include <stdio.h>
#include "base.h"


int main (int argc, char const *argv[])
{
	char* cmd = (char*) malloc(sizeof(char));
	printf("Digitare il carattere dell'operazione da svolgere secondo il seguente menu:\n");
	printf("n  inizializza un nuovo mosaico \n");
	printf("i  inserisce a caso una tessera\n");
	printf("I (x,y)  inserisce una tessera alle coordinate x,y\n");
	printf("c n  costruisce un mosaico di n tessere\n");	
	printf("p restituisce il perimetro del mosaico\n");
	printf("o resitutisce l'ordine del mosaico\n");
	printf("s (n, k) stampa il valore medio dei k valori di a e di b\n");
	
	while(1){
		printf("\n>");
	   scanf("%s", cmd);
	   switch (cmd[0]){
		case 'n':
			printf("nuovomosaico");
			// rbtree* mosaico = nuovo();
			break;
		case 'i':
			break;
		case 'i':
			break;
		case 'i':	
			break;
		case 'i':
		    break;
	  }
	  return 0;
}