#include <time.h> // Para usar timespec_get
#include <stdio.h> // Para poder imprimir por pantalla
#include <stdlib.h> // Para poder usar getline()
#include <string.h> // Para poder usar strcmp() 
#include <sys/types.h> // para poder usar pid_t
#include <unistd.h> // Necesario para declarar el fork()
#include <sys/wait.h> // Para poder usar el wait()
#include <pwd.h> // para usar el struct passwd
#include <errno.h> // para usar una variable errno

#define MAX_ARGUMENTS 40

int SonIguales(const char *str1, const char *str2) {
	return strcmp(str1, str2) == 0;
}

int main()
{
	// Tamaño inicial del buffer
	size_t n = 10;
	char *buf = malloc(sizeof(char) * n);
	// Creamos una variable para controlar la salida del bucle
	int seguir_ejecutandose = 1;
	// Arreglo de argumentos
	char *args[MAX_ARGUMENTS];
	char *cara = ":)";
	// Creamos el estado que devolvera el hijo 
	int status;

	//Bucle principal del programa
	while(seguir_ejecutandose) {
		printf("%s", cara);
		getline(&buf, &n, stdin);

		// Cambiando el \n por un \0
		if((strlen(buf) > 0) && (buf[strlen(buf) - 1] == '\n')) {
			buf[strlen(buf) - 1] = '\0';
		}

		// Salir del bucle si se introduce exit o exit()
		if(SonIguales(buf, "exit") || SonIguales(buf, "exit()")) {
			// Ponemos el valor de seguir_ejecutandose a 0
			seguir_ejecutandose = 0;
			continue;
		}

		// Comprobar que se introduce clear por terminal
		if(SonIguales(buf, "clear")) {
			printf("\033[2J\033[H");
			continue;
		}

		// Dividimos la entrada del usuario por tokens
		char *token = strtok(buf, " ");
		int i = 0;
		while(token != NULL) {
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		// Implementamos el comando cd
		if(SonIguales(args[0], "cd")){
			struct passwd *pwd;
			char* path = args[1];
			if(path == NULL) {
				pwd = getpwuid(getuid());
				path = pwd->pw_dir;
			}
			errno = chdir(path);
			if (errno != 0){
				printf("No existe ese directorio o hubo un error\n");
				cara = ":(";
			} else {
				printf("Se cambió al directorio %s\n", path);
				cara = ":)";
			}
			continue;
		}

		// Creamos un proceso hijo
		pid_t pid;
		
		// Obtenemos la marca de tiempo de inicio
		struct timespec begin;
		timespec_get(&begin, TIME_UTC);

		pid = fork();

		if (pid == -1) {
			// Error al crear el hijo
			perror("Error al crearse el proceso hijo");
			exit(1);
		} else if (pid == 0) {
			// Proceso hijo
			printf("PID del proceso hijo %d\n", getpid());
			printf("PID del proceso padre es %d\n", getppid());

			execvp(args[0], args);
			exit(1); //Salir si execve falla
		} else {
			// Proceso padre
			wait(&status); // Espera a que termine el hijo
			// Obtenemos la marca de tiempo final
			struct timespec end;
			timespec_get(&end, TIME_UTC);

			// Calcula el tiempo de ejecución del proceso hijo
			double time_spent = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
			printf("Tiempo de ejecución del proceso hijo: %f segundos\n", time_spent);
			if(WEXITSTATUS(status) == 1) {
				cara = ":(";
			} else {
				cara = ":)";
			}
		}
	}
	free(buf);
	return 0;
}