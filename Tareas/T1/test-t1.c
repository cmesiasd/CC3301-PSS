#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t1.h"

Nodo *abb(char c, Nodo *izq, Nodo *der) {
  Nodo *a= malloc(sizeof(*a));
  a->c= c;
  a->izq= izq;
  a->der= der;
  return a;
}

void mostrar(Nodo *a, int lvl) {
  int i;
  for (i= 0; i<lvl; i++)
    putchar(' ');

  if (a==NULL) {
    printf("NULL\n");
  }
  else {
    printf("%c\n", a->c);
    mostrar(a->izq, lvl+2);
    mostrar(a->der, lvl+2);
  }
}

int comparar(Nodo *a, Nodo *b) {
  if (a==NULL)
    return b==NULL;
  else if (b==NULL)
    return 0;
  else if (a->c != b->c)
    return 0;
  else
    return comparar(a->izq,b->izq) && comparar(a->der,b->der);
}

int main() {
  // Test parte a
  uint z1 = concat_bits(0x5, 3, 0x19, 5); // concat_bits(0b101, 3, 0b11001, 5)
  if (z1!=0xb9) {
    fprintf(stderr, "error en concat_bits(0b101, 3, 0b11001, 5)\n");
    exit(1);
  }
  uint z2= concat_bits(0x1b, 3, 0x15, 2); // concat_bits(0b11011,3,0b10101,2)
  if (z2!=0x0d) {
    fprintf(stderr, "error en concat_bits(0b11011,3,0b10101,2)\n");
    exit(1);
  }
  printf("Test parte a aprobado\n");

  // Test parte b
  {
    char *s1= eliminados("las palas van", "las");
    if (strcmp(s1, " pa van")!=0) {
      fprintf(stderr, "error en eliminados(\"las palas van\", \"las\")\n");
      exit(1);
    }
    char *s2= eliminados("111011001", "10");
    if (strcmp(s2, "11101")!=0) {
      fprintf(stderr, "error en eliminados(\"111011001\", \"10\")\n");
      exit(1);
    }
    printf("Test parte b aprobado\n");
  }

  // Test parte c
  {
    char s1[]= "Xlas palas van";
    eliminar(&s1[1], "las");
    if (strcmp(s1, "X pa van")!=0) {
      fprintf(stderr, "error en eliminar(s1, \"las\")\n");
      exit(1);
    }
    char s2[] = "Y111011001";
    eliminar(&s2[1], "10");
    if (strcmp(s2, "Y11101")!=0) {
      fprintf(stderr, "error en eliminar(s2, \"10\")\n");
      exit(1);
    }
    printf("Test parte c aprobado\n");
  }

  // Test parte d
  Nodo *a= abb('v',
             abb('s',
               abb('r', NULL, NULL),
               abb('u', abb('t', NULL, NULL), NULL) ),
             abb('x', abb('w', NULL, NULL), NULL) );
  Nodo *a2= abb('v',
             abb('s',
               abb('r', NULL, NULL),
               abb('u', abb('t', NULL, NULL), NULL) ),
             abb('x', abb('w', NULL, NULL), NULL) );
  Nodo *b= abb('s', abb('r', NULL, NULL), abb('t', NULL, NULL));
  int k= k_primeros(&a, 20);
  if (!comparar(a, a2) || k!=7) {
    fprintf(stderr, "error en k_primeros(&a, 20)\n");
    exit(1);
  }
  k= k_primeros(&a, 3);
  if (!comparar(a, b) || k!=3) {
    fprintf(stderr, "error en k_primeros(&a, 3)\n");
    exit(1);
  }
  printf("Test parte d aprobado\n");

  printf("Felicitaciones!  Aprobo todos los tests.  Puede entregar.\n");

  return 0;
}
