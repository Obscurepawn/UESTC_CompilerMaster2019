#ifndef HASHMAP_H
#define HASHMAP_H

typedef struct HashTable HashTable;

// Symbol
typedef struct Symbol
{
    char serial[10];
    int value;
    char type[10];
    char string[300];
    char name[100];
} sb, *ptrSb;

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
    struct HashTable *last;
} ht, *ptrHt;

typedef struct HashStack
{
    ptrHt now;
    ptrHt global;
} hs, *ptrhs;

typedef struct strRecord
{
    char string[300];
    struct strRecord *next;
} sr, *ptrSr;

typedef struct strTable
{
    ptrSr *table;
} st, *ptrSt;

/* new an instance of HashTable */
HashTable *hash_table_new();

/*
delete an instance of HashTable,
all values are removed automatically.
*/
void hash_table_delete(HashTable *ht);

/*
add or update a value to ht, 
free_value(if not NULL) is called automatically when the value is removed.
return 0 if success, -1 if error occurred.
*/
int hash_table_put(HashTable *ht, char *key, void *value, void (*free_value)(void *));

/* get a value indexed by key, return NULL if not found. */
void *hash_table_get(HashTable *ht, char *key);

/* remove a value indexed by key */
void hash_table_rm(HashTable *ht, char *key);

void symbol_push(ptrhs SymbolTable, ptrSb symbol);

void *symbol_get(ptrhs SymbolTable, char *key);

void hash_stack_pop(ptrhs SymbolTable);

int hash_stack_subScope(ptrhs SymbolTable);

ptrhs hash_stack_new();

ptrSt hash_str_table_new();

void hash_str_table_delete(ptrSt sample);

void string_push(ptrSt sample, ptrSr str);

int string_check(ptrSt sample, char *str);

#endif