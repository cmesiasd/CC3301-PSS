typedef int (*Comparador)(void *a, int k, void *x);
int buscar(void *a, int n, void *x, Comparador cmp);
char *consultar(char *nom_dic, char *pal, int n_lin);

#define ANCHO 80
#define LINEAS 12
