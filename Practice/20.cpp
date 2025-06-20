#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

#define CAPACITY 10
int current_capa = CAPACITY;

typedef struct {
    char* key;
    unsigned long hash;
    int value;
} Entry;

Entry* bucket[CAPACITY];

unsigned long _hash(const char* str) { // djb2
    unsigned long hash = 5381;
    int c;
    while(c = *str++)
        hash = (hash << 5) + hash + c;

    return hash;
}

void insert(const char* key, const int value) {
    const auto h = _hash(key);
    // const auto idx = h % current_capa;
    const auto idx = h % CAPACITY;
    printf("Inserting %s at index %lu (hash: %lu)\n", key, idx, h);
    if(bucket[idx]){
        printf("    Collision occurred at index %lu (no handling)\n", idx);
        return;
    }

    const auto entry = (Entry *)malloc(sizeof(Entry));
    if(!entry){
        perror("malloc");
        return;
    }

    entry->key = (char *)malloc(strlen(key) + 1);
    if(!entry->key){
        perror("malloc");
        return;
    }

    strcpy(entry->key, key);
    entry->hash = h;
    entry->value = value;
    bucket[idx] = entry;
}

int get(const char* key) {
    const auto h = _hash(key);
    const auto idx = h % current_capa;
    const auto b = bucket[idx];

    if(b && strcmp(b->key, key) == 0) return b->value;
    return -1;
}

void remove_entry(const char* key) {
    const auto h = _hash(key);
    const auto idx = h % current_capa;
    const auto b = bucket[idx];

    if(!b) return;
    if(strcmp(key, b->key) == 0){
        free(b->key);
        free(b);
        bucket[idx] = nullptr;
    }
}

void print_bucket() {
    printf("\n[Hash Table - No Collision Handling]\n");
    for (int i = 0; i < current_capa; i++) {
        if (bucket[i])
            printf("[%d] %s => %d\n", i, bucket[i]->key, bucket[i]->value);
        else
            printf("[%d] NULL\n", i);
    }
}

void rehash_bucket(int new_size) {
    const auto new_bucket = (Entry **)calloc(new_size, sizeof(Entry *));
    if(!new_bucket){
        perror("calloc");
        return;
    }
    
    for(const auto& b:bucket){
        if(b){
            unsigned long new_index = b->hash % new_size;
            new_bucket[new_index] = b;
        }
    }

    current_capa = new_size;

    memcpy(bucket, new_bucket, sizeof(Entry *) * new_size);
    free(new_bucket);
    printf("Bucket rehashed to new size: %d\n", new_size);
}

void free_bucket() {
    for(int i = 0; i < current_capa; i++)
        if(bucket[i]){
            free(bucket[i]->key);
            free(bucket[i]);
            bucket[i] = nullptr;
        }
}

int main() {
    printf("=== Hash Table without Collision Handling ===\n");
    insert("apple", 100);
    insert("banana", 80);
    insert("grape", 120);
    insert("melon", 90);
    insert("lemon", 95);

    print_bucket();

    printf("Price of apple: %d\n", get("apple"));
    printf("Price of melon: %d\n", get("melon"));
    remove_entry("banana");
    printf("Price of banana after removal: %d\n", get("banana"));

    printf("Rehashing...");
    rehash_bucket(25);
    insert("waterlemon", 250);
    print_bucket();

    free_bucket();

	return 0;
}