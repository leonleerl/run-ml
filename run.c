#include <stdio.h>

int main(int argc, char *argv[]) {
	int a = 0;
	a = 10;
	double x = 0.0;
	x = 23.3;
	int y = 0;
	y = 30;
	double b = 0.0;
	b = 3.33333;
	if ((x + y) == (int)(x + y)) {
		printf("%d\n", (int)(x + y));
	} else {
		printf("%.6f\n", (double)(x + y));
	}
	if ((a + y) == (int)(a + y)) {
		printf("%d\n", (int)(a + y));
	} else {
		printf("%.6f\n", (double)(a + y));
	}
	if ((123213) == (int)(123213)) {
		printf("%d\n", (int)(123213));
	} else {
		printf("%.6f\n", (double)(123213));
	}
	if ((a + x + y - b) == (int)(a + x + y - b)) {
		printf("%d\n", (int)(a + x + y - b));
	} else {
		printf("%.6f\n", (double)(a + x + y - b));
	}
	return 0;
}
