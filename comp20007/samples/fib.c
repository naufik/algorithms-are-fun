/**
 *
 * Fibonacci Numbers - COMP20007 Tutorial 1
 * Author: Naufal F. Setiawan
 * nauffik@gmail.com
 *
 */

#include <stdio.h>

int fib_rec(int n);
int fib_itr(int n);

int main(int argc, char **argv) {
	printf("Enter a positive integer: ");
	
	int z;
	scanf("%d", &z);
	
	printf("The %d-th Fibonacci number is %d.\n", z, fib_itr(z));
	return 0;
}

int fib_rec(int n) {
	if (n < 0) {
		return -1;
	} else {
		return n <= 1 ? n : fib_rec(n-1) + fib_rec(n-2);
	}
}

int fib_itr(int n) {
	if (n < 0) {
		return -1;
	}

	int a,b;
	a = 0;
	b = 1;

	for (int i = 0; i < n; ++i) {
		int c = a + b;
		a = b;
		b = c;
	}
	
	return b;
}
