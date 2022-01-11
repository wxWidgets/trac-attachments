
#include <stdio.h>

const char *fmt = "( %d , %d , %d , %20c";
const char *to_parse = "(0, 0, 0, 0.000)";

int main()
{
	int r,g,b;
	char alphastr[100];
	
	int n = sscanf(to_parse, fmt, &r, &g, &b, alphastr);
	
	printf("item parsed = %d\n", n);

	return 0;
}