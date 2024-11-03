#include <stdio.h>
#include <stdlib.h>
#include "binary-search-tree.h"

/* createNode: cria um novo node para a árvore bst
   'new_node': novo node criado após a alocação de memória */
Node *createNode(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node != NULL)
    {
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    else
        printf("ERROR: Memory Allocation for New Node Failed!!!\n");
    
    return new_node;
}

/* insert: adiciona um novo node na árvore bst
   'root': raiz da árvore bst
   'new_node_data': dado int do node */
Node *insert(Node *root, int new_node_data)
{
    if (root == NULL)
        createNode(new_node_data);
    else if (new_node_data < root->data)
        root->left = insert(root->left, new_node_data);
    else if (new_node_data > root->data)
        root->right = insert(root->right, new_node_data);
    
    return root;
}

/* preOrderTraverse: realiza o percurso pré-ordem na árvore bst
   'root': raiz da árvore bst */
void preOrderTraverse(Node *root)
{
    if (root != NULL)
    {
        printf("%d -> ", root->data);
        preOrderTraverse(root->left);
        preOrderTraverse(root->right);
    }
}
