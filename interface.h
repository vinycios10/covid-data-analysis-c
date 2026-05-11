typedef struct{
	int dia;
	int mes;
	unsigned int ano;
	float numCasos;
	float taxaIsolamento;
}DADO;

typedef struct nodo{
	DADO covid;
	struct nodo *prox;
}NODO;

typedef struct {
	NODO *primeiro;
	int tamanho;
}ND;

typedef ND *LISTA_ENC_ND;

void criarLista(LISTA_ENC_ND *pl);
void inserir (LISTA_ENC_ND, int, int, unsigned int);
int data_eh_valida(int, int, unsigned int);
int mes_ano_eh_valido(int mes, unsigned int ano);
void importarBanco(LISTA_ENC_ND l, DADO valor);
void carregarDados(LISTA_ENC_ND l);
void exportarDados(LISTA_ENC_ND l);
void atualizaDado (LISTA_ENC_ND l);
void mostrarTodosDados(LISTA_ENC_ND l);
void mostrarPicoAno(LISTA_ENC_ND l);
void mostrarPiorIsolamentoAno(LISTA_ENC_ND l);
void mostrarPiorIsolamentoMes(LISTA_ENC_ND l);
int mes_ano_eh_valido (int mes, unsigned int ano);
void display(LISTA_ENC_ND);
void comparaDados(LISTA_ENC_ND, int, int, unsigned int);
void mostraDado(LISTA_ENC_ND);
void comparaDatas(LISTA_ENC_ND);
void comparaDataAnt(LISTA_ENC_ND, int, int, unsigned int);
void picoCasosMes(LISTA_ENC_ND);
