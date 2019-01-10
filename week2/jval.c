#include <stdio.h>
#include <stdlib.h>
#include "jval.h"

int main(){
	Jval a, b;
	a = new_jval_i(5);
	b = new_jval_f(6.9);
	printf("%d\n", jval_i(a));
	printf("%f\n", jval_f(b));
}