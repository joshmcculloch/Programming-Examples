#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#ifndef WELCOME_MSG
#define WELCOME_MSG "Linking test welcome message"
#endif

/* This is the type definition for our math function. In these examples
 * we are luck beacuse all of the math functions have the same 
 * signature. In less contrived circumstances you would likely need to 
 * create many signatures. 
 */
typedef double (*mathfunc)(double a, double b);

int main(int argc, char* argv[]) {
	
	/* We load our dynamic lirary using a null terminated string 
	 * containing the library's filename and path. We are given a handle
	 * for future reference and check that it is not null.
	 */
	void *tinymath_so = dlopen("libtinymath.so",RTLD_NOW);
	if (tinymath_so == NULL) {
		printf("Unable to load tinymath library\n");
		exit(1);
	}
	
	/* The next for function calls retrieve function pointers for each 
	 * of the math functions in our library. The dlsym function takes 
	 * the library handle we received earlier and a null terminated 
	 * string with the symbol name for the function we want. We use the
	 * function signature "mathfunc" which we created earlier and check 
	 * that the retrieved point is not null.
	 */
	mathfunc add = dlsym(tinymath_so, "add");
	if (add == NULL) {
		printf("Unable to load add symbol\n");
		exit(2);
	}
	
	mathfunc subtract = dlsym(tinymath_so, "subtract");
	if (subtract == NULL) {
		printf("Unable to load subtract symbol\n");
		exit(2);
	}
	
	mathfunc multiply = dlsym(tinymath_so, "multiply");
	if (multiply == NULL) {
		printf("Unable to load multiply symbol\n");
		exit(2);
	}
	
	mathfunc divide = dlsym(tinymath_so, "divide");
	if (divide == NULL) {
		printf("Unable to load divide symbol\n");
		exit(2);
	}
	
	/* We can now use the math functions exactly the same as if they had 
	 * been linked at compile time.
	 */
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
