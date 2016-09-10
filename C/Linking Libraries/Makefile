# Make file for Linking Libraries Examples in C

all : static_application shared_application runtime_application

# We compile our library with the "Posistion Independent Code" flag set.
# This is not required for static linking, but seeing as we also want to
# dynamically link this library we will set it.
tinymath.o : tinymath.c
	gcc -c -fPIC tinymath.c -o tinymath.o

# Archive tinymath.o into libtinymath.a, multiple *.o files could be 
# added to a single archive file if our library was bigger.
libtinymath.a : tinymath.o
	ar rcs libtinymath.a tinymath.o

# We produce a shared object by calling gcc with the -shared parameter.
# We also pass "-soname libtinymath.so" to the linker using the -Wl 
# parameter.
libtinymath.so : tinymath.o
	gcc -shared -Wl,-soname,libtinymath.so -o libtinymath.so tinymath.o

# When we compile our statically linked application we specify the
# directory to search for the library "-L." and the library to link 
# against "-l:libtinymath.a". We also specify the custom welcome message
# to be used by the program.
static_application :  application.c libtinymath.a
	gcc application.c -L. -ltinymath -o static_application \
		-DWELCOME_MSG="\"This example is statically linked\""

# When we compile our dynamically linked application the command is 
# largely the same as that from before. The only changes are the name of
# the library we are linking against ".so" opposed to ".a". And a change
# to the custom welcom message.
shared_application :  application.c libtinymath.so
	gcc application.c -L. -l:libtinymath.so -o shared_application \
		-DWELCOME_MSG="\"This example is dynamically linked\""

# When we compile the application to be linked at runtime there is no 
# need to specify the tinymaths library during compilation. We do
# however need to link our application against libdl using "-ldl". This 
# library contains the necessary dynamic linking support we need.
runtime_application :  runtime_application.c
	gcc runtime_application.c -o runtime_application -ldl \
		-DWELCOME_MSG="\"This example is dynamically linked at runtime\""

.PHONY: clean
clean :
	rm tinymath.o libtinymath.a static_application libtinymath.so \
		shared_application runtime_application
