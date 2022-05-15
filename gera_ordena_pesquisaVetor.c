#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int menu(int opcoes, int vOrganizado){
    int retorno;

    do{
        printf("===========->MENU<-===========\n");
        printf("\t-> 0 - SAIR\n");
        printf("\t-> 1 - GERAR VETOR\n");
        if(opcoes > 1){
            if(vOrganizado){
                printf("\t-> 2 - BUSCA SEQUENCIAL\n");
                printf("\t-> 3 - BUSCA BINARIA\n");
            }
            else{
                printf("\t-> 2 - ORDENAR VETOR\n");
                printf("\t-> 3 - BUSCA SEQUENCIAL\n");
            }
        }
        printf("\nDigite uma opcao valida: ");
        scanf("%d", &retorno);

        if(retorno == 2){
            if(!vOrganizado){
                char opcao;

                do{
                    printf("===========->MENU<-===========\n");
                    printf("====->OPCOES DE ORDENACAO<-===\n");
                    printf("\t-> 0 - VOLTAR\n");
                    printf("\t-> M - MERGE SORT\n");
                    printf("\t-> Q - QUICK SORT\n");
                    printf("\nDigite uma opcao valida: ");
                    scanf(" %c", &opcao);

                    if((opcao == 'm') || (opcao == 'M')){
                        return 11; //Retorna o "id" da funcao merge sort
                    }
                    else if((opcao == 'q') || (opcao == 'Q')){
                        return 12; //retorna o "id" da funcao quick sort
                    }
                } while((opcao != 'm') && (opcao != 'M') && (opcao == 'q') && (opcao != 'Q') && (opcao != '0'));

                if(opcao == '0'){
                    continue;
                }
            }
            else{
                return 3; //Retorna o "id" da funcao de busca sequencial
            }
        }
        else if(retorno == 3){
            if(vOrganizado){
                return 4; //Retorna o "id" da funcao de busca binaria
            }
        }
    } while((retorno < 0) || (retorno > opcoes));

    return retorno;
}

void sair(int *vetor){
    if(vetor != NULL){
        free(vetor);
    }
}

int recebe_tVetor(){
    int tVetor;

    do{
        printf("===========->MENU<-===========\n");
        printf("========->GERAR VETOR<-=======\n");
        printf("Digite um numero para o tamanho do vetor ou 0 para sair: ");
        scanf("%d" , &tVetor);
    } while((tVetor < 0) || (tVetor > 1000000));

    return tVetor;
}
void sorteaVetor(int *vetor, int tVetor){
    for(int i = 0; i < tVetor; ++i){
        vetor[i] = rand() % 1000;
    }
}

void imprimirVetor(int *vetor, int tVetor) {
    for(int i = 0; i < tVetor; i++){
        if(i > 0){
            if(i != (tVetor - 1)){
                printf("%d, ", vetor[i]);
            }
            else{
                printf("%d]\n", vetor[i]);
            }
        }
        else{
            printf("v[%d, ", vetor[i]);
        }
    }
    printf("\n");
}

void merge(int *vetor, int iniciaOrdenacao, int pontoMedio, int fimOrdenacao) {
    int tmp[(fimOrdenacao - iniciaOrdenacao) + 1];
    int i = iniciaOrdenacao, j = pontoMedio + 1, k = 0;

    while (i <= pontoMedio && j <= fimOrdenacao) {
        if (vetor[i] < vetor[j]) {
            tmp[k++] = vetor[i++];
        } else {
            tmp[k++] = vetor[j++];
        }
    }
    for (; i <= pontoMedio; i++, k++) {
        tmp[k] = vetor[i];
    }
    for (; j <= fimOrdenacao; j++, k++) {
        tmp[k] = vetor[j];
    }
    for (i = iniciaOrdenacao, k = 0; i <= fimOrdenacao; i++, k++) {
        vetor[i] = tmp[k];
    }
}

int mergeSort(int *vetor, int iniciaOrdenacao, int fimOrdenacao) {
    if (iniciaOrdenacao < fimOrdenacao) {
        int pontoMedio = (iniciaOrdenacao + fimOrdenacao) / 2;
        //Posicao de onde vai ser dividido

        mergeSort(vetor, iniciaOrdenacao, pontoMedio);
        mergeSort(vetor, pontoMedio + 1, fimOrdenacao);

        merge(vetor, iniciaOrdenacao, pontoMedio, fimOrdenacao);
        //Mescla os 2 grandes "vetores" que ja estao ordenados
    }

    return 1;
}

