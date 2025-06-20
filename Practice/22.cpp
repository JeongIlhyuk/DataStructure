#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 10

int current_size = CAPACITY;

unsigned long hash(const char* str) { // djb2
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

typedef enum {
    EMPTY,
    FILLED,
    DELETED
} NodeState;

typedef struct {
    char* key;
    int value;
    unsigned long hash;
    NodeState state = EMPTY;
} Node;

Node* bucket = NULL;

void init_linear_table(const int size) {
    current_size = size;
    bucket = (Node*)calloc(current_size, sizeof(Node));
}

void linear_insert(const char* key, const int value) {
    const auto h = hash(key);
    const auto index = h % current_size;
    
    printf("Trying to insert %s at index %lu (hash: %lu)\n", key, index, h);
    
    for(int i = 0; i < current_size; i++){
        const auto try_idx = (index + i) % current_size;
        auto& b = bucket[try_idx];

        if(b.state != FILLED){
            b.key = (char *)malloc(strlen(key) + 1);
            if(!b.key){
                perror("malloc");
                return;
            }
            strcpy(b.key, key);
            b.value = value;
            b.hash = h;
            b.state = FILLED;
            return;
        }
    }
    printf("Table full (linear probing failed)\n");
}

int linear_get(const char* key) {
    const auto idx = hash(key) % current_size;

    for(int i = 0; i < current_size; i++){
        const auto try_idx = (idx + i) % current_size;
        const auto& b = bucket[try_idx];

        if(b.state == EMPTY) return -1;
        if(b.state == DELETED) continue;
        if(strcmp(b.key, key) == 0) return bucket[try_idx].value;
    }
}

void linear_remove(const char* key) {
    const auto idx = hash(key) % current_size;

    for(int i = 0; i < current_size; i++){
        const auto try_idx = (idx + i) % current_size;
        auto& b = bucket[try_idx];

        if(b.state == EMPTY) return;
        if(b.state == DELETED) continue;
        if(strcmp(b.key, key) == 0){
            free(b.key);
            b.state = DELETED;
            
            return;
        }
    }
}

void linear_rehash_table() {
    const auto new_size = current_size * 2;
    const auto& new_bucket = (Node *)calloc(new_size, sizeof(Node));

    if(!new_bucket){
        perror("calloc");
        return;
    }

    for(int i = 0; i < current_size; i++){
        if(bucket[i].state != FILLED) continue;

        const auto new_idx = bucket[i].hash % new_size;

        for(int j = 0; j < new_size; j++){
            const auto try_idx = (new_idx + j) % new_size;

            if(new_bucket[try_idx].state == EMPTY){
                new_bucket[try_idx] = bucket[i];
                break;
            }
        }
    }

    free(bucket);
    bucket = new_bucket;
    current_size = new_size;
    printf("Linear probing table rehashed to size %d\n", current_size);
}

void print_linear_table() {
    printf("[Table - Linear Probing with Tombstone]\n");
    for (int i = 0; i < current_size; i++) {
        printf("[%d] ", i);
        if (bucket[i].state == FILLED) {
            printf("FILLED  | %s => %d\n", bucket[i].key, bucket[i].value);
        }
        else if (bucket[i].state == DELETED) {
            printf("DELETED | <tombstone>\n");
        }
        else {
            printf("EMPTY   | \n");
        }

    }
}

int main() {
    printf("=== Hash Table with Linear Probing (with Tombstone) ===\n");
    init_linear_table(CAPACITY);
    linear_insert("coconut", 110);
    linear_insert("lime", 310);
    linear_insert("peas", 550);
    linear_insert("chicken", 400);

    linear_remove("lime");
    linear_remove("peas");

    print_linear_table();

    printf("Price of chicken: %d\n", linear_get("chicken"));

    linear_insert("apricot", 1310);

    print_linear_table();

    printf("Price of chicken: %d\n", linear_get("chicken"));


    linear_rehash_table();

    //    print_linear_table();

    return 0;
}