# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <conio.h>
# include <locale.h>
# include <ctype.h>
# include "interface.h"

void criarLista(LISTA_ENC_ND *pl) {
    *pl = (ND*) malloc(sizeof(ND));
    if(*pl == NULL) {
        printf("[!] MEMORIA INSUFICIENTE!");
        exit(1);
    }

    (*pl)->primeiro = NULL;
    (*pl)->tamanho = 0;    
}

void inserir (LISTA_ENC_ND lnc, int dia, int mes, unsigned int ano){
    NODO *nod, *aux=lnc->primeiro;
    float numCasos, taxaIsolamento;
    
    nod = (NODO *) malloc(sizeof(NODO));
    if(!nod){
        printf("\nNao foi possivel alocar memoria!");
        exit(1);
    }
    else{
        int exist=0;
        
        printf("\n[Data atual: %02d/%02d/%d]\n\n", dia, mes, ano);
        printf("DIGITE A QUANTIDADE DE CASOS: ");
        scanf("%f", &numCasos);
        printf("DIGITE A TAXA DE ISOLAMENTO: ");
        scanf("%f", &taxaIsolamento);
        while(aux){
            if(ano==aux->covid.ano&&mes==aux->covid.mes&&dia==aux->covid.dia){
                exist=1;
                break;
            }
            aux = aux->prox;
        }
        if(exist){
            aux->covid.numCasos=numCasos;
            aux->covid.taxaIsolamento=taxaIsolamento;
            return;
        }
        else{
            nod->covid.dia=dia;
            nod->covid.mes=mes;
            nod->covid.ano=ano; 
            nod->covid.numCasos=numCasos;
            nod->covid.taxaIsolamento=taxaIsolamento;
        }
    
        if(!lnc->primeiro){
            lnc->primeiro=nod;
            nod->prox=NULL;
        }
        else{
            int pos;
            for(pos=lnc->tamanho+1, aux=lnc->primeiro; pos>2; aux=aux->prox, pos--);
            nod->prox=aux->prox;
            aux->prox=nod;
        }
        lnc->tamanho++;
        exportarDados(lnc);
    }
}

void importarBanco(LISTA_ENC_ND l, DADO valor) {
    NODO *novo, *aux;

    novo = (NODO*)malloc(sizeof(NODO));
    if(novo == NULL) {
        printf("[!] MEMORIA INSUFICIENTE!");
        exit(2);
    }

    novo->covid = valor;

    if(l->tamanho == 0) {
        novo->prox = l->primeiro;
        l->primeiro = novo;
    } else {
        int pos;
        for(pos = l->tamanho + 1, aux = l->primeiro; pos > 2; aux = aux->prox, pos--);
        novo->prox = aux->prox;
        aux->prox =  novo;
    }
    l->tamanho++; 
}

void mostrarTodosDados(LISTA_ENC_ND l) {
    int i, tamanho = l->tamanho;
    NODO *aux;
    aux = l->primeiro;
    printf("LISTA DE DADOS COVID-19:\n");
    
    for(i = 0; i < tamanho; i++, aux = aux->prox) {
        printf("\n------------------------------------------\n");
        printf("DATA: %02d/%02d/%u\n", aux->covid.dia, aux->covid.mes, aux->covid.ano);
        printf("NUMERO DE CASOS NO DIA: %.0f\n", aux->covid.numCasos);
        printf("TAXA DE ISOLAMENTO: %.2f\n", aux->covid.taxaIsolamento);
    }
}

void atualizaDado (LISTA_ENC_ND l) {
    NODO *aux;
    
    int i, tamanho = l->tamanho;
    aux = l->primeiro;
    int diaUsuario, mesUsuario;
	unsigned int anoUsuario;
    
    do{
    	printf("\nDIGITE UMA DATA PARA PESQUISA:		[DD/MM/AAAAA]\n ");
    	scanf("%d/%d/%u", &diaUsuario, &mesUsuario, &anoUsuario);
	}while(!data_eh_valida(diaUsuario, mesUsuario,anoUsuario));
    
    for(i = 0; i < tamanho; i++, aux = aux->prox) {
        if(anoUsuario == aux->covid.ano && mesUsuario == aux->covid.mes && diaUsuario == aux->covid.dia) {
            float casos, taxa;
            
            printf("\n\nREGISTRO ENCONTRADO:\n");
			printf("\nDATA: %02d/%02d/%02u", aux->covid.dia, aux->covid.mes, aux->covid.ano);
			printf("\nNUMERO DE CASOS: %.0f", aux->covid.numCasos);
			printf("\nTAXA DE ISOLAMENTO: %.2f\n", aux->covid.taxaIsolamento);
                        
            printf("DIGITE A NOVA QUANTIDADE DE CADOS: \n");
            scanf("%f", &casos);
            printf("DIGITE A NOVA TAXA DE ISOLAMENTO: \n");
            scanf("%f", &taxa);
            aux->covid.numCasos = casos;
            aux->covid.taxaIsolamento = taxa;

            printf("[!] DADOS ATUALIZADOS COM SUCESSO!");
            exportarDados(l);
            return;
        }
    }

    printf("A DATA ESPECIFICADA NAO CONSTA NO SISTEMA!");    
}

