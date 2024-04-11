// Aluno: Gabriel Hoffmann
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int proximoNumero = 0;
int primos = 0;
pthread_mutex_t mutex;

int isPrime(int num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return 0;
    }
    return 1;
}

void *threadFunction(void *arg) {
    int proximoLocal;
    while (1) {
        pthread_mutex_lock(&mutex);
        proximoLocal = proximoNumero++;
        pthread_mutex_unlock(&mutex);

        if (proximoLocal > 5000000) break;

        if (isPrime(proximoLocal)) {
            pthread_mutex_lock(&mutex);
            primos++;
            pthread_mutex_unlock(&mutex);
        }
    }
}

int main() {
    pthread_t threads[4];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, threadFunction, NULL);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Números primos entre 1 e 5000000: %d\n", primos);

    return 0;
}