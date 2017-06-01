#include <stdio.h>
#define numberColumns 3
#define numberFly 10 /*DEIXAR DE FORMA DINÂMICA*/
#define numberBinary 1024 /*DEIXAR DE FORMA DINÂMICA*/

int main()
{
    /*
    Ler a programação de voo de uma companhia e indicar qual aeronave irá atender os voos para que a diferença do tempo de voo seja a menor.

    Entrada do programa:
        Inteiro n <= 10 (número de aeroportos)
        n linhas contendo (CODIGO IATA, NUMERO MINUTOS DESTINO, NUMERO PASSAGEIRO IDA, NUMERO PASSAFEIRO VOLTA)
        imprimir nesta ordem mais o nome da aeronave que atenderá (EMB-195, ERJ-145) + \n
        imprimir um consolidado de voo de cada aeronave da maneira abaixo:
        CONDIÇÃO: quando as duas aeronaves estão qualificadas para o voo, a ERJ-145 voa o menor tempo.
            printf("ERJ-145 %d minutos \nEMJ-195 %d minutos\n", totalMinutosERJ, totalMinutosEMJ);

    */
    int i,j,ii,jj,n,r;
    int contadorMinutosEMB195=0,contadorMinutosERJ145=0,somatorioDiferencaVoos=0,menorNumero=99999999,menorQdtMinutos=99999999,auxIndex=0,auxIndexVetorCidade=0,numberFlyBinary=numberFly-1;
    int vetorBinariaCombinacoes[10][1024]; // vetor de valores binarios para o calculo
    int matrizSomatorioVooAeronave[numberFly][numberColumns]; // matriz de relacoes de voos

    /*
        Deixar as variaveis vetorCidade e matrizVoos dinâmicas e não usar as constantes #define numberBinary 1024 e #define numberFly 10
    */

    /*DEIXAR DE FORMA DINÂMICA*/char vetorCidade[100][numberFly] = {"FLN","SDU","BSB","CGH","BEL","RBR","CBG","SSA","GRU","CGR"}; // vetor de cidades

    /*DEIXAR DE FORMA DINÂMICA*/int matrizVoos[numberFly][numberColumns] = {{136,42,44},{103,21,59},{122,27,44},{107,32,26},{106,21,64}
                                                                           ,{135,29,46},{141,47,57},{102,49,43},{125,31,34},{137,58,46}}; // matriz de voos

    // Cria o vetor de binario auxiliar
    for(jj=0;jj<1024;jj++){
        for(ii = numberFlyBinary; ii >= 0; ii--) {
          r = jj >> ii;
          if(r & 1) {
            vetorBinariaCombinacoes[ii][jj] = 1;
          } else {
            vetorBinariaCombinacoes[ii][jj] = 0;
          }
        }
    }

    // Cria a estrutura de um vetor binário (distribuição de viagens)
    for(i=0;i<numberBinary;i++){
        for(ii = numberFlyBinary; ii >= 0; ii--){
            if(vetorBinariaCombinacoes[ii][i]==0){
                contadorMinutosEMB195 += matrizVoos[ii][0];
            }else{
                contadorMinutosERJ145 += matrizVoos[ii][0];
            }
        }
        contadorMinutosEMB195 *= 2;
        contadorMinutosERJ145 *= 2;
        somatorioDiferencaVoos = contadorMinutosEMB195 - contadorMinutosERJ145;
        if(somatorioDiferencaVoos < 0) somatorioDiferencaVoos *= -1;
        matrizSomatorioVooAeronave[i][0] = contadorMinutosEMB195;
        matrizSomatorioVooAeronave[i][1] = contadorMinutosERJ145;
        matrizSomatorioVooAeronave[i][2] = somatorioDiferencaVoos;

        contadorMinutosEMB195 = 0;
        contadorMinutosERJ145 = 0;
        somatorioDiferencaVoos = 0;
    }

    // Verifica a menor diferença de tempo de voo
    for(i=0;i<numberBinary;i++){
        if(matrizSomatorioVooAeronave[i][2] < menorNumero){
            menorNumero = matrizSomatorioVooAeronave[i][2];
        }
    }

    // Calcula a menor diferença de tempo e o index que possui o menor tempo de voo para a aeronave ERJ-145
    for(jj=0;jj<numberBinary;jj++){
        if(matrizSomatorioVooAeronave[jj][2] == menorNumero){
            if(matrizSomatorioVooAeronave[jj][1] < menorQdtMinutos){
				for(ii = numberFlyBinary; ii >= 0; ii--){
					r = jj >> ii;
					if(r & 1) {
					   printf("%s ERJ-145\n", vetorCidade[auxIndexVetorCidade]);
					} else {
					   printf("%s EMB-195\n", vetorCidade[auxIndexVetorCidade]);
					}
                    auxIndexVetorCidade++;
				}
                menorNumero = matrizSomatorioVooAeronave[jj][1];
                auxIndex = jj;
            }
        }
    }

    printf("\nERJ-145 %d minutos \nEMB-195 %d minutos\n\n", matrizSomatorioVooAeronave[auxIndex][1], matrizSomatorioVooAeronave[auxIndex][0]);

	getchar();
    return 0;
}
