
#include <stdio.h>
#include "tinymath.h"

/* We check if a welcome message has been defined and define it if it 
 * has not been. This allows us to define the welcome message in the 
 * make file and have difference messages depending on the method of 
 * linking. See the Makefile in this directory for more information.
 */
#ifndef WELCOME_MSG
#define WELCOME_MSG "Linking test welcome message"
#endif

int main(int argc, char* argv[]) {
	double v1, v2, m;
	v1 = 156.1;
	v2 = 54.1;
	printf("%s\n",WELCOME_MSG);
	m = add(v1,v2);
	printf("%.2lf + %.2lf = %.2lf\n",v1,v2,m);
	m = subtract(v1,v2);
	printf("%.2lf - %.2lf = %.2lf\n",v1,v2,m);
	m = multiply(v1,v2);
	printf("%.2lf * %.2lf = %.2lf\n",v1,v2,m);
	m = divide(v1,v2);
	printf("%.2lf / %.2lf = %.2lf\n",v1,v2,m);
	return 0;
}
