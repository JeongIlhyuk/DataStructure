#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
typedef struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    int isEndOfWord = 0;
} TrieNode;

TrieNode* createNode() {
    const auto node = (TrieNode *)malloc(sizeof(TrieNode));
    if(!node){
        perror("malloc");
        return nullptr;
    }
    for(auto& child:node->children)
        child = nullptr;

    return node;
}

void insert(TrieNode* root, const char* word) {
    auto curr = root;
    for(int i = 0; word[i] != '\0'; i++){
        const auto idx = word[i] - 'a';
        if(!curr->children[idx]) curr->children[idx] = createNode();
        curr = curr->children[idx];
    }
    curr->isEndOfWord = 1;
}

int search(TrieNode* root, const char* word) {
    auto curr = root;
    for(int i = 0; word[i] != '\0'; i++){
        const auto idx = word[i] - 'a';
        if(!curr->children[idx]) return 0;
        curr = curr->children[idx];
    }
    return curr->isEndOfWord;
}

int isEmpty(const TrieNode* root) {
    for(const auto child:root->children)
        if(child) return 0;
    return 1;
}

TrieNode* deleteWord(TrieNode* root, const char* word, int depth = 0) {
    if(!root) return nullptr;
    if(word[depth] == '\0'){
        root->isEndOfWord = 0;
        if(isEmpty(root)){
            free(root);
            return nullptr;
        }
        return root;
    }

    const int idx = word[depth] - 'a';
    root->children[idx] = deleteWord(root->children[idx], word, depth + 1);
    if(isEmpty(root) && !root->isEndOfWord){
        free(root);
        return nullptr;
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