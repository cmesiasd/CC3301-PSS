#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "t1.h"

uint concat_bits(uint x, int n, uint y, int m){
    uint mask = ((1<<n)-1);
    uint mask2 = ((1<<m)-1);
    uint result = (x & mask) << m | (y & mask2);
    return result;
}

char *eliminados(char *str, char *pat){
    int len_str = strlen(str);
    int len_pat = strlen(pat);
    int count_pat = 0;
    int cmp = 0;
    while(*str){
        if(*str == *pat){
            cmp = strncmp(str,pat,len_pat);
            if(cmp==0){
                count_pat++;
                str += len_pat-1;
            }
        }
        str++;
    }
    
    int len_malloc = len_str - (count_pat * len_pat) + 1;
    char *res = (char*)malloc(len_malloc);
    str -= len_str;

    while(*str){
        if(*str == *pat){
            cmp = strncmp(str,pat,len_pat);
            if(cmp==0)
                str += len_pat;
        }
        //*res = *str;
        strncpy(res,str,1);
        res++;
        str++;
    }
    res -= len_malloc-1; 
    return res;
}

void eliminar(char *str, char *pat){

}

int k_primeros(Nodo **pa, int k){
    return 0;
}