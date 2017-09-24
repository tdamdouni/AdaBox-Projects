#include <stdio.h>

int main() {
int a = 3;

for (int i=0; i < 16; i++) {
   printf("%d\n", a & 1000000000000000 ? 1:0);
   a  <<= 1;
}

return 0;
}

void getxy(int n, int w) {

	int x = n % w;
	int y = n / w; 
}