typedef unsigned int uint;
uint concat_bits(uint x, int n, uint y, int m);
void eliminar(char *str, char *pat);
char *eliminados(char *str, char *pat);

typedef struct nodo {
  char c;
  struct nodo *izq, *der;
} Nodo;

int k_primeros(Nodo **pa, int k);

