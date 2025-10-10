#include <stdio.h>
#include <stdlib.h>

// Define structure for a tree node
struct Node {
    int data;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a value into the BST
struct Node* insert(struct Node* root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    else
        printf("Duplicate values not allowed!\n");

    return root;
}

// Function to search for a value in the BST
struct Node* search(struct Node* root, int value) {
    if (root == NULL || root->data == value)
        return root;

    if (value < root->data)
        return search(root->left, value);

    return search(root->right, value);
}

// Find the minimum value node (used during deletion)
struct Node* findMin(struct Node* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

// Function to delete a node from the BST
struct Node* deleteNode(struct Node* root, int value, int *found) {
    if (root == NULL)
        return NULL;

    if (value < root->data)
        root->left = deleteNode(root->left, value, found);
    else if (value > root->data)
        root->right = deleteNode(root->right, value, found);
    else {
        *found = 1; // Node found
        // Node with one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get inorder successor
        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data, found);
    }
    return root;
}

// Inorder traversal (sorted order)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Function to display tree after every operation
void displayTree(struct Node* root) {
    printf("\nCurrent Tree (Inorder): ");
    if (root == NULL)
        printf("Empty");
    else
        inorder(root);
    printf("\n");
}

// Main function
int main() {
    struct Node* root = NULL;
    int choice, value, found;

    printf("==== Binary Search Tree Implementation ====\n");

    while (1) {
        printf("\n1. Insert\n2. Search\n3. Delete\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                displayTree(root);
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (search(root, value))
                    printf("Value %d found in the tree.\n", value);
                else
                    printf("Value %d not found in the tree.\n", value);
                displayTree(root);
                break;

            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                found = 0;
                root = deleteNode(root, value, &found);
                if (!found)
                    printf("Invalid! Value %d not found in the tree.\n", value);
                displayTree(root);
                break;

            case 4:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

