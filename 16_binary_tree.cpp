#include<stdio.h>
#include<stdlib.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implement a binary tree | linked lists
typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

void freeTree(TreeNode* root) {
	if (root == NULL) {
		return;
	}
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

void printTree(TreeNode* root, int indent) {
	if (root == NULL) return;

	if (root->left) {
		printTree(root->left, indent + 4);
		for (int i = 0; i < indent + 2; i++) printf(" ");
		printf("/\n");
	}

	for (int i = 0; i < indent; i++) printf(" ");
	printf("%d\n", root->data);

	if (root->right) {
		for (int i = 0; i < indent + 2; i++) printf(" ");
		printf("\\\n");
		printTree(root->right, indent + 4);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implement a binary tree | array
#define MAX_SIZE 20

int BT_Array[MAX_SIZE];
int BT_Array_Size = 0;

void insertBT_Array(int value) {
	if (BT_Array_Size >= MAX_SIZE) {
		printf("Tree is full!\n");
		return;
	}
	BT_Array[BT_Array_Size] = value;
	BT_Array_Size = BT_Array_Size + 1;
}

void printBT_Array() {
	printf("\nParent-Child Relations:\n");
	for (int i = 0; i < BT_Array_Size; i++) {
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		
		if (left < BT_Array_Size) {
			printf("Parent %d: ", BT_Array[i]);
			printf("Left = %d ", BT_Array[left]);
		}
		if (right < BT_Array_Size) {
			printf("Right = %d", BT_Array[right]);
		}
		printf("\n");
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implement a binary search tree
TreeNode* insertBST(TreeNode* root, int data) {
	if (root == NULL) {
		return createNode(data);
	}
	if (data < root->data) {
		root->left = insertBST(root->left, data);
	}
	else if (data > root->data) {//else로 해도 됨
		root->right = insertBST(root->right, data);
	}
	return root;
}

TreeNode* searchBST(TreeNode* root, int target_data) {
	if (root == NULL || root->data == target_data) {
		return root;
	}
	else if (target_data < root->data) {
		return searchBST(root->left, target_data);
	}
	else {
		return searchBST(root->right, target_data);
	}
}

TreeNode* deleteBST(TreeNode* root, int target_data) {
	if (root == NULL) {
		return root;
	}
	else if (target_data < root->data) {
		root->left = deleteBST(root->left, target_data);
	}
	else if (target_data > root->data) {
		root->right = deleteBST(root->right, target_data);
	}
	else {
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		TreeNode* temp = root->right;
		while (temp && temp->left != NULL) {
			temp = temp->left;
		}
		root->data = temp->data;
		root->right = deleteBST(root->right, temp->data);
	}
	return root;
}

int main() {
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Simple creation of a binary tree
	printf("-------- 1. Simple binary tree\n");
	TreeNode* root = createNode(1);
	root->left = createNode(2);
	root->right = createNode(3);
	root->left->left = createNode(4);
	root->left->right = createNode(5);
	root->left->left->right = createNode(6);

	// Visualize the binary tree
	printTree(root, 0);
	// Free the tree
	freeTree(root);
	printf("\n\n\n\n\n");

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create a binary tree using an array
	printf("-------- 2. Binary tree uisng an array\n");
	insertBT_Array(1);
	insertBT_Array(2);
	insertBT_Array(3);
	insertBT_Array(4);
	insertBT_Array(5);
	insertBT_Array(6);
	insertBT_Array(7);

	printBT_Array();
	printf("\n\n\n\n\n");

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create a binary search tree
	printf("-------- 3. Binary search tree\n");
	TreeNode* bstRoot = createNode(10);
	bstRoot = insertBST(bstRoot, 5);
	bstRoot = insertBST(bstRoot, 3);
	bstRoot = insertBST(bstRoot, 12);
	bstRoot = insertBST(bstRoot, 1);
	bstRoot = insertBST(bstRoot, 4);
	bstRoot = insertBST(bstRoot, 7);
	bstRoot = insertBST(bstRoot, 8);
	bstRoot = insertBST(bstRoot, 6);

	// Search the node (7) in the binary search tree
	TreeNode* search_result = searchBST(bstRoot, 7);
	if (search_result == NULL) {
		printf("Target data is not exist in the Tree \n");
	}
	else {
		printf("Target data is exist in the Tree \n");
	}

	// Visualize the binary search tree
	printTree(bstRoot, 0);
	printf("\n\n");

	// Delete the node (5) in the binary search tree
	bstRoot = deleteBST(bstRoot, 5);

	// Visualize the binary search tree after deletion
	printTree(bstRoot, 0);
	freeTree(bstRoot);

	return 0;
}
