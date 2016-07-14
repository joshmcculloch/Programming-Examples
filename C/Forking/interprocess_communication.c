#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef enum {add, subtract, multiply, divide} MathOperations;

typedef struct {
	MathOperations operation;
	double operand1;
	double operand2;
	double result;
} MathOp;

int main(void) {
	int ptcPipe[2];
	int ctpPipe[2];
	
	if (pipe(ptcPipe)) {
		printf("Error creating parent to child pipe: %d", errno);
	}
	
	if (pipe(ctpPipe)) {
		printf("Error creating child to parent pipe: %d", errno);
	}
	
	if (fork() == 0 ) {
		
		printf("I am the child\n");
		close(ptcPipe[1]);
		close(ctpPipe[0]);
		char buffer[sizeof(MathOp)];
		read(ptcPipe[0], buffer, sizeof(MathOp));
		MathOp *request = (MathOp*)buffer;
		printf("Operand %f and %f\n", request->operand1, request->operand2);
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
		
		write(ctpPipe[1], buffer, sizeof(MathOp));
	}
	else {
		char buffer[sizeof(MathOp)];
		printf("I am the parent\n");
		close(ptcPipe[0]);
		close(ctpPipe[1]);
		MathOp request;
		request.operation = add;
		request.operand1 = 10;
		request.operand2 = 12;
		write(ptcPipe[1], &request, sizeof(MathOp));
		read(ctpPipe[0], buffer, sizeof(MathOp));
		MathOp *result = (MathOp*)buffer;
		printf("Result: %f", result->result);
	}
	return EXIT_SUCCESS;
}