void mostrarPicoAno(LISTA_ENC_ND l) {
    NODO *aux;

    aux = l->primeiro;
    DADO maior = aux->covid;

    while(aux != NULL) {
        if(maior.numCasos < aux->covid.numCasos) {
            maior = aux->covid;
        }
        aux = aux->prox;
    }

    printf("DATA DO MAIOR PICO DO ANO: %02d/%02d/%u\n", maior.dia, maior.mes, maior.ano);
    printf("TOTAL DE CASOS: %.0f\n", maior.numCasos);

}

void mostrarPiorIsolamentoAno(LISTA_ENC_ND l) {
    NODO *aux;

    aux = l->primeiro;
    DADO maior = aux->covid;

    while(aux != NULL) {
        if(maior.taxaIsolamento > aux->covid.taxaIsolamento) {
            maior = aux->covid;
        }
        aux = aux->prox;
    }

    printf("DATA DA PIOR TAXA DE ISOLAMENTO DO ANO: %02d/%02d/%u\n", maior.dia, maior.mes, maior.ano);
    printf("TAXA DE ISOLAMENTO: %.1f\n", maior.taxaIsolamento);

}

void mostrarPiorIsolamentoMes(LISTA_ENC_ND l) {
    NODO *aux, *piorIso;
    int mes;
    unsigned int ano;
    int pior=0;
    float menor;

    do{
    	printf("\nDIGITE A DATA PARA PESQUISA:		[MM/AAAAA]\n ");
    	scanf("%d/%u", &mes, &ano);
	}while(!mes_ano_eh_valido(mes, ano));
    
	for(aux=l->primeiro, menor=aux->covid.taxaIsolamento; aux; aux=aux->prox){
		if(ano==aux->covid.ano&&mes==aux->covid.mes){
			if(menor>=aux->covid.taxaIsolamento){
				piorIso=aux;
                menor = piorIso->covid.taxaIsolamento;
				pior=1;			
			}
		}
	}
	if(pior){
		printf("\nA PIOR TAXA DE ISOLAMENTO DO MES %d FOI NA DATA ABAIXO:", mes);
		printf("\nDATA: %02d/%02d/%02u", piorIso->covid.dia, piorIso->covid.mes, piorIso->covid.ano);
		printf("\nNUMERO DE CASOS: %.0f", piorIso->covid.numCasos);
		printf("\nTAXA DE ISOLAMENTO: %.2f", piorIso->covid.taxaIsolamento);
		return;		
	}
	printf("\nO MES E O ANO NAO EXISTEM NO SISTEMA");
}


void carregarDados(LISTA_ENC_ND l) {
    FILE *arquivo;
    DADO importar;

    arquivo = fopen("bancodados.txt", "r");
    if(arquivo == NULL) {
        printf("[!] ERRO NA LEITURA DO ARQUIVO!");
        exit(3);
    }

    char dado[50];
    char *sub;

    while(1) {

        fgets(dado, 50, arquivo);
        
        sub = strtok(dado, "-");
        importar.dia = atoi(sub);

        sub = strtok(NULL, "-");
        importar.mes = atoi(sub);

        sub = strtok(NULL, "-");
        importar.ano = atoi(sub);

        sub = strtok(NULL, "-");
        importar.numCasos = atof(sub);

        sub = strtok(NULL, "-");
        importar.taxaIsolamento = atof(sub);

        importarBanco(l, importar);

        if(feof(arquivo)) {
            break;
        }
    }

    fclose(arquivo);
}

