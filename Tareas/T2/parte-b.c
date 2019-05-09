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
	char pa[ANCHO];
	read_line(f, pa, k, ANCHO);
	char *def=malloc(ANCHO*sizeof(char));
	strcpy(def,pa);
	int len_def=0;

	while(*def!=':'){
		def++;
		len_def++;
	}

	*def=0;
	def -= len_def;
	int val = strcmp(def, busqueda);
	return val;
}


char *consultar(char *nom_dic, char *pal, int n_lin) {
	FILE *f = fopen(nom_dic, "r+");
	char *def = malloc((ANCHO +1) * sizeof(char));
	int line = buscar(f, n_lin, pal, cmp_file);

	if (line==-1) {
		free(def); 
		return NULL; 
	}

	char buf[ANCHO+1];
	fseek(f, ANCHO*line, SEEK_SET);
	fread(buf,1,ANCHO,f);
	int largo = 0;
	int len_def = 0;
	for(;;){
		if(buf[largo]==':'){ //Recorro palabra
			break;
		}
		largo++;
	}
	largo++;
	for(;;){ //Recorro def
		if(buf[largo]==':'){
			break;
		}
		def[len_def] = buf[largo];
		largo++;
		len_def++;
	}
	def[len_def] = '\0';
	fclose(f);
	return def;
}
