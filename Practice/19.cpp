#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
typedef struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord = false;
} TrieNode;

TrieNode* createNode() {
    auto node = (TrieNode*)malloc(sizeof(TrieNode));
    for(int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

void insert(TrieNode* root, const char* word) {
    auto curr = root;
    for(int i = 0; word[i] != '\0'; i++){
        int idx = word[i] - 'a';
        if(!curr->children[idx]) curr->children[idx] = createNode();
        curr = curr->children[idx];
    }
    curr->isEndOfWord = true;
}

bool search(TrieNode* root, const char* word) {
    auto curr = root;
    for(int i = 0; word[i] != '\0'; i++){
        int idx = word[i] - 'a';
        if(!curr->children[idx]) return false;
        curr = curr->children[idx];
    }
    return curr->isEndOfWord;
}

bool isEmpty(TrieNode* root) {
    for(int i = 0; i < ALPHABET_SIZE; i++)
        if(root->children[i]) return false;
    return true;
}

TrieNode* deleteWord(TrieNode* root, const char* word, int depth = 0) {
    if(!root) return NULL;

    if(word[depth] == '\0'){
        if(isEmpty(root)){
            free(root);
            return NULL;
        }
        root->isEndOfWord = false;
        return root;
    }

    int idx = word[depth] - 'a';
    root->children[idx] = deleteWord(root->children[idx], word, depth + 1);

    if(isEmpty(root) && !root->isEndOfWord){
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