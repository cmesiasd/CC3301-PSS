#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t2.h"

void read_line(FILE *file, char *line, int i, int len);
int cmp_lines(void *a, int k, void *x);

void read_line(FILE *file, char *line, int i, int len) {
  if (fseek(file, i*ANCHO, SEEK_SET)!=0) {
    perror("compare_file_lines");
    exit(1);
  }
  if (fread(line, 1, len, file)!=len) {
    perror("compare_file_lines");
    exit(1);
  }
}

int cmp_file(void *ptr, int k, void *x){
	FILE *f = ptr;
	char *busqueda = x;
	int len = strlen(busqueda);
	char pa[len];
	read_line(f, pa, k, len);
	int val = strncmp(pa, busqueda, len);
	return val;
}


char *consultar(char *nom_dic, char *pal, int n_lin) {
	FILE *f = fopen(nom_dic, "r+");
	char *palabra;
	int line = buscar(f, n_lin, pal, cmp_file);
	fprintf(stderr, "LINEA = %d \n", line);
	fseek(f,)
	palabra = "holaaa";
	fclose(f);
	return palabra;
}


