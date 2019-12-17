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

char *StrAssign(int InitFlag,int tempFlag,char *lvalue,char *rvalue)
{
	if(tempFlag)
	{
		if(InitFlag)
			free(lvalue);
		return rvalue;
	}
	if(!InitFlag)
		lvalue = malloc(strlen(rvalue));
	else if(InitFlag)
	{
		free(lvalue);
		lvalue = malloc(strlen(rvalue));
	}
	strcpy(lvalue,rvalue);
	return lvalue;
}

char *StrSum(char *head,char *tail)
{
	char *Dest = malloc(strlen(head)+strlen(tail));
	strcat(Dest,head);
	strcat(Dest,tail);
	return Dest;
}

int main(int argc,char *argv[])
{
	char *a = "aaa";
	char *b = malloc(4); 
	b = StrAssign(1,0,b,a);
	char *c = malloc(100);
	c = StrAssign(1,0,c,a);
	c[2] = b[0];
	int aaaaaa = 9;
	int bbbbbb = 1;
	int cccccc = aaaaaa/bbbbbb;
	//printf("%s\n",b);
	//b = StrSum(1,&b,a,"ccc");
	//printf("%s\n",b);
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
	// int oooooo = 888+12;
	// char *b = "ccc";
	// char *c;
	// c = b;
	// char *a;
	// a = tteesst();
	// strcat(a,a);
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

char *TEST(char *temp)
{
	char *kkk = temp;
	char *aaa = kkk;
	return kkk;
}