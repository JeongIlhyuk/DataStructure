#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;

TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

void insert(TrieNode* root, const char* word) {
    TrieNode* curr = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL)
            curr->children[index] = createNode();
        curr = curr->children[index];
    }
    curr->isEndOfWord = true;
}

bool search(TrieNode* root, const char* word) {
    TrieNode* curr = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL)
            return false;
        curr = curr->children[index];
    }
    return curr->isEndOfWord;
}

bool isEmpty(TrieNode* root) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i]) return false;
    return true;
}

TrieNode* deleteWord(TrieNode* root, const char* word, int depth = 0) {
    if (!root) return NULL;

    if (word[depth] == '\0') {
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        if (isEmpty(root)) {
            free(root);
            return NULL;
        }
        return root;
    }

    int index = word[depth] - 'a';
    root->children[index] = deleteWord(root->children[index], word, depth + 1);

    if (isEmpty(root) && !root->isEndOfWord) {
        free(root);
        return NULL;
    }

    return root;
}

int main() {
    TrieNode* root = createNode();

    insert(root, "hello");
    insert(root, "hi");
    insert(root, "hill");

    printf("Search results:\n");
    printf("hi: %s\n", search(root, "hi") ? "Found" : "Not Found");
    printf("hill: %s\n", search(root, "hill") ? "Found" : "Not Found");
    printf("hive: %s\n", search(root, "hive") ? "Found" : "Not Found");

    printf("\nInsert hive:\n");
    insert(root, "hive");
    printf("hive: %s\n", search(root, "hive") ? "Found" : "Not Found");

    deleteWord(root, "hi");
    printf("\nDelete hi:\n");
    printf("hi: %s\n", search(root, "hi") ? "Found" : "Not Found");

    return 0;
}