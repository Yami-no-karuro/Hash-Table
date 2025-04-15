#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

/**
 * Creates and initializes a new hash table.
 *
 * @param size - The initial size of the hash table.
 * @return - A pointer to the newly allocated HashTable.
 */
HashTable *ht_create(int size) 
{
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    if (!table) {
        printf("Error: Unable to allocate memory for a new \"HashTable\" entry.\n");
        exit(EXIT_FAILURE);
    }

    table->buckets = (HashNode **)calloc(size, sizeof(HashNode *));
    table->size = size;
    table->count = 0;

    return table;
}

/**
 * Resizes the hash table to a new size and rehashes all elements.
 *
 * @param table - The hash table to resize.
 * @param new_size - The new size for the table.
 */
void ht_resize(HashTable *table, int new_size) 
{
    HashNode **old_buckets = table->buckets;
    int old_size = table->size;

    table->buckets = (HashNode **)calloc(new_size, sizeof(HashNode *));
    table->size = new_size;
    table->count = 0;

    for (int i = 0; i < old_size; i++) {
        HashNode *node = old_buckets[i];
        while (node) {
            ht_insert(table, node->key, node->value);
            HashNode *temp = node;
            node = node->next;

            free(temp->key);
            free(temp);
        }
    }

    free(old_buckets);
}

/**
 * Inserts a key-value pair into the hash table. If the key already exists, updates its value.
 * Automatically resizes the table if load factor exceeds 0.7.
 *
 * @param table - The hash table where the key-value pair should be inserted.
 * @param key - The key associated with the value.
 * @param value - The integer value to be stored.
 */
void ht_insert(HashTable *table, const char *key, int value) 
{
    if ((float)table->count / table->size > 0.7f)
        ht_resize(table, table->size * 2);

    unsigned int index = ht_hash(key, table->size);
    HashNode *node = table->buckets[index];

    while (node) {
        if (strcmp(node->key, key) == 0) {
            node->value = value;
            return;
        }

        node = node->next;
    }

    HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));
    if (!new_node) {
        printf("Error: Unable to allocate memory for a new \"HashNode\" entry.\n");
        exit(EXIT_FAILURE);
    }

    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = table->buckets[index];

    table->buckets[index] = new_node;
    table->count++;
}

/**
 * Deletes a key-value pair from the hash table.
 *
 * @param table - The hash table from which the key-value pair should be removed.
 * @param key - The key to be deleted.
 */
void ht_delete(HashTable *table, const char *key) 
{
    unsigned int index = ht_hash(key, table->size);
    HashNode *current = table->buckets[index];
    HashNode *prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                table->buckets[index] = current->next;
            }

            free(current->key);
            free(current);

            table->count--;
            return;
        }

        prev = current;
        current = current->next;
    }
}

/**
 * Frees the memory used by the hash table and all its nodes.
 *
 * @param table - The hash table to free.
 */
void ht_free(HashTable *table) 
{
    for (int i = 0; i < table->size; i++) {
        HashNode *current = table->buckets[i];
        while (current) {
            HashNode *temp = current;
            current = current->next;

            free(temp->key);
            free(temp);
        }
    }

    free(table->buckets);
    free(table);
}

/**
 * Searches for a key in the hash table and retrieves its associated value.
 *
 * @param table - The hash table to search in.
 * @param key - The key whose associated value is to be retrieved.
 * @return - The value associated with the key, or -1 if the key is not found.
 */
int ht_search(HashTable *table, const char *key) 
{
    unsigned int index = ht_hash(key, table->size);
    HashNode *current = table->buckets[index];

    while (current) {
        if (strcmp(current->key, key) == 0)
            return current->value;

        current = current->next;
    }

    return -1;
}

/**
 * Computes the hash value of a given string using the FNV-1a hash function.
 *
 * @param str - The input string to be hashed.
 * @param table_size - The size of the hash table.
 * @return - The computed hash value modulo the table size.
 */
unsigned long ht_hash(const char *str, unsigned int table_size) 
{
    int c;
    unsigned long hash = FNV_OFFSET_BASIS;

    while ((c = *str++)) {
        hash ^= c;
        hash *= FNV_PRIME;
    }

    return hash % table_size;
}