void exportarDados(LISTA_ENC_ND l) {
    FILE *arquivo;
    arquivo = fopen("armazenamentodados.txt", "w");
    if(arquivo == NULL) {
        printf("[!] ERRO NA ESCRITA DO ARQUIVO!");
        exit(4);
    }
    NODO *aux;
    aux = l->primeiro;
    
    while(aux != NULL) {
        fprintf(arquivo, "%d-%d-%u-%.0f-%.1f\n", aux->covid.dia, aux->covid.mes, aux->covid.ano, aux->covid.numCasos, aux->covid.taxaIsolamento);

        aux = aux->prox;
    }

    fclose(arquivo);

}

void display(LISTA_ENC_ND lnc){
	time_t data;
	time(&data);
	char opcao;  

	struct tm *today = localtime(&data);
    system("cls");
	do{
		printf("\n[DATA ATUAL: %02d/%02d/%d]\n\n", today->tm_mday, today->tm_mon+1, today->tm_year+1900);
		printf("\n1 - INSERIR DADOS;");
		printf("\n2 - MOSTRAR DADOS DE DATA ESPECIFICA;");
		printf("\n3 - ALTERAR DADOS;");
		printf("\n4 - LISTAR TODOS OS DADOS;");
		printf("\n5 - COMPARAR DADOS;");		
		printf("\n0 - SAIR DO MENU;\n");
		do{
			printf("\nINSIRA UM COMANDO VALIDO:");
			scanf(" %c", &opcao);
		}while(isalpha(opcao) || opcao<'0' || opcao>'5');
	
		switch(opcao){
			case '0': break;
			case '1':
                system("cls");
                inserir(lnc,today->tm_mday,today->tm_mon+1,today->tm_year+1900);
				printf("\n[!] DADOS INSERIDOS COM SUCESSO!");
				printf("\nINSIRA QUALQUER TECLA PARA VOLTAR...");
				getch();
                system("cls");
				break;
			case '2': 
                system("cls");
                mostraDado(lnc);
				printf("\nINSIRA QUALQUER TECLA PARA VOLTAR...");
				getch();
                system("cls");
                break;
			case '3':
                system("cls");
                atualizaDado(lnc);
				printf("\nINSIRA QUALQUER TECLA PARA VOLTAR...");
				getch();
                system("cls");
				break;
			case '4':
                system("cls");
                mostrarTodosDados(lnc);
				printf("\nINSIRA QUALQUER TECLA PARA VOLTAR...");
				getch();
                system("cls");
				break;
			case '5': 
                system("cls");
                comparaDados(lnc,today->tm_mday,today->tm_mon+1,today->tm_year+1900);
				printf("\nINSIRA QUALQUER TECLA PARA VOLTAR...");
				getch();
                system("cls");
				break;	
		}
	}while(opcao!='0');
}


void comparaDados(LISTA_ENC_ND lnc, int dia, int mes, unsigned int ano){
	char opcao;
		
	do{
		printf("\n[Data atual: %02d/%02d/%d]\n\n", dia, mes, ano);
		printf("\n1 - COMPARAR TAXA DE ISOLAMENTO E NUMERO DE CASOS DE DUAS DATAS;"); 			
		printf("\n2 - MOSTRAR VARIACAO DO NUMERO DE CASOS E TAXA DE ISOLAMENTO EM RELACAO AO DIA ANTERIOR;");	
		printf("\n3 - MOSTAR PICO DE CASOS DE UM MES;");											
		printf("\n4 - MOSTRAR PIOR TAXA DE ISOLAMENTO DE UM MES;");
		printf("\n5 - MOSTRAR PICO DE CASOS DE UM ANO;");
		printf("\n6 - MOSTRAR PIOR TAXA DE ISOLAMENTO DE UM ANO;");	
		printf("\n0 - VOLTAR AO MENU;\n");
		do{
			printf("\nINSIRA UM COMANDO VALIDO:");
			scanf(" %c", &opcao);
		}while(isalpha(opcao) || opcao<'0' || opcao>'7');
	
		switch(opcao){
			case '0': break;
			case '1': 
                system("cls");
				comparaDatas(lnc);
				printf("\nINSIRA QUALQUER TECLA PARA VOLTAR...");
				getch();
                system("cls");
				break;
			case '2':
				system("cls");
				comparaDataAnt(lnc,dia,mes+1,ano+1900);
				printf("\nINSIRA QUALQUER TECLA PARA VOLTAR...");
				getch();
                system("cls");
				break;
			case '3': 
                system("cls");
				picoCasosMes(lnc);
				printf("\nINSIRA QUALQUER TECLA PARA VOLTAR...");
				getch();
                system("cls");
				break;
			case '4':
				system("cls");
				mostrarPiorIsolamentoMes(lnc);
				printf("\nINSIRA QUALQUER TECLA PARA VOLTAR...");
				getch();
                system("cls");
				break;
			case '5':
				system("cls");
				mostrarPicoAno(lnc);
				printf("\nINSIRA QUALQUER TECLA PARA VOLTAR...");
				getch();
                system("cls");
				break;	
			case '6':
				system("cls");
				mostrarPiorIsolamentoAno(lnc);
				printf("\nINSIRA QUALQUER TECLA PARA VOLTAR...");
				getch();
                system("cls");
				break;
		}
	}while(opcao!='0');
}


