#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    int a = 3;
    int b = 5;
    int sum = a + b;

    pid = getppid();

    printf("El PID de mi padre es: %d\n", pid);
    printf("La suma es %d\n", sum);

    return 0;
}
