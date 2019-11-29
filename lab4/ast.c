#include "ast.h"

ptrast newAstNode(char *nodeType, char *content, int value, ptrast left, ptrast right)
{
	ptrast NewNode = (ptrast)malloc(sizeof(ast));
	NewNode->nodetype = nodeType;
	NewNode->content = content;
	NewNode->value = value;
	NewNode->left = left;
	NewNode->right = right;
	NewNode->next = NULL;
	return NewNode;
}

ptrast newListNode(ptrast now, ptrast next)
{
	next->next = now;
	ptrast temp = next;
	return temp;
}

ptrast newIfNode(char *nodetype, ptrast judge_exp, ptrast if_do_statement, ptrast else_do_statement)
{
	ptr_if_statement NewNode = (ptr_if_statement)malloc(sizeof(if_statement));
	if (!NewNode)
		return NULL;
	NewNode->nodetype = nodetype;
	NewNode->judge_exp = judge_exp;
	NewNode->else_do_statement = else_do_statement;
	return (ptrast)NewNode;
}

int checkOperator(ptrast root)
{
	for (int i = 0; i < 12; ++i)
		if (!strcmp(root->nodetype, Operator[i]))
			return i;
	return -1;
}

void produceSpace(int depth)
{
	for (int i = 0; i < depth * 2; ++i)
		printf(" ");
}

void showAst(ptrast root, int depth)
{
	if (root == NULL)
		return;
	produceSpace(depth);
	int checkFlag = checkOperator(root);
	if (checkFlag != -1)
	{
		printf("Operator:%s\n", root->nodetype);
		if (checkFlag <= 5)
		{
			produceSpace(depth);
			printf("VariableName:%s\n", root->content);
			showAst(root->left, depth);
			return;
		}
	}
	showAst(root->next, depth);
	showAst(root->left, depth);
	showAst(root->right, depth);
	return;
}

char *strdup(const char *s)
{
	if (!s)
		return NULL;
	size_t len = strlen(s) + 1;
	void *New = malloc(len);
	if (New == NULL)
		return NULL;
	return (char *)memcpy(New, s, len);
}
