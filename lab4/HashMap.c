#include "HashMap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TABLE_SIZE (1024*1024)

/* element of the hash table's chain list */
struct kv
{
    struct kv* next;
    char* key;
    void* value;
    void(*free_value)(void*);
};

/* HashTable */
struct HashTable
{
    struct kv ** table;
};

/* constructor of struct kv */
static void init_kv(struct kv* kv)
{
    kv->next = NULL;
    kv->key = NULL;
    kv->value = NULL;
    kv->free_value = NULL;
}
/* destructor of struct kv */
static void free_kv(struct kv* kv)
{
    if (kv) {
        if (kv->free_value) {
            kv->free_value(kv->value);
        }
        free(kv->key);
        kv->key = NULL;
        free(kv);
    }
}
/* the classic Times33 hash function */
static unsigned int hash_33(char* key)
{
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + hash + *key++;
    }
    return hash;
}

/* new a HashTable instance */
HashTable* hash_table_new()
{
    HashTable* ht = malloc(sizeof(HashTable));
    if (NULL == ht) {
        hash_table_delete(ht);
        return NULL;
    }
    ht->table = malloc(sizeof(struct kv*) * TABLE_SIZE);
    if (NULL == ht->table) {
        hash_table_delete(ht);
        return NULL;
    }
    memset(ht->table, 0, sizeof(struct kv*) * TABLE_SIZE);

    return ht;
}
/* delete a HashTable instance */
void hash_table_delete(HashTable* ht)
{
    if (ht) {
        if (ht->table) {
            int i = 0;
            for (i = 0; i<TABLE_SIZE; i++) {
                struct kv* p = ht->table[i];
                struct kv* q = NULL;
                while (p) {
                    q = p->next;
                    free_kv(p);
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
int hash_table_put2(HashTable* ht, char* key, void* value, void(*free_value)(void*))
{
    int i = hash_33(key) % TABLE_SIZE;
    struct kv* p = ht->table[i];
    struct kv* prep = p;

    while (p) { /* if key is already stroed, update its value */
        if (strcmp(p->key, key) == 0) {
            if (p->free_value) {
                p->free_value(p->value);
            }
            p->value = value;
            p->free_value = free_value;
            break;
        }
        prep = p;
        p = p->next;
    }

    if (p == NULL) {/* if key has not been stored, then add it */
        char* kstr = malloc(strlen(key) + 1);
        if (kstr == NULL) {
            return -1;
        }
        struct kv * kv = malloc(sizeof(struct kv));
        if (NULL == kv) {
            free(kstr);
            kstr = NULL;
            return -1;
        }
        init_kv(kv);
        kv->next = NULL;
        strcpy(kstr, key);
        kv->key = kstr;
        kv->value = value;
        kv->free_value = free_value;

        if (prep == NULL) {
            ht->table[i] = kv;
        }
        else {
            prep->next = kv;
        }
    }
    return 0;
}

/* get a value indexed by key */
void* hash_table_get(HashTable* ht, char* key)
{
    int i = hash_33(key) % TABLE_SIZE;
    struct kv* p = ht->table[i];
    while (p) {
        if (strcmp(key, p->key) == 0) {
            return p->value;
        }
        p = p->next;
    }
    return NULL;
}

/* remove a value indexed by key */
void hash_table_rm(HashTable* ht, char* key)
{
    int i = hash_33(key) % TABLE_SIZE;
	
    struct kv* p = ht->table[i];
    struct kv* prep = p;
    while (p) {
        if (strcmp(key, p->key) == 0) {
            free_kv(p);
            if (p == prep) {
                ht->table[i] = NULL;
            }
            else {
                prep->next = p->next;
            }
        }
        prep = p;
        p = p->next;
    }
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