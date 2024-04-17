#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid;
    printf("Antes del fork() tengo un proceso\n");

    pid = fork();

    if(pid == -1) {
        printf("Hubo un error\n");
        return 1;
    } else if(pid == 0) {
        sleep(1);
        printf("Proceso zombie\n");
        return 0;
    }

    return 0;
}
