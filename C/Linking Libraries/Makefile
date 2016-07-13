all : static_application shared_application runtime_application

tinymath.o : tinymath.c
	gcc -c -fPIC tinymath.c -o tinymath.o
	
libtinymath.a : tinymath.o
	ar rcs libtinymath.a tinymath.o
	
libtinymath.so : tinymath.o
	gcc -shared -Wl,-soname,libtinymath.so -o libtinymath.so tinymath.o
	
static_application :  application.c libtinymath.a
	gcc application.c -L. -l:libtinymath.a -o static_application -DWELCOME_MSG="\"This example is statically linked\""
	
shared_application :  application.c libtinymath.so
	gcc application.c -L. -l:libtinymath.so -o shared_application -DWELCOME_MSG="\"This example is dynamically linked\""
	
runtime_application :  runtime_application.c
	gcc runtime_application.c -o runtime_application -ldl -DWELCOME_MSG="\"This example is dynamically linked at runtime\""

.PHONY: clean
clean :
	rm tinymath.o libtinymath.a static_application libtinymath.so shared_application \
	runtime_application
