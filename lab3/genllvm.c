#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ast.h"

typedef struct LLVMQue CodeNode;
typedef struct QueHead qHead;

struct LLVMQue
{
	CodeNode *next;
	char *CodeContent;
};

struct QueHead
{
	CodeNode *FirstNode;
	CodeNode *LastNode;
};

void QueInit(qHead *head)
{
	head->FirstNode = NULL;
	head->LastNode = NULL;
	return;
}

char *strdup(char *Code)
{
	char *temp = malloc(strlen(Code));
	strcpy(temp, Code);
	return temp;
}

bool push(qHead *head, char *Code)
{
	if (head->FirstNode == NULL)
	{
		if (head->FirstNode = (CodeNode *)malloc(sizeof(CodeNode)))
		{
			head->FirstNode->CodeContent = strdup(Code);
			head->FirstNode->next = NULL;
			head->LastNode = head->FirstNode;
		}
		else
			return false;
	}
	else
	{
		if (head->LastNode->next = (CodeNode *)malloc(sizeof(CodeNode)))
		{
			CodeNode *new_last = head->LastNode->next;
			new_last->CodeContent = strdup(Code);
			new_last->next = NULL;
			head->LastNode = new_last;
		}
		else
			return false;
	}
}

char *pop(qHead *head)
{
	CodeNode *temp = head->FirstNode;
	head->FirstNode = head->FirstNode->next;
	char *code = strdup(temp->CodeContent);
	free(temp->CodeContent);
	free(temp);
	return code;
}

bool LLVM_Produce(ptrast root)
{
	if (root == NULL)
		return false;
	GenProgrammeNode(root);
}

bool GenProgrammeNode(ptrast root)
{
	if (root == NULL)
		return false;
	if (root->right)
		GenExternalDeclaration(root->right);
	else
	{
		printf("lack of the root->right for external_declaration\n");
		return false;
	}
	if (root->left)
		GenProgrammeNode(root->left);
	return true;
}

bool GenExternalDeclaration(ptrast root)
{
	if (root == NULL)
		return false;
	if (root->left == NULL)
	{
		printf("lack of the root->left for function_definition or declaration\n");
		return false;
	}
	else if (!strcmp(root->left->nodeType, "FunctionDefinition"))
		GenFunctionDefinition(root->left);
	else if (!strcmp(root->left->nodeType, "__list__"))
		GenDeclaration(root->left);
	else
	{
		printf("unknown nodetype\n");
		return false;
	}
	return true;
}

bool GenFunctionDefinition()
{
	
}
