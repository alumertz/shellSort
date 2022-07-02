#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

const char* filename = "entrada.txt";

int main(int argc, char *argv[])
{
    FILE *in_file = fopen(filename, "r");
    int linha = 0;
    int size;
    int *vetor;

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
                }
                token = strtok(NULL, " ");
                vetor[i] = atoi(token);
                i++;
        }

        printf("\nLINHA %d tem %d elementos. Veja a seguir:", linha, size); //mostra o vetor que contem os resultados da linha
        for(int j=0; j<size;j++){
                printf("\n%d", vetor[j]);
        }


        //ORDENA O VETOR DA LINHA

        free(vetor);
        }



    fclose(in_file);
    exit(EXIT_SUCCESS);
}
