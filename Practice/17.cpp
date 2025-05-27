#include<stdio.h>
#include<stdlib.h>
#include<algorithm>

using namespace std;

typedef struct TreeNode {
    int data;
    TreeNode *left = NULL;
    TreeNode *right = NULL;
} TreeNode;

TreeNode* createNode(int data) {
    auto newNode = (TreeNode* )malloc(sizeof(TreeNode));
    newNode->data = data;
    return newNode;
}

void printTree(TreeNode* root, int indent) {
    if (root == NULL) return;

    // Print left subtree
    if (root->left) {
        printTree(root->left, indent + 4);
        for (int i = 0; i < indent + 2; i++) printf(" ");
        printf("/\n");
    }

    // Print current node
    for (int i = 0; i < indent; i++) printf(" ");
    printf("%d\n", root->data);

    // Print right subtree
    if (root->right) {
        for (int i = 0; i < indent + 2; i++) printf(" ");
        printf("\\\n");
        printTree(root->right, indent + 4);
    }
}

TreeNode* insertBST(TreeNode* root, int data) {
    if(!root) return createNode(data);
    if(data > root->data) root->right = insertBST(root->right, data);
    else root->left = insertBST(root->left, data);
    return root;
}



int height(TreeNode* root) {
    if(!root) return 0;
    return max(height(root->left), height(root->right)) + 1;
}

int getBalance(TreeNode* root) {
    if(!root) return 0;

    return height(root->left) - height(root->right);
}

TreeNode* rotateLL(TreeNode* y) {//y - x - T2
    auto x = y->left;
    auto t2 = x->right;
    x->right = y;
    y->left = t2;
    return x;
}

TreeNode* rotateRR(TreeNode* x) {
    auto y = x->right;
    auto t2 = y->left;
    y->left = x;
    x->right = t2;
    return y;
}

TreeNode* insertAVL(TreeNode* root, int data) {
    if(!root) return createNode(data);

    if(data == root->data) return root;

    if(data > root->data) root->right = insertAVL(root->right, data);
    else root->left = insertAVL(root->left, data);

    const int balance = getBalance(root);

    if( balance >= -1 && balance <= 1) return root;

    if(balance > 1){
        if(data > root->left->data) root->left = rotateRR(root->left);
        return rotateLL(root);
    }else{
        if(data < root->right->data) root->right = rotateLL(root->right);
        return rotateRR(root);
    }
}

int main() {
    TreeNode* avl = NULL;
    TreeNode* bst = NULL;
    int values[] = { 10, 30, 70, 75};
    for (int i = 0; i < 4; i++) {
        avl = insertAVL(avl, values[i]);
		bst = insertBST(bst, values[i]);
    }
    printf("\nAVL Tree after insertions:\n");
    printTree(avl, 0);
	printf("\---------------------------------------\n");
    printf("\nBST Tree after insertions:\n");
    printTree(bst, 0);
    return 0;
}
