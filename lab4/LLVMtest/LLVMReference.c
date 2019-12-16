#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int e;
char *v = "ccc";

char *tteesst()
{
	char *a = malloc(100);
	strcpy(a,"kkkkkk");
	return a;
}

char *Strcat(char *head,char *tail)
{
	char *dest = malloc(strlen(head)+strlen(tail));
	strcat(dest,head);
	strcat(dest,tail);
	return dest;
}

int main(int argc,char *argv[])
{
	// static int d = 0;
	// double x = 0;
	// int k = 0;
	// int kkkkk = 1;
	// int bbbbb = 2;
	// int yyyyyyyy = kkkkk/bbbbb;
	// int ccccc = kkkkk + bbbbb;
	// ccccc = kkkkk;
	// ccccc = 1;
	// ccccc = kkkkk + bbbbb;
	// ccccc /= kkkkk;
	// //int yyyyyy = 1;
	int oooooo = 888+12;
	char *b = "ccc";
	char *c;
	c = b;
	char *a;
	a = tteesst();
	strcat(a,a);
	// char *b = "bbb";
	// char *c = (char*)malloc(strlen(a)+strlen(b));
	// strcat(c,a);
	// strcat(c,b);
	// printf("%s\n",c);
 	//free(c);
	return 8;
}

// int test()
// {
// 	char a[10] = "aaaaaaaaaa";
// 	return 0;
// }

// char *TEST(char *temp)
// {
// 	char *kkk = temp;
// 	char *aaa = kkk;
// 	return kkk;
// }