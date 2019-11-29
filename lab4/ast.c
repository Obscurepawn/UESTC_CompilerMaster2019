#include "ast.h"

char *OperaTor[] = {
	"<",
	">",
	"=",
	">=",
	"<=",
	"==",
	"+",
	"-",
	"*",
	"/",
	":=",
	"+=",
	"/=",
	"-=",
	"*="};

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

ptrast getLastNode(ptrast root)
{
	while (root->next != NULL)
		root = root->next;
	return root;
}

ptrast newListNode(ptrast next, ptrast now)
{
	ptrast temp = getLastNode(now);
	temp->next = next;
	return now;
}

ptrast newIfNode(char *nodetype, ptrast judge_exp, ptrast if_do_statement, ptrast else_do_statement)
{
	ptr_if_statement NewNode = (ptr_if_statement)malloc(sizeof(if_statement));
	if (!NewNode)
		return NULL;
	NewNode->nodetype = nodetype;
	NewNode->judge_exp = judge_exp;
	NewNode->else_do_statement = else_do_statement;
	NewNode->if_do_statement = if_do_statement;
	NewNode->next = NULL;
	return (ptrast)NewNode;
}

int checkOperator(ptrast root)
{
	for (int i = 0; i < 12; ++i)
		if (!strcmp(root->nodetype, OperaTor[i]))
			return i;
	return -1;
}

void produceSpace(int depth)
{
	for (int i = 0; i < depth * 2; ++i)
		printf(" ");
}

void DecDefPrint(int depth, ptrast root, char *content_title)
{
	printf("%s:", root->nodetype);
	puts("");
	produceSpace(depth + 1);
	printf("%s:%s\n", content_title, root->content);
}

void showAst(ptrast root, int depth)
{
	if (root == NULL)
		return;
	else
	{
		produceSpace(depth);
		if (!strcmp(root->nodetype, "Number"))
			printf("%s:%d\n", root->nodetype, root->value);
		else if (!strcmp(root->nodetype, "FunctionDef"))
			DecDefPrint(depth, root, "ReturnType");
		else if (checkOperator(root) != -1)
			printf("Operator:%s\n", root->nodetype);
		else if (!strcmp(root->nodetype, "VariableDec"))
			DecDefPrint(depth, root, "VariableType");
		else if (!strcmp(root->nodetype, "IF_Stmt"))
		{
			ptr_if_statement temp = (ptr_if_statement)root;
			ptrast judge_exp = temp->judge_exp;
			ptrast if_do_statement = temp->if_do_statement;
			ptrast else_do_statement = temp->else_do_statement;
			printf("IF_Stmt:\n");
			showAst(judge_exp, depth + 1);
			showAst(if_do_statement, depth + 3);
			produceSpace(depth);
			printf("Else:\n");
			showAst(else_do_statement, depth + 3);
			showAst(temp->next,depth);
			return;
		}
		else
		{
			printf("%s:", root->nodetype);
			if (root->content)
				printf("%s\n", root->content);
			else
				puts("");
		}
		showAst(root->left, depth + 1);
		showAst(root->right, depth + 1);
	}
	showAst(root->next, depth);
	return;
}

void freeAst(ptrast root)
{
	if (!root)
		return;
	freeAst(root->next);
	freeAst(root->left);
	freeAst(root->right);
	free(root->content);
	free(root->nodetype);
	free(root);
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
