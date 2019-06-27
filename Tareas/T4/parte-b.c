#include "integral.h" 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "util.h"

double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int p) {
	pid_t child[p];
	int infds[p];
	double step = (xf-xi)/p;

	for (int i = 0; i < p; i++)	{
		int fd[2];

		if(pipe(fd)!=0){
			perror("error pipe");
			exit(1);
		}

		infds[i] = fd[0];
		
		if ((child[i] = fork()) == 0){
			close(fd[0]);
			double res = integral(f,ptr,xi+i*step,xi+(i+1)*step,n);
			write(fd[1],(char*)&res,sizeof(res));
			exit(1);
		}
		else{
			close(fd[1]);
		}
	}

	double result = 0;
	for (int j = 0; j < p; j++){
		double f;
		read(infds[j],(char*)&f,sizeof(f));
		if (f!=0){
			result += f;
		}
		waitpid(child[j], NULL, 0);
	}
	return result;
}

