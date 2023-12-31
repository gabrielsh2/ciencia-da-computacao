#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    char *message;
    int n;

    printf("Iniciando FORK\n");
    pid = fork();

    switch (pid)
    {
    case -1:
        perror("errouu!\n");
        exit(1);
    case 0:
        message = "\nFILHO\n";
        n = 5;
        break;
    default:
        message = "\nPAI\n";
        n = 3;
        break;
    }

    for (; n > 0; n--)
    {
        printf("PID=%d\n", pid);
        puts(message);
        sleep(1);
    }

    exit(0);
}
