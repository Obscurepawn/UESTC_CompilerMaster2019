<<<<<<< HEAD
#ifndef AST_C_
#define AST_C_
#include "ast.h"

ptrast CreateNewAstNode(char *content, char *nodeType, ptrast left, ptrast right)
{
	ptrast NewNode = (ptrast)malloc(sizeof(ast));
	NewNode->content = content;
	NewNode->nodeType = nodeType;
	NewNode->left = left;
	NewNode->right = right;
	return NewNode;
}

void ShowAst(ptrast root, int depth)
{
	if (root == NULL)
		return;
	if (!strcmp(root->nodeType, "__list__"))
	{
		ShowAst(root->left, depth);
		ShowAst(root->right, depth);
	}
	else
	{
		for (int i = 0; i < depth * 2; ++i)
			printf(" ");
		printf("%s:%s\n", root->nodeType, root->content);
		ShowAst(root->left, depth + 1);
		ShowAst(root->right, depth + 1);
	}
	return;
}

void FreeAst(ptrast root)
{
	if (!root)
		return;
	FreeAst(root->left);
	FreeAst(root->right);
	free(root->content);
	free(root->nodeType);
	free(root);
	return;
}

=======
#ifndef AST_C_
#define AST_C_
#include "ast.h"

ptrast CreateNewAstNode(char *content, char *nodeType, ptrast left, ptrast right)
{
	ptrast NewNode = (ptrast)malloc(sizeof(ast));
	NewNode->content = content;
	NewNode->nodeType = nodeType;
	NewNode->left = left;
	NewNode->right = right;
	return NewNode;
}

void ShowAst(ptrast root, int depth)
{
	if (root == NULL)
		return;
	if (!strcmp(root->nodeType, "__list__"))
	{
		ShowAst(root->left, depth);
		ShowAst(root->right, depth);
	}
	else
	{
		for (int i = 0; i < depth * 2; ++i)
			printf(" ");
		printf("%s:%s\n", root->nodeType, root->content);
		ShowAst(root->left, depth + 1);
		ShowAst(root->right, depth + 1);
	}
	return;
}

void FreeAst(ptrast root)
{
	if (!root)
		return;
	FreeAst(root->left);
	FreeAst(root->right);
	free(root->content);
	free(root->nodeType);
	free(root);
	return;
}

>>>>>>> 8dad9ee129215d834500947d610d65c5aead218d
#endif 