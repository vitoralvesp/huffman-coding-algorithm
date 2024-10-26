#include <stdio.h>
#include <stdlib.h>
#include "binary-search-tree.c"

int main() {

    Node *root = createNode(10);
    insert(&root, 80);
    insert(&root, 9);

    printf("\n\n");
    printf("Root Data: %d\n", root->data);
    if (root->left == NULL) printf("Root Left Data: NULL\n");
    if (root->right == NULL) printf("Root Right Data: NULL\n");
    if (root->left != NULL) printf("Root Left Data: %d\n", root->left->data);
    if (root->right != NULL) printf("Root Right Data: %d\n", root->right->data);
    printf("\n\n");

    free(root);
    // free(n1);
    // free(n2);

    return 0;

}