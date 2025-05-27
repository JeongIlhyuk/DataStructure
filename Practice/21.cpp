#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 10

int current_capa = CAPACITY;

unsigned long hash(const char* str) { // djb2
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

typedef struct Node {
    char* key;
    int value;
    unsigned long hash;
    Node* next;
} Node;

Node** bucket = nullptr;

void init_bucket(int size) {
    current_capa = size;
    bucket = (Node**)calloc(size, sizeof(Node*));
}

void chain_insert(const char* key, int value) {
    const auto h = hash(key);
    const auto index = h % current_capa;

    printf("Trying to insert %s at index %lu (hash: %lu)\n", key, index, h);
    Node* new_node = (Node*)malloc(sizeof(Node));   // ✅ 구조체 전체 크기 할당
    if(!new_node){
        perror("malloc");
        return;
    }
    new_node->key = (char*)malloc(strlen(key) + 1);
    if(!new_node->key){
        perror("malloc");
        free(new_node);
        return;
    }
    strcpy(new_node->key, key);
    new_node->value = value;
    new_node->hash = h;
    new_node->next = bucket[index];
    bucket[index] = new_node;
}

int chain_get(const char* key) {
    auto curr = bucket[hash(key) % current_capa];
    while(curr){
        if(strcmp(curr->key, key) == 0) return curr->value;
        curr = curr->next;
    }
    return -1;
}

void chain_remove(const char* key) {
    const auto index = hash(key) % current_capa;
    Node *curr = bucket[index], *prev = nullptr;
    while(curr){
        if(strcmp(key, curr->key) == 0){
            if(prev) prev->next = curr->next;
            else bucket[index] = curr->next;
            free(curr->key);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void print_chain_bucket() {
    printf("\n[Bucket - Chaining]\n");
    for (int i = 0; i < current_capa; i++) {
        printf("[%d] ", i);
        Node* curr = bucket[i];
        while (curr) {
            printf("(%s:%d) -> ", curr->key, curr->value);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

// Rehashing for Chaining
void chain_rehash_bucket() {
    const int new_size = current_capa * 1.3;
    const auto new_bucket = (Node**)calloc(new_size, sizeof(Node*));

    for(int i = 0; i < current_capa; i++){
        auto curr = bucket[i];
        while(curr){
            const auto next = curr->next;
            const auto index = curr->hash % new_size;
            curr->next = new_bucket[index];
            new_bucket[index] = curr;
            curr = next;
        }
    }
    free(bucket);
    bucket = new_bucket;
    current_capa = new_size;

    printf("Chaining bucket rehashed to size %d\n", current_capa);
}

void free_chain_bucket() {
    for(int i = 0; i < current_capa; i++){
        auto curr = bucket[i];
        while(curr){
            const auto next = curr->next;
            free(curr->key);
            free(curr);
            curr = next;
        }
    }
    free(bucket);
    bucket = nullptr;
}

int main() {
    printf("=== Hash Table with Chaining ===\n");
    init_bucket(CAPACITY);
    chain_insert("apple", 100);
    chain_insert("banana", 80);
    chain_insert("grape", 120);
    chain_insert("melon", 90);
    chain_insert("lemon", 95);

    print_chain_bucket();

    printf("Price of lemon: %d\n", chain_get("lemon"));

    chain_rehash_bucket();

    print_chain_bucket();

    free_chain_bucket();

    return 0;
}