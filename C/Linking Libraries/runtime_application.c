#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#ifndef WELCOME_MSG
#define WELCOME_MSG "Linking test welcome message"
#endif

typedef double (*mathfunc)(double a, double b);

int main(int argc, char* argv[]) {
	
	void *tinymath_so = dlopen("./libtinymath.so",RTLD_NOW);
	if (tinymath_so == 0) {
		printf("Unable to load tinymath library\n");
		exit(1);
	}
	
	mathfunc add = dlsym(tinymath_so, "add");
	if (add == 0) {
		printf("Unable to load add symbol\n");
		exit(2);
	}
	
	mathfunc subtract = dlsym(tinymath_so, "subtract");
	if (subtract == 0) {
		printf("Unable to load subtract symbol\n");
		exit(2);
	}
	
	mathfunc multiply = dlsym(tinymath_so, "multiply");
	if (multiply == 0) {
		printf("Unable to load multiply symbol\n");
		exit(2);
	}
	
	mathfunc divide = dlsym(tinymath_so, "divide");
	if (divide == 0) {
		printf("Unable to load divide symbol\n");
		exit(2);
	}
	
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
	dlclose(tinymath_so);
	return 0;
}
