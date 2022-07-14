#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>
#include <time.h>

const char* filename = "entradaT.txt";
const char* out1 = "saida1.txt";
const char* out2 = "saida2.txt";


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

void selectSort(int *vet,int tam, int type, FILE *out_file1 ){
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
            fprintf(out_file1,"%d ", vet[j]);
        }
        fprintf(out_file1,"INCR=%d\n", h);
        h= calcH(type, h);
    }

    fprintf(out_file1,"\n");
}

void copyVet(int *vet, int *vetcpy, int size){
    for(int x =0 ; x < size ; x++){
        vetcpy[x] = vet[x];
    }
}

int openTxt(){
    FILE *in_file = fopen(filename, "r");
    int linha = 0;
    int size;
    int *vetor,*vetcpy;

    FILE *out_file1 = fopen(out1, "wt");
    FILE *out_file2 = fopen(out2, "wt");


    //variaveis auxiliares para calcular o tempo de execucao
    clock_t t;

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
        copyVet(vetor, vetcpy, size);
        //memcpy(vetcpy, vetor,sizeof(int)*size);//copia vetor
        fprintf(out_file1,"SEQ=SHELL\n");
        t = clock();
        selectSort(vetcpy,size, 0, out_file1);
        t = clock() - t;
        fprintf(out_file2,"\nSHELL,%d,%lf",size, ((double)t)/((CLOCKS_PER_SEC)));

        //KNUTH
        copyVet(vetor, vetcpy, size);
       // memcpy(vetcpy, vetor,sizeof(int)*size); //copia vetor
        fprintf(out_file1,"SEQ=KNUTH\n");
         t = clock();
        selectSort(vetcpy,size, 1, out_file1);
        t = clock() - t;
        fprintf(out_file2,"\nKNUTH,%d,%lf",size, ((double)t)/((CLOCKS_PER_SEC)));

        //CIURA
        fprintf(out_file1,"SEQ=CIURA\n");
         t = clock();
        selectSort(vetor,size, 2, out_file1);
         t = clock() - t;
        fprintf(out_file2,"\nCIURA,%d,%lf",size, ((double)t)/((CLOCKS_PER_SEC)));


        free(vetor);
        }



    fclose(in_file);
    exit(EXIT_SUCCESS);
}


int main()
{

    openTxt();
}
