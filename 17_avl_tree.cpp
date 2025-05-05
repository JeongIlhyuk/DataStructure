#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// Binary Search Tree Implementation
TreeNode* insertBST(TreeNode* root, int data) {
    if (root == NULL) return createNode(data);
    if (data < root->data) {
        root->left = insertBST(root->left, data);
    }
    else if (data > root->data) {
        root->right = insertBST(root->right, data);
    }
    return root;
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


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// AVL Tree Implementation
int height(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int l = height(root->left);
    int r = height(root->right);
    int max_height;
    if (l > r) {
        max_height = l;
    }
    else {
        max_height = r;
    }
    return max_height + 1;
}

int getBalance(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    return height(root->left) - height(root->right);
}

TreeNode* rotateLL(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}

TreeNode* rotateRR(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    return y;
}

TreeNode* insertAVL(TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertAVL(root->left, data);
    }
    else if (data > root->data) {
        root->right = insertAVL(root->right, data);
    }
    else {
        return root;
    }

    int balance = getBalance(root);

    if (balance > 1 && data < root->left->data)  // LL
        return rotateLL(root);
    if (balance > 1 && data > root->left->data) { // LR
        root->left = rotateRR(root->left);
        return rotateLL(root);
    }
    if (balance < -1 && data > root->right->data) // RR
        return rotateRR(root);
    if (balance < -1 && data < root->right->data) { // RL
        root->right = rotateLL(root->right);
        return rotateRR(root);
    }

    return root;
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
