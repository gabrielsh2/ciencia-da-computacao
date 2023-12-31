#include <pthread.h>
#include <stdio.h>
unsigned long soma[4];
void *thread_fn(void *arg)
{
    long id = (long)arg;
    int inicio = id * 2500000000;
    int i = 0;
    while (i < 2500000000)
    {
        soma[id] += (i + inicio);
        i++;
    }
    return NULL;
}
int main(void)
{
    pthread_t t1, t2, t3, t4;
    unsigned long resultado = 0;
    pthread_create(&t1, NULL, thread_fn, (void *)0);
    pthread_create(&t2, NULL, thread_fn, (void *)1);
    pthread_create(&t3, NULL, thread_fn, (void *)2);
    pthread_create(&t4, NULL, thread_fn, (void *)3);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    resultado = soma[0] + soma[1] + soma[2] + soma[3];
    printf("%lu\n", resultado);
    return 0;
}