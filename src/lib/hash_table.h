#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define FNV_OFFSET_BASIS 14695981039346656037U
#define FNV_PRIME 1099511628211U

typedef struct HashNode {
    char *key;
    int value;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode **buckets;
    int size;
    int count;
} HashTable;

typedef void (*ht_callback)(const char *key, int value, void *user_data);

HashTable *ht_create(int size);

void ht_resize(HashTable *table, int new_size);
void ht_insert(HashTable *table, const char *key, int value);
void ht_delete(HashTable *table, const char *key);
void ht_free(HashTable *table);
int ht_search(HashTable *table, const char *key);

unsigned long ht_hash(const char *str, unsigned int table_size);

void ht_foreach(HashTable *table, ht_callback callback, void *user_data);

#endif
