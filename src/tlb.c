#include <stdio.h>  // printf, fprintf
#include <stdlib.h> // exit, calloc, free
#include <linux/time.h> // clock_gettime
#include <unistd.h> // sysconf

// Función utilitaria para manejar errores
#define handle_error(msg)                                                      \
  do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s pages trials\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    long PAGESIZE = sysconf(_SC_PAGESIZE); // Tamaño de la página
    int pages = atoi(argv[1]);   // Número de páginas
    int trials = atoi(argv[2]);  // Número de repeticiones
    long jump = PAGESIZE / sizeof(int);  // Salto entre páginas

    volatile int *a = calloc(pages * jump, sizeof(int));  // Asignar espacio para todas las páginas
    if (a == NULL) handle_error("calloc");

    struct timespec start, end;

    //Punto inicial de dedida de tiempo
    if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) 
        handle_error("clock_gettime");

    //Experimento
    for (int j = 0; j < trials; j++) {
        for (int i = 0; i < pages * jump; i += jump) {
            a[i] += 1;
        }
    }

    //Punto final de medida de tiempo
    if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) 
        handle_error("clock_gettime");

    // Imprime tiempo transcurrido del experimento en nanosegundos
    double time_per_access = ((end.tv_sec - start.tv_sec) * 1E9 + end.tv_nsec - start.tv_nsec) / (double)(trials * pages);
    printf("%d\t%.2f\n", pages, time_per_access);

    free((void*)a);
    return 0; 
}