void troca(int *vetor, int a, int b){
    int aux = vetor[a];
    vetor[a] = vetor[b];
    vetor[b] = aux;
}

int particiona(int *vetor, int inicioOrdenacao, int fimOrdenacao){
    int pivot = vetor[inicioOrdenacao], i = inicioOrdenacao;

    for(int j = inicioOrdenacao + 1; j <= fimOrdenacao; j++){
        if(vetor[j] <= pivot){
            i++;
            troca(vetor, i, j);
        }
    }

    troca(vetor, inicioOrdenacao, i);

    return i;
}

int quickSort(int *vetor, int inicioOrdenacao, int fimOrdenacao){
    if(inicioOrdenacao < fimOrdenacao){
        int pivo = particiona(vetor, inicioOrdenacao, fimOrdenacao);

        quickSort(vetor, inicioOrdenacao, pivo - 1);
        quickSort(vetor, pivo + 1, fimOrdenacao);
    }

    return 1;
}

int recebe_valorBusca(){
    int valorBusca;
    
    printf("===========->MENU<-===========\n");
    printf("===========->BUSCA<-==========\n");
    printf("Qual valor voce deseja buscar: ");
    scanf("%d", &valorBusca);

    printf("\n\n");

    return valorBusca;
}

int buscaSequencial(int *vetor, int tVetor, int valorBusca){
    for(int i = 0; i < tVetor; ++i){
        if(vetor[i] == valorBusca){
            return i;
        }
    }
    return -1;
}

int buscaBinaria(int *vetor, int tVetor, int valorBusca){
    int primeiraPosicao = 0, ultimaPosicao = tVetor - 1;

    while(primeiraPosicao <= ultimaPosicao){
        int pontoMedio = (primeiraPosicao + ultimaPosicao) / 2;

        if(valorBusca == vetor[pontoMedio]){
            return pontoMedio;
        }
        else if(valorBusca > vetor[pontoMedio]){
            primeiraPosicao = pontoMedio + 1;
        }
        else if(valorBusca < vetor[pontoMedio]){
            ultimaPosicao = pontoMedio - 1;
        }
    }
    return -1;
}

int main(){
    int retorno, tVetor = 0, *vetor = NULL, opcoes = 1, vOrganizado;

    srand(time(NULL));

    do{
        retorno = menu(opcoes, vOrganizado);

        if(retorno == 1){
            tVetor = recebe_tVetor();

            if(tVetor){
                if(vetor != NULL){
                    realloc(vetor, tVetor);
                }
                else{
                    vetor = (int *)malloc(sizeof(int) * tVetor);
                }

                sorteaVetor(vetor, tVetor);

                printf("\n\nVetor de %d posicoes randomizado!!\n\n", tVetor);

                vOrganizado = 0;

                imprimirVetor(vetor, tVetor);

                printf("\n");
                
                opcoes = 3;
            }
        }
        else if(retorno == 11){
            printf("\n\nMetodo de ordenacao Merge\n\n");

            vOrganizado = mergeSort(vetor, 0, tVetor - 1);

            imprimirVetor(vetor, tVetor);
        }
        else if(retorno == 12){
            printf("\n\nMetodo de ordenacao Quick\n\n");

            vOrganizado = quickSort(vetor, 0, tVetor - 1);

            imprimirVetor(vetor, tVetor);
        }
        else if((retorno == 3) || (retorno == 4)){
            int valorBusca = recebe_valorBusca();

            if(retorno == 3){
                printf("Busca sequencial\n");

                valorBusca = buscaSequencial(vetor, tVetor, valorBusca);
            }
            else{
                printf("Busca binaria\n");

                valorBusca = buscaBinaria(vetor, tVetor, valorBusca);
            }
            
            if(valorBusca == (-1)){
                printf("Valor nao encontrado!!\n\n");
            }
            else{
                printf("Valor %d encontrado na posicao %d\n\n", vetor[valorBusca], valorBusca);
            }
        }
        else{
            if(retorno != 0){
                printf("\n\nOpcao invalida\n\n");
            }
        }
    } while(retorno);

    printf("\n\nPrograma encerrando...\n\n");

    sair(vetor);

    return 0;
}