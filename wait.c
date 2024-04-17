// C program to demonstrate working of wait()
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0)
        printf("C: Hola desde el Hijo\n");
    else
    {
        printf("P: Hola desde el padre\n");
        wait(NULL);
        printf("T: Hijo terminó\n");
    }

    printf("Adiós\n");
    return 0;
}