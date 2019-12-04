#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int e;

int main()
{
	static int d = 0;
	double x = 0;
	int k = 0;
	char *a = "aaa";
	char *b = "bbb";
	char *c = (char*)malloc(strlen(a)+strlen(b));
	strcat(c,a);
	strcat(c,b);
	printf("%s\n",c);
 	//free(c);
	return 0;
}
char test()
{
	char a[10] = "aaaaaaaaaa";
	return a[6];
}