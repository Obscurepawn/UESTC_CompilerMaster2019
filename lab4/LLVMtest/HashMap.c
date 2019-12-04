#include "HashMap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TABLE_SIZE (1024 * 1024)
#define MAX_NAME 255
#define show_symbol(p); printf("serial:%d,value:%d,string:%s,name:%s,nameSpace:%s\n",p->serial,p->value,p->string,p->name,p->nameSpace);
/* element of the hash table's chain list */
typedef struct SubHashTable
{
    struct SubHashTable *next;
    char *key;
    void *value;
    void (*free_value)(void *);
} sht, *ptrSht;

/* HashTable */
typedef struct HashTable
{
    sht **table;
} ht, *ptrHt;

/* constructor of sht */
void init_subTable(ptrSht subTable)
{
    subTable->next = NULL;
    subTable->key = NULL;
    subTable->value = NULL;
    subTable->free_value = NULL;
}
/* destructor of sht */
void free_subTable(ptrSht subTable)
{
    ptrSht now = subTable;
    ptrSht next = subTable->next;
    if (next)
    {
        if (now->free_value)
            now->free_value(subTable->value);
        free(now->key);
        now->key = NULL;
        free(now);
        now = next;
        next = next->next;
    }
}
/* the classic Times33 hash function */
unsigned int hash_33(char *key)
{
    unsigned int hash = 0;
    //do %d times-->%d:the length of the char *key
    while (*key)
        hash = (hash << 5) + hash + *key++;
    return hash;
}

/* new a HashTable instance */
HashTable *hash_table_new()
{
    HashTable *ht = malloc(sizeof(HashTable));
    if (NULL == ht)
    {
        hash_table_delete(ht);
        return NULL;
    }
    ht->table = malloc(sizeof(ptrSht) * TABLE_SIZE);
    if (NULL == ht->table)
    {
        hash_table_delete(ht);
        return NULL;
    }
    memset(ht->table, 0, sizeof(ptrSht) * TABLE_SIZE);
    return ht;
}

/* delete a HashTable instance */
void hash_table_delete(ptrHt ht)
{
    if (ht)
    {
        if (ht->table)
        {
            int i = 0;
            for (i = 0; i < TABLE_SIZE; i++)
            {
                ptrSht p = ht->table[i];
                ptrSht q = NULL;
                while (p)
                {
                    q = p->next;
                    free_subTable(p);
                    p = q;
                }
            }
            free(ht->table);
            ht->table = NULL;
        }
        free(ht);
    }
}

/* insert or update a value indexed by key */
int hash_table_put2(HashTable *ht, char *key, void *value, void (*free_value)(void *))
{
    int i = hash_33(key) % TABLE_SIZE;
    ptrSht p = ht->table[i];
    ptrSht prep = p;

    while (p)
    { /* if key is already stroed, update its value */
        if (strcmp(p->key, key) == 0)
        {
            if (p->free_value)
            {
                p->free_value(p->value);
            }
            p->value = value;
            p->free_value = free_value;
            break;
        }
        prep = p;
        p = p->next;
    }

    if (p == NULL)
    { /* if key has not been stored, then add it */
        char *kstr = malloc(strlen(key) + 1);
        if (kstr == NULL)
        {
            return -1;
        }
        ptrSht kv = malloc(sizeof(sht));
        if (NULL == kv)
        {
            free(kstr);
            kstr = NULL;
            return -1;
        }
        init_subTable(kv);
        kv->next = NULL;
        strcpy(kstr, key);
        kv->key = kstr;
        kv->value = value;
        kv->free_value = free_value;

        if (prep == NULL)
        {
            ht->table[i] = kv;
        }
        else
        {
            prep->next = kv;
        }
    }
    return 0;
}

/* get a value indexed by key */
void *hash_table_get(HashTable *ht, char *key)
{
    int i = hash_33(key) % TABLE_SIZE;
    ptrSht p = ht->table[i];
    while (p)
    {
        if (strcmp(key, p->key) == 0)
        {
            return p->value;
        }
        p = p->next;
    }
    return NULL;
}

/* remove a value indexed by key */
void hash_table_rm(HashTable *ht, char *key)
{
    int i = hash_33(key) % TABLE_SIZE;

    ptrSht p = ht->table[i];
    ptrSht prep = p;
    while (p)
    {
        if (strcmp(key, p->key) == 0)
        {
            free_subTable(p);
            if (p == prep)
            {
                ht->table[i] = NULL;
            }
            else
            {
                prep->next = p->next;
            }
        }
        prep = p;
        p = p->next;
    }
}

// 要放入哈希表中的结构体
typedef struct Symbol
{
    int serial;
    int value;
    char *string;
    char *name;
    char *nameSpace;
} st, *ptrSt;

// free the space occupied by the Table
void free_symbol(ptrSt SymbolTable)
{
    if (SymbolTable->string)
        free(SymbolTable->string);
    if (SymbolTable->name)
        free(SymbolTable->name);
    if (SymbolTable->name)
        free(SymbolTable->name);
    if (SymbolTable->nameSpace)
        free(SymbolTable->nameSpace);
    free(SymbolTable);
    return;
}

// int main()
// {
//     // 新建一个HashTable实例
//     HashTable *ht = hash_table_new();
//     if (NULL == ht)
//     {
//         return -1;
//     }

//     // 向哈希表中加入多个学生结构体
//     for (int i = 0; i < 100; i++)
//     {
//         struct Student *stu = (struct Student *)malloc(sizeof(struct Student));
//         stu->age = 18 + rand() % 5;
//         stu->score = 50.0f + rand() % 100;
//         sprintf(stu->name, "同学%d", i);
//         hash_table_put2(ht, stu->name, stu, free_student);
//     }

//     // 根据学生姓名查找学生结构
//     for (int i = 0; i < 100; i++)
//     {
//         char name[32];
//         sprintf(name, "同学%d", i);
//         struct Student *stu = (struct Student *)hash_table_get(ht, name);
//         show_student(stu);
//     }

//     // 销毁哈希表实例
//     hash_table_delete(ht);
//     return 0;
// }