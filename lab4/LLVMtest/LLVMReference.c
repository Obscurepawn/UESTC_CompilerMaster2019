#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int e;
char *v = "ccc";

int main(int argc,char *argv[])
{
	// static int d = 0;
	// double x = 0;
	// int k = 0;
	// int kkkkk = 1;
	// int bbbbb = 2;
	// int ccccc = kkkkk + bbbbb;
	char *a = malloc(strlen("aaa"));
	strcpy(a,"aaa");
	// char *b = "bbb";
	// char *c = (char*)malloc(strlen(a)+strlen(b));
	// strcat(c,a);
	// strcat(c,b);
	// printf("%s\n",c);
 	//free(c);
	return 8;
}

int test()
{
	char a[10] = "aaaaaaaaaa";
	return 0;
}

char *TEST(char *temp)
{
	char *kkk = temp;
	char *aaa = kkk;
	return kkk;
}