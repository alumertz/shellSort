#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

const char* filename = "entradaT.txt";

int CIURA[17] = {1,4,10,23,57,132,301,701,1577,3548,7983,17961,40412,90927,204585,460316,1035711};

void ordena(int *vet, int tam, int h){
    int num, pos, auxpos;
    for (int pos=h;pos<tam;pos++){//começa comparando numero na posição h
        num = vet[pos]; //numero na posição pos

        auxpos = pos; //salva posição atual

        //enquanto posição>= ao tamanho do "pulo" h &&
        //o número na posição pos for menor que o número na posição auxpos-h
        while (auxpos>=h && num <vet[auxpos-h]){

            vet[auxpos] = vet[auxpos-h]; //troca de posição
            auxpos = auxpos - h;
        }
        vet[auxpos] = num;
    }
}

int calcH(int type, int h){
    if (type ==0){
        return h/2;
    }
    else if (type==1){
        return (h-1)/3;
    }
    else{
        for(int x = 16; x >= 0; x-- ){
            if (CIURA[x] ==h){
                return h = CIURA[x-1]; //ciura
            }
        }
    }
}

void selectSort(int *vet,int tam, int type){
    int h;

    if (type==0){
        h = floor(tam/2);//shell
    }else if (type ==1){
        h=1;
        while (h< tam/3){
            h = 3*h+1;//knuth
        }
    }else{
        for(int x = 0; x < 17; ++x ){
            if (CIURA[x]<tam && CIURA[x+1]>tam){
                h = CIURA[x]; //ciura
            }
        }
    }

    while (h>0){
        ordena(vet,tam, h);

        for(int j=0; j<tam;j++){
            printf("%d ", vet[j]);
        }
        printf ("INCR=%d\n", h);
        h= calcH(type, h);
    }

    printf ("\n");
}

int openTxt(){
    FILE *in_file = fopen(filename, "r");
    int linha = 0;
    int size;
    int *vetor,*vetcpy;

    struct stat sb;
    stat(filename, &sb);

    char *file_contents = malloc(sb.st_size);

    //percorre o arquivo linha por linha ate terminar.
    //salva cada linha na variavel file_contents.
    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF) {
        linha++; //pra comecar em 1
        //le a quantidade de numeros, primeiro numero no arquivo
        char *token;
        token = strtok(file_contents, " ");

        int i=0; //contador para saber se é o primeiro token

        while(token != NULL){
                //se for o primeiro token, eh o tamanho do vetor
                if(i==0){
                    size = atoi(token);
                    vetor = (int *)malloc(size * sizeof(int));
                    vetcpy = (int *)malloc(size * sizeof(int));
                }
                token = strtok(NULL, " ");
                vetor[i] = atoi(token);
                i++;
        }

        //printf("\nLINHA %d tem %d elementos. Veja a seguir:\n", linha, size); //mostra o vetor que contem os resultados da linha


        //ORDENA O VETOR DA LINHA


        //SHELL
        memcpy(vetcpy, vetor,sizeof(int)*size);//copia vetor
        printf ("SEQ=SHELL\n");
        selectSort(vetcpy,size, 0);
        //KNUTH
        memcpy(vetcpy, vetor,sizeof(int)*size); //copia vetor
        printf ("SEQ=KNUTH\n");
        selectSort(vetcpy,size, 1);
        //CIURA
        printf ("SEQ=CIURA\n");
        selectSort(vetor,size, 3);


        free(vetor);
        }



    fclose(in_file);
    exit(EXIT_SUCCESS);
}


int main()
{
    openTxt();
}
