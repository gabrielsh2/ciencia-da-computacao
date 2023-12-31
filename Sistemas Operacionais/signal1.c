#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void ouch(int sig) {
    printf("Ouch! - I got signal %d\n", sig);
    // Replace current signal handler with default handler
    (void) signal(SIGINT, SIG_DFL);
}

int main() {
    (void) signal(SIGINT, ouch); // Gatilho gerado pelo Ctrl+C
    while (1) {
        printf("Hello World!\n");
        sleep(1);
    }
    
}
