# C - Hash Table

## Introduction  

In computer science, a **Hash Table** is a data structure that implements an associative array, also known as a dictionary or map.  
An associative array is an abstract data type that maps keys to corresponding values.  
A **Hash Table** utilizes a **hash function** to compute an index, often referred to as a hash code, which points to a specific location in an array of buckets or slots where the desired value is stored.  

For more details, see the [Wikipedia page on Hash Tables](https://en.wikipedia.org/wiki/Hash_table).  

## FNV-1a Hash Function  

This library is based on the **FNV-1a** hash function, which is known for its simplicity and efficiency.  
The algorithm starts with an initial value called the *FNV offset basis*.  
For each byte in the input string, the hash value is first XORed with the byte and then multiplied by a constant known as the *FNV prime*.  
The **FNV-1a** variant differs from the original FNV function by reversing the order of the XOR and multiplication operations.  

For further reading, check the [Wikipedia page on FNV Hash](https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function).  

```c
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
```
