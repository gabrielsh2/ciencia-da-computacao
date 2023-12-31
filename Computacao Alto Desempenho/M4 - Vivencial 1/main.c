// Alunos: Gabriel Hoffmann e Rafael Brustolin

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct thread_parms {
    float *total;
    char *fileName;
    int fileIndex;
    pthread_mutex_t *mutex;
} thread_parms;

/*
 * Função para leitura de um arquivo de temperaturas. Espera-se que cada
 * linha do arquivo contenha uma temperatura por linha em formato de ponto
 * flutuante. O returno da função será um inteiro com o número de entradas
 * de temperatura lidas do arquivo. O parâmetro "temp_vector" é uma
 * referência para um array de floats dinamicamente alocado onde serão
 * armazenadas as leituras obtidas do arquivo. O parâmetro "nome_arq" é
 * uma string que contém o nome do arquivo que será lido pela função.
 */
int ler_arquivo_temps(float **temp_vector, char *nome_arq)
{
    FILE *arq_ref;
    int i, count = 0;
    float *res = (float*) malloc(sizeof(float));
    char line_read[20];
    arq_ref = fopen(nome_arq, "r");
    while(fgets(line_read, 20, arq_ref))
    {
        float aux_val = atof(line_read);
        count++;
        res = (float*) realloc(res, sizeof(float)*count);
        res[count-1] = aux_val;
    }
    fclose(arq_ref);
    *temp_vector = res;
    return count;
}

void * calcula_media(void *ptr) {
    thread_parms *tp = (thread_parms*) ptr;
    float  *temps;
    float avg, sum;
    int count, i;

    count = ler_arquivo_temps(&temps, tp->fileName);

    sum = 0;
    for (i=0; i<count; i++)
    {
        sum += temps[i];
    }

    avg = sum / count;
    printf("%d -> %.1f\n", tp->fileIndex+1, avg);

    pthread_mutex_lock(tp->mutex);
    *tp->total += avg;
    pthread_mutex_unlock(tp->mutex);
}

/*
 * Função principal que fará a leitura dos doze arquivos de temperatura,
 * cada um contendo as leituras referentes a um dos meses do ano. Para
 * cada mês, o programa invoca a função de leitura do arquivo. Em seguida,
 * realiza o cálculo da média mensal de temperatura e a imprime.
 */
int main()
{
    int threadnum = 12;
    pthread_t tlist[threadnum];
    thread_parms *atp;
    pthread_mutex_t *mutex;
    float *total;

    mutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutex, NULL);
    total = (float*) malloc(sizeof(float));
    *total = 0;

    char *arquivos_temp[] = {"01.txt", "02.txt", "03.txt", "04.txt", "05.txt", "06.txt", "07.txt", "08.txt", "09.txt", "10.txt", "11.txt", "12.txt"};
    int i;

    for (i=0; i<threadnum; i++)
    {
        atp = (thread_parms*) malloc(sizeof(thread_parms));
        atp->fileName = arquivos_temp[i];
        atp->total = total;
        atp->mutex = mutex;
        atp->fileIndex = i;

        pthread_create( &tlist[i], NULL, calcula_media, (void*) atp);
    }

    for (i=0; i<threadnum; i++)
    {
        pthread_join( tlist[i], NULL );
    }

    float yearAverage = *total / 12.0;

    printf("Média anual %.2f\n", yearAverage);

    return 0;
}