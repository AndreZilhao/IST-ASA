#include <stdio.h>
#include <stdlib.h>

void doWork(int numeroInterseccoes, int numeroRuas, int numeroIntInicio){
  
	int **matrizInt;
	matrizInt = (int**) malloc (numeroInterseccoes* sizeof(int*));
	
	int rotaFinal[numeroRuas+1];
	rotaFinal[0]=numeroIntInicio;
	int inicio = 0;				/* interseccao inicio da rua */
	int fim = 0;				/* interseccao fim da rua */
	int linhas=0; 				/* linhas da matriz */
	int colunas=0;				/* colunas da matriz */
	int j = 0;
	int i=0;
	int nPassagens;				/* numero de ruas que passam por uma determinada interseccao */
	int interseccaoActual = numeroIntInicio;
	int numeroRuasAteInicio = 0;
	int numeroRuasAteInicioAux;

	for(colunas=0; colunas<numeroInterseccoes; colunas++){							/*nIntersec*/
		matrizInt[colunas] = (int*) malloc (numeroInterseccoes* sizeof(int));
	}
	
	/* inicializacao da matriz a zero */
	for (linhas=0; linhas<numeroInterseccoes; linhas++){							/*nIntersec*/
		for(colunas=0; colunas<numeroInterseccoes; colunas++){						/*somatorio tj*/ j=0 -> n
			matrizInt[linhas][colunas] = 0;											/*somatorio tj-1*/
		}
	}
	
	while (scanf("%d %d", &inicio, &fim) != EOF){									/*nRuas*/
		
		matrizInt[inicio-1][fim-1]=1;
		matrizInt[fim-1][inicio-1]=1;
		
		if(fim == numeroIntInicio || inicio == numeroIntInicio)						
			numeroRuasAteInicio++;
	}
	
	
	/* numero de ruas que passam por uma interseccao tem de ser par */
	for (linhas=0; linhas<numeroInterseccoes; linhas++){							/*nIntersec*/
		for(colunas=0; colunas<numeroInterseccoes; colunas++){						/*somatorio tj*/
			
			if(matrizInt[linhas][colunas] == 1)										/*somatorio tj-1*/
				nPassagens++;
		}
		
		if(nPassagens%2 !=0){														/*nIntersec -1*/
			printf("-1\n");
			return;
		}
		nPassagens = 0;
	}
	
	numeroRuasAteInicioAux = numeroRuasAteInicio;
	
	if(numeroRuasAteInicio%2 != 0 || numeroRuasAteInicio ==0){
		printf("-1\n");
		return;
	}
	
	j=1;
	numeroRuasAteInicio--;
	while(numeroRuasAteInicio!=0){												/* pior hipotese: */
		for(i=0; i<numeroInterseccoes; i++){									/* somatorio nInterse*/
			
			if(matrizInt[interseccaoActual-1][i] ==1){							/*somatorio nInterse - 1*/
					
					if(!(j>1 && j<(numeroRuas)									
					&& ( (interseccaoActual == numeroIntInicio) || ((i+1) == numeroIntInicio)) 
					&& (numeroRuasAteInicio == 1))
					){
						
						matrizInt[interseccaoActual-1][i] = 0;
						matrizInt[i][interseccaoActual-1] = 0;
						if(interseccaoActual == numeroIntInicio || i+1 == numeroIntInicio)
							numeroRuasAteInicioAux--;
						interseccaoActual = i+1;
						rotaFinal[j]=interseccaoActual;
						j++;
						numeroRuasAteInicio=numeroRuasAteInicioAux;	
						i=-1;
						
					}				
			}	
		}	
	}	
	
	for (i=0; i<=numeroRuas-1; i++){							/* n ruas*/
			printf("%d ", rotaFinal[i]);	
	}
	
	printf("%d\n", rotaFinal[i]);
	
	return;
}

int main (){
	
	int numeroInterseccoes=0;
	int numeroRuas=0;
	int numeroIntInicio=0;
	
	/*Dados das peÃ§as sao obtidos aqui*/

	if((scanf("%d", &numeroInterseccoes) != 1 || numeroInterseccoes == 0) 
		|| (scanf("%d", &numeroRuas) !=1 || numeroRuas == 0) 
		|| (scanf("%d", &numeroIntInicio) !=1 || numeroIntInicio == 0)){
		printf("-1\n");
		return 0;
	}

	doWork(numeroInterseccoes, numeroRuas, numeroIntInicio);

	return 0;
}