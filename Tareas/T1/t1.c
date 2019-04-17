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
    while(*str){
        if(*str == *pat){
            if(strncmp(str,pat,len_pat)==0){
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
        if(strncmp(str,pat,len_pat)==0)
            str += len_pat;
        strncpy(res,str,1); //*res = *str;
        res++;
        str++;
    }
    res -= len_malloc-1; 
    return res;
}

void eliminar(char *str, char *pat){
    char *ptr;
    int len_pat = strlen(pat);
    ptr = str;
    while(*str){
        if(strncmp(str,pat,len_pat)==0)
                str += len_pat;
        else{
            *ptr = *str;
            str++;
            ptr++;
        }
    }
    *str = *ptr;
    *ptr='\0';
}


int k_primeros(Nodo **pa, int k){
    Nodo *a = *pa;
    if(k==0){
        *pa = NULL;
        return 0;
    }
    else if (a == NULL){
        return 0;        
    }
    else if (a->izq == NULL && a->der == NULL){
        return 1;
    }
    
    else{
        int kizq = k_primeros(&a->izq,k);
        if (kizq== k-1){
            return kizq;
        }
        else if (kizq >= k){
            kizq = k_primeros(&a->izq,kizq);
            *pa = a->izq;
            return kizq;
        }
        int kder = k_primeros(&a->der,k-kizq-1);
        return kizq+kder+1;
    }
}