void mostraDado(LISTA_ENC_ND lnc){
	NODO *aux;
	int diaUsuario, mesUsuario;
	unsigned int anoUsuario;
   
    do{
    	printf("\nDIGITE UMA DATA PARA PESQUISA:		[DD/MM/AAAAA]\n ");
    	scanf("%d/%d/%d", &diaUsuario, &mesUsuario, &anoUsuario);
	}while(!data_eh_valida(diaUsuario, mesUsuario,anoUsuario));
	
	for(aux=lnc->primeiro; aux; aux=aux->prox){
  		if(diaUsuario==aux->covid.dia&&mesUsuario==aux->covid.mes&&anoUsuario==aux->covid.ano){
  			printf("\n\nREGISTRO ENCONTRADO:\n");
			printf("\nDATA: %02d/%02d/%02u", aux->covid.dia, aux->covid.mes, aux->covid.ano);
			printf("\nNUMERO DE CASOS: %.0f", aux->covid.numCasos);
			printf("\nTAXA DE ISOLAMENTO: %.2f", aux->covid.taxaIsolamento);
			return;
		}
  	}
	printf("\nNAO EXISTE REGISTRO PARA ESSA DATA!");

}


void comparaDatas(LISTA_ENC_ND lnc){
	int dia1, dia2, mes1, mes2, ano1, ano2;
	NODO *aux, *dat1=NULL, *dat2=NULL;
	do{
    	printf("\nDIGITE A DATA 1 PARA PESQUISA:		[DD/MM/AAAAA]\n ");
    	scanf("%d/%d/%u", &dia1, &mes1, &ano1);
	}while(!data_eh_valida(dia1,mes1,ano1));	
	do{
    	printf("\n\nDIGITE A DATA 2 PARA PESQUISA:		[DD/MM/AAAAA]\n ");
    	scanf("%d/%d/%u",  &dia2, &mes2, &ano2);
	}while(!data_eh_valida(dia2,mes2,ano2));
	
	for(aux=lnc->primeiro;aux;aux=aux->prox){
		if(ano1==aux->covid.ano&&mes1==aux->covid.mes&&dia1==aux->covid.dia)
			dat1=aux;
		if(ano2==aux->covid.ano&&mes2==aux->covid.mes&&dia2==aux->covid.dia)
			dat2=aux;
	}
	
	if(!dat1 || !dat2){
		if(dat1&&!dat2)
			printf("\nDATA 2 NAO ENCONTRADA!");
		if(!dat1&&dat2)
			printf("\nDATA 1 NAO ENCONTRADA!");
		if(!dat1&&!dat2)
			printf("\nNENHUMA DATA ENCONTRADA!");		
		return;
	}
	else{
		int cont=2;
		for(aux=dat1;cont;aux=dat2, cont--){
			if(cont==2)
				printf("\nDATA 1");
			else
				printf("\nDATA 2");
			printf("\nDATA: %02d/%02d/%u", aux->covid.dia, aux->covid.mes, aux->covid.ano);
			printf("\nNUMERO DE CASOS: %.0f", aux->covid.numCasos);
			printf("\nTAXA DE ISOLAMENTO: %.2f", aux->covid.taxaIsolamento);
			printf("\n");
		}
	}
}


