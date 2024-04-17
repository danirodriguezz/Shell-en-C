#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Hola,mundo,estoy,usando,strtok";
    const char delim[] = ",";

    char *token = strtok(str, delim);

    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, delim);
    }

    return 0;
}