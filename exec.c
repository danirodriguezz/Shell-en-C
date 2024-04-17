#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main()
{
    char *argv[] = {"/bin/ls", "-l", NULL};

    int val = execve(argv[0], argv, NULL);

    if(val == -1) {
        perror("Error");
    }

    printf("Se ejecutó execve");

    return 0;
}
