#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

#define CAPACITY 10
int current_capa = CAPACITY;

typedef struct {
    char* key;
    int value;
    int hash;
} Entry;

Entry* bucket[CAPACITY];

unsigned long _hash(const char* str) { // djb2
    int hash = 5381;
    while(auto c = *str++){
        hash = hash << 5 + hash + c;
    }
    return hash;
}

void insert(const char* key, int value) {
    const auto hash = _hash(key);
    const auto idx = hash % CAPACITY;
    printf("Inserting %s at index %lu (hash: %lu)\n", key, idx, hash);
    if(bucket[idx]){
        printf("    Collision occurred at index %lu (no handling)\n", idx);
        return;
    }
    const auto entry = (Entry *)malloc(sizeof(Entry));
    if(!entry){
        perror("malloc");
        return;
    }

    entry->key = (char*)malloc(strlen(key) + 1);
    if(!entry->key){
        perror("malloc");
        free(entry);
        return;
    }
    strcpy(entry->key, key);
    entry->value = value;
    bucket[idx] = entry;
}

int get(const char* key) {

}

void remove_entry(const char* key) {

}

void print_bucket() {

}

void rehash_bucket(int new_size) {

}

void free_bucket() {

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