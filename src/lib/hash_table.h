#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define TABLE_SIZE 256
#define FNV_OFFSET_BASIS 14695981039346656037U
#define FNV_PRIME 1099511628211U

typedef struct HashNode {
    char *key;
    int value;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode *buckets[TABLE_SIZE];
} HashTable;

HashTable *ht_create();

unsigned long ht_hash(const char *str, unsigned int table_size);
void ht_insert(HashTable *table, const char *key, int value);
int ht_search(HashTable *table, const char *key);
void ht_delete(HashTable *table, const char *key);
void ht_free(HashTable *table);

#endif
