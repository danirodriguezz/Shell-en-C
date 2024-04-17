#include <stdio.h>
#include <stdlib.h>

int main()
{
    size_t n = 10;
    char *buf = malloc(sizeof(char) * n);

    printf("Introduce tu nombre: ");
    getline(&buf, &n, stdin);

    printf("Tu nombre es %sEl tamaño del Buffer es %ld\n", buf, n);
    free(buf);


    return(0);
}
