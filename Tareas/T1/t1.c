#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t1.h"

uint concat_bits(uint x, int n, uint y, int m){
    uint mask = ((1<<n)-1);
    uint mask2 = ((1<<m)-1);
    uint result = (x & mask) << m | (y & mask2 );
    return result;
}

char *eliminados(char *str, char *pat){
    int len_str = strlen(str);
    int len_pat = strlen(pat);
    int count_pat = 1;
    
    int len_malloc = len_str - (count_pat * len_pat) + 1;

    char *res = (char*)malloc(len_malloc);
    return res;
}

void eliminar(char *str, char *pat){

}

int k_primeros(Nodo **pa, int k){

}