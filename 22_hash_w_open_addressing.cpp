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
    NodeState state;
} Node;

Node* bucket = NULL;

void init_linear_table(int size) {
    current_size = size;
    bucket = (Node*)calloc(current_size, sizeof(Node));
    for (int i = 0; i < current_size; i++) {
        bucket[i].state = EMPTY;
    }
}

void linear_insert(const char* key, int value) {
    unsigned long h = hash(key);
    unsigned long index = h % current_size;
    printf("Trying to insert %s at index %lu (hash: %lu)\n", key, index, h);
    for (int i = 0; i < current_size; i++) {
        int try_idx = (index + i) % current_size;
        if (bucket[try_idx].state == EMPTY || bucket[try_idx].state == DELETED) {
            bucket[try_idx].key = (char*)malloc(strlen(key) + 1);
            if (bucket[try_idx].key != NULL) {
                strcpy(bucket[try_idx].key, key);
            }
            bucket[try_idx].value = value;
            bucket[try_idx].hash = h;
            bucket[try_idx].state = FILLED;
            return;
        }
    }
    printf("Table full (linear probing failed)\n");
}

int linear_get(const char* key) {
    unsigned long index = hash(key) % current_size;
    for (int i = 0; i < current_size; i++) {
        int try_idx = (index + i) % current_size;
        if (bucket[try_idx].state == EMPTY) break;
        if (bucket[try_idx].state == FILLED && strcmp(bucket[try_idx].key, key) == 0) {
            return bucket[try_idx].value;
        }
    }
    return -1;
}

void linear_remove(const char* key) {
    unsigned long index = hash(key) % current_size;
    for (int i = 0; i < current_size; i++) {
        int try_idx = (index + i) % current_size;
        if (bucket[try_idx].state == EMPTY) break;
        if (bucket[try_idx].state == FILLED && strcmp(bucket[try_idx].key, key) == 0) {
            free(bucket[try_idx].key);
            bucket[try_idx].state = DELETED;
            return;
        }
    }
}

void linear_rehash_table() {
    int new_size = current_size * 2;
    Node* new_table = (Node*)calloc(new_size, sizeof(Node));
    for (int i = 0; i < new_size; i++) new_table[i].state = EMPTY;

    for (int i = 0; i < current_size; i++) {
        if (bucket[i].state == FILLED) {
            unsigned long index = bucket[i].hash % new_size;
            for (int j = 0; j < new_size; j++) {
                int try_idx = (index + j) % new_size;
                if (new_table[try_idx].state == EMPTY) {
                    new_table[try_idx] = bucket[i];
                    break;
                }
            }
        }
    }
    free(bucket);
    bucket = new_table;
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