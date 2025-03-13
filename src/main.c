#include <stdio.h>

#include "lib/hash_table.h"

int main() {
    HashTable *table = ht_create();

    ht_insert(table, "foo", 1);
    ht_insert(table, "bar", 2);

    printf("foo: %d\n", ht_search(table, "foo"));
    printf("bar: %d\n", ht_search(table, "bar"));

    ht_free(table);
    return 0;
}

