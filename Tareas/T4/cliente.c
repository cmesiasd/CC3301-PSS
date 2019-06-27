#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "jsocket.h"
#include "util.h"
#include "integral.h"

int main(int argc, char **argv) {
    long s = j_socket();
    char* host = "localhost";

    if(j_connect(s,host,4000)<0){
        perror("Fallo conexion");
        exit(1);
    }
    double xi,xf;
    for(;;){
        leer(s,(char*)&xi,sizeof(xi));
        leer(s,(char*)&xf,sizeof(xf));
        printf("rec [%.3f, %.3f]\n",xi,xf);
        double res = integral_f(xi,xf);
        if(res!=0){
            write(s,&res,sizeof(res));
            //printf("result = %f\n",res);
        }
        
    }
    close(s);   
    return 0;
}
