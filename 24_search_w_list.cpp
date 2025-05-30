#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* head = NULL;
Node* tail = NULL;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append(int data) {
    Node* new_node = create_node(data);
    if (!head) {
        head = tail = new_node;
        return;
    }
    tail->next = new_node;
    tail = new_node;
}

void print_list(Node* node) {
    while (node) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// Linear search
Node* linear_search(Node* node, int key) {
    while (node) {
        if (node->data == key) return node;
        node = node->next;
    }
    return NULL;
}

// Sentinel linear search (insert sentinel node at the end)
Node* sentinel_linear_search(Node* head, int key) {
    if (!head) return NULL;
    Node* sentinel = create_node(key);
    tail->next = sentinel;

    Node* curr = head;
    while (curr->data != key) {
        curr = curr->next;
    }

    tail->next = NULL;
    free(sentinel);

    return (curr == sentinel) ? NULL : curr;
}

// Print search result
void print_result(Node* result) {
    if (result) printf("Found: %d\n", result->data);
    else printf("Not found\n");
}

int main() {
    for (int i = 0; i < 100000; i++) append(i * 2);

    int key = 100000;
    printf("Searching for key: %d\n\n", key);

    clock_t start, end;
    double time_taken = 0;
    Node* result = NULL;

    // Repeat multiple times to improve measurement resolution
    int trials = 10;

    // Linear Search Timing
    start = clock();
    for (int i = 0; i < trials; i++) {
        result = linear_search(head, key);
    }
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC / trials;
    printf("Linear Search: ");
    print_result(result);
    printf("Average time taken (over %d trials): %.9f seconds\n\n", trials, time_taken);

    // Sentinel Linear Search Timing
    start = clock();
    for (int i = 0; i < trials; i++) {
        result = sentinel_linear_search(head, key);
    }
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC / trials;
    printf("Sentinel Linear Search: ");
    print_result(result);
    printf("Average time taken (over %d trials): %.9f seconds\n\n", trials, time_taken);

    return 0;
}
