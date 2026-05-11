# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <conio.h>
# include <locale.h>
# include <ctype.h>
# include "interface.h"

int main() {

	setlocale(LC_CTYPE, "Portuguese");

	LISTA_ENC_ND l;

	criarLista(&l);
	carregarDados(l);
	display(l);
	return 0;
}