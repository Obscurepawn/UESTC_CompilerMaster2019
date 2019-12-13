#include "HashMap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TABLE_SIZE (1024 * 1024)
#define MAX_NAME 255
#define show_symbol(p) printf("serial:%s,value:%d,string:%s,name:%s,type:%s\n",p->serial,p->value,p->string,p->name,p->type)

int tabNum = 0;
extern void tabSpace();

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
    ht->last = NULL;
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
int hash_table_put(HashTable *ht, char *key, void *value, void (*free_value)(void *))
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

ptrhs hash_stack_new()
{
    ptrhs hashStack = malloc(sizeof(hs));
    if(!hashStack)
        return NULL;
    ptrHt globalSymTable = hash_table_new();
    if(!globalSymTable)
        return NULL;
    globalSymTable->last = NULL;
    hashStack->global = globalSymTable;
    hashStack->now = globalSymTable;
    return hashStack;
}

int hash_stack_subScope(ptrhs SymbolTable)
{
    ptrHt subScopeSymTable = hash_table_new();
    if(!subScopeSymTable)
        return -1;
    subScopeSymTable->last = SymbolTable->now;
    SymbolTable->now = subScopeSymTable;   
    tabNum++;
    tabSpace();
    return 0;
}

void hash_stack_pop(ptrhs SymbolTable)
{
    ptrHt temp = SymbolTable->now->last;
    hash_table_delete(SymbolTable->now);
    SymbolTable->now = temp;
    tabNum--;
    tabSpace();
}

void* symbol_get(ptrhs SymbolTable,char *key)
{
    ptrHt temp = SymbolTable->now;
    ptrSb symbol;
    while (temp)
    {
        if(symbol = hash_table_get(temp,key))
            return symbol;
        else 
            temp = temp->last;
    }
    return NULL;
}

void  symbol_push(ptrhs SymbolTable,ptrSb symbol)
{
    if(!symbol||!symbol->name)
        return;
    hash_table_put(SymbolTable->now,symbol->name,symbol,free);
    return;
}




// // 要放入哈希表中的结构体
// struct Student
// {
//     int age;
//     float score;
//     char name[32];
//     char data[1024 * 1024* 10];
// };

// // 结构体内存释放函数
// static void free_student(void* stu)
// {
//     free(stu);
// }

// // 显示学生信息的函数
// static void show_student(struct Student* p)
// {
//     printf("姓名:%s, 年龄:%d, 学分:%.2f\n", p->name, p->age, p->score);
// }

// int main()
// {
//     // 新建一个HashTable实例
//     HashTable* ht = hash_table_new();
//     if (NULL == ht) {
//         return -1;
//     }

//     // 向哈希表中加入多个学生结构体
//     for (int i = 0; i < 100; i++) {
//         struct Student * stu = (struct Student*)malloc(sizeof(struct Student));
//         stu->age = 18 + rand()%5;
//         stu->score = 50.0f + rand() % 100;
//         sprintf(stu->name, "同学%d", i);
//         hash_table_put2(ht, stu->name, stu, free_student);
//     }

//     // 根据学生姓名查找学生结构
//     for (int i = 0; i < 100; i++) {
//         char name[32];
//         sprintf(name, "同学%d", i);
//         struct Student * stu = (struct Student*)hash_table_get(ht, name);
//         show_student(stu);
//     }

//     // 销毁哈希表实例
//     hash_table_delete(ht);
//     return 0;
// }