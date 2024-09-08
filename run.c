#include <stdio.h>

int main(int argc, char *argv[]) {
	int x = 0;
	x = 3;
	if ((x) == (int)(x)) {
		printf("%d\n", (int)(x));
	} else {
		printf("%.6f\n", (double)(x));
	}
	return 0;
}
