#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#include "jsocket.h"
#include "util.h"

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
double result = 0;
double base = 0;
double delta = 1/(double)1000;
int clientes = 0;


typedef void *(*Thread_fun)(void *);

void *serv(long ptr){
    clientes++;
    while (base < 1.00) {
        pthread_mutex_lock(&m);
        double res;
        double xi = base;
        double xf = base + delta;
        base = xf;
        pthread_mutex_unlock(&m);

        printf("env [%.3f, %.3f]\n", xi, xf);
        write(ptr, (char*)&xi, sizeof(xi));
        write(ptr, (char*)&xf, sizeof(xf));
        read(ptr, (char*)&res, sizeof(double));

        
        pthread_mutex_lock(&m);
        if (res!=0) {
            result += res;
        }
        pthread_mutex_unlock(&m);
    }
    clientes--;
    
    if(clientes == 0) 
        printf("integral = %f\n",result);
    close(ptr); 
    return NULL;
    
}

int main(int argc,char** argv){
    long s,s2;
    pthread_t pid;
    
    signal(SIGPIPE, SIG_IGN);

    s = j_socket();

    if(j_bind(s,4000) < 0){
        fprintf(stderr,"Fallo bind \n");
        exit(1);
    }

    for(;;){
        pthread_attr_t attr;
        s2 = j_accept(s);
        pthread_attr_init(&attr);

        if(pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED) != 0){
            fprintf(stderr,"Fallo Detachable");
            exit(1);
        }

        if(pthread_create(&pid, &attr, (Thread_fun) serv,(void*) s2) != 0){
            fprintf(stderr,"No pude crear thread para nuevo cliente %ld \n", s2);
            close(s2);
            exit(1);
        }
        pthread_attr_destroy(&attr);
    }
    return 0;
}