void comparaDataAnt(LISTA_ENC_ND lnc, int dia, int mes, unsigned int ano){
	int diaUsuario, mesUsuario;
	unsigned int anoUsuario;
	NODO *aux, *dat=NULL, *datAnt=NULL;
	do{
    	printf("\nDIGITE A DATA PARA PESQUISA:		[DD/MM/AAAAA]\n ");
    	scanf("%d/%d/%u", &diaUsuario, &mesUsuario, &anoUsuario);
	}while(!data_eh_valida(diaUsuario,mesUsuario,anoUsuario));	
	
	for(aux=lnc->primeiro;aux; datAnt=aux, aux=aux->prox){
		if(anoUsuario==aux->covid.ano&&mesUsuario==aux->covid.mes&&diaUsuario==aux->covid.dia){
			dat=aux;
			break;
		}
	}
	
	if(dat==lnc->primeiro)
		printf("\nDATA NAO POSSUI DIA ANTERIOR!");
	if(dat){		
		int cont=2;
		for(aux=dat;cont;aux=datAnt, cont--){
			if(cont==2)
				printf("\nDADOS DE HOJE");
			else
				printf("\nDADOS DE ONTEM");
			printf("\nDATA: %02d/%02d/%u", aux->covid.dia, aux->covid.mes, aux->covid.ano);
			printf("\nNUMERO DE CASOS: %.0f", aux->covid.numCasos);
			printf("\nTAXA DE ISOLAMENTO: %.2f", aux->covid.taxaIsolamento);
			printf("\n");
		}
		printf("\nTAXA DE VARIACAO DE CASOS = %s%.0f", (dat->covid.numCasos-datAnt->covid.numCasos)>0?"+":"", dat->covid.numCasos-datAnt->covid.numCasos);
		printf("\nTAXA DE VARIACAO DE TAXA DE ISOLAMENTO = %s%.2f", (dat->covid.taxaIsolamento-datAnt->covid.taxaIsolamento)>0?"+":"", dat->covid.taxaIsolamento-datAnt->covid.taxaIsolamento);
	}
	else
		printf("\nDATA NAO ENCONTRADA!");
}


void picoCasosMes(LISTA_ENC_ND lnc){
	int diaUsuario, mesUsuario, pico=0;
	unsigned int anoUsuario;
	float maior;
	NODO *aux, *datPico=NULL;
	do{
    	printf("\nDIGITE A DATA PARA PESQUISA:		[MM/AAAAA]\n ");
    	scanf("%d/%u", &mesUsuario, &anoUsuario);
	}while(!mes_ano_eh_valido(mesUsuario,anoUsuario));		
	
	for(aux=lnc->primeiro, maior=aux->covid.numCasos; aux; aux=aux->prox){
		if(anoUsuario==aux->covid.ano&&mesUsuario==aux->covid.mes){
			if(maior<=aux->covid.numCasos){
				datPico=aux;
                maior = datPico->covid.numCasos;
				pico=1;			
			}
		}
	}
	if(pico){
		printf("\nO PICO NO NUMERO DE CASOS DO MES %d FOI NA DATA ABAIXO:", mesUsuario);
		printf("\nDATA: %02d/%02d/%u", datPico->covid.dia, datPico->covid.mes, datPico->covid.ano);
		printf("\nNUMERO DE CASOS: %.0f", datPico->covid.numCasos);
		printf("\nTAXA DE ISOLAMENTO: %.2f", datPico->covid.taxaIsolamento);
		return;		
	}
	printf("\nO MES E O ANO NAO EXISTEM NO SISTEMA");
}


int data_eh_valida (int dia, int mes, unsigned int ano){
	time_t data;
	time(&data);
	struct tm *today = localtime(&data);
	
	if(mes==2&&ano%400==0&&ano%100==0&&dia>29 || mes==2&&ano%4==0&&dia>29 || mes==2&&ano%100==0&&ano%400!=0&&dia>28 || mes==2&&ano%4!=0&&dia>28 || mes==11&&dia>30
	|| mes==4&&dia>30 || mes==6&&dia>30 || mes==9&&dia>30 || dia<1||dia>31 || mes<1||mes>12 || ano<1||ano>today->tm_year+1900 || mes==today->tm_mon+1&&ano==today->tm_year+1900&&dia>today->tm_mday){
		printf("\nDATA INVALIDA!\n\n");
		return 0;
	}
	return 1;
}


int mes_ano_eh_valido (int mes, unsigned int ano){
	time_t data;
	time(&data);
	struct tm *today = localtime(&data);

	if(mes<1||mes>12 || ano<1||ano>today->tm_year+1900 || ano==today->tm_year+1900&&mes>today->tm_mon+1){
		printf("\nDATA INVALIDA!\n\n");
		return 0;
	}
	return 1;
}