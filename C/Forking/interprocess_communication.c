#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* Definitions of the possible math operations that can be passed
 * between processes
 */
typedef enum {add, subtract, multiply, divide} MathOperations;

/* Definition of the interprocess message structure
 */
typedef struct {
	MathOperations operation;
	double operand1;
	double operand2;
	double result;
} MathOp;

int main(void) {
	/* We create our two interprocess pipes for comunication. The first 
	 * is the parent to child (ptc) and the child to parent (ctp). These
	 * pipes are defined as arrays of two integers, this is because when
	 * we create a pipe we are given two file handes, one for writing 
	 * and the other for reading.
	 */
	int ptcPipe[2];
	int ctpPipe[2];
	
	/* We create our pipes and check for errors
	 */
	if (pipe(ptcPipe)) {
		printf("Error creating parent to child pipe: %d", errno);
		exit(1);
	}
	
	if (pipe(ctpPipe)) {
		printf("Error creating child to parent pipe: %d", errno);
		exit(2);
	}
	
	/* We fork the application, from this point forward there are two
	 * seperate processes running. When for is called it returns the 
	 * childs process id to the parent and 0 to the child. This allows
	 * us to seperate the two.
	 */
	if (fork() == 0 ) {
		/* Only the child process will execute this code. We close the 
		 * ptcPipe's write file handle and the ctpPipe's read file
		 * handle.
		 */
		close(ptcPipe[1]);
		close(ctpPipe[0]);
		
		/* We create a buffer for storing incomming MathOp messages.
		 */
		char buffer[sizeof(MathOp)];
		
		/* We create a MathOp pointer and point it at the buffer we
		 * created. This will allow us to read values out of the buffer
		 * by using the stucts members.
		 */
		MathOp *request = (MathOp*)buffer;
		
		/* We now call read a message from the ptcPipe into the buffer 
		 * we created. This will block execution until a message is
		 * ready.
		 */
		printf("Child: Ready for MathOp request\n");
		read(ptcPipe[0], buffer, sizeof(MathOp));
		
		/* Once the buffer has been populated the struct's members can
		 * be accessed like normal.
		 */
		printf("Child: Recieved MathOp Request - Operands =(%f, %f)\n", 
			request->operand1, request->operand2);
		
		/* We execute the correct math operation based on the operatio
		 * member and store the result back into the same stuct.
		 */
		switch (request->operation) {
			case add:
				request->result = request->operand1 + request->operand2;
				break;
			case subtract:
				request->result = request->operand1 - request->operand2;
				break;
			case multiply:
				request->result = request->operand1 * request->operand2;
				break;
			case divide:
				request->result = request->operand1 / request->operand2;
				break;
		}
		
		/* Finally we write the contents of the buffer into the ctpPipe
		 * which sends the result back to the parent process.
		 */
		write(ctpPipe[1], buffer, sizeof(MathOp));
	}
	else {
		/* Only the parent process will execute this code. We close the 
		 * ptcPipe's read file handle and the ctpPipe's write file
		 * handle.
		 */
		close(ptcPipe[0]);
		close(ctpPipe[1]);
		
		/* Once again we create a buffer to store any recieved messages
		 * and a point to allow easy access to each of the MathOp 
		 * members.
		 */
		char buffer[sizeof(MathOp)];
		MathOp *result = (MathOp*)buffer;
		
		/* We create a new MathOp request and populate its values.
		 */
		MathOp request;
		request.operation = add;
		request.operand1 = 10;
		request.operand2 = 12;
		
		/* We sennd the request MathOp to the child by handing its
		 * address to the write function.
		 */
		printf("Parent: Sending MathOp request\n");
		write(ptcPipe[1], &request, sizeof(MathOp));
		
		/* And then we wait for a result to be returnd from the child.
		 */
		read(ctpPipe[0], buffer, sizeof(MathOp));
		
		/* Lastly we print the result*/
		printf("Parent: Result = %f", result->result);
	}
	return EXIT_SUCCESS;
}
