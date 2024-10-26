#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// createNode(dado) --> aloca dinamicamente um espaço na memória
// e cria um novo node com um valor passado como parâmetro.
Node *createNode(int data) {
    Node *result = malloc(sizeof(Node));
    if (result != NULL) {
        result->data = data;
        result->left = NULL;
        result->right = NULL;
    }
    return result;
}

// insert(ponteiro para a raiz, novo dado) --> insere um novo node na árvore
int insert(Node **rootptr, int new_data) {
    Node *root = *rootptr;
    
    if (root == NULL) { // Caso a árvore esteja vazia
        (*rootptr) = createNode(new_data);
        return 1;

    } else if (new_data == root->data) { // Caso o dado for igual a raiz
        return -1;

    } else if (new_data < root->data) { // Inserir dado à esquerda
        return insert(&(root->left), new_data);

    } else { // Inserir dado à direita
        return insert(&(root->right), new_data);

    }

}

// find(raiz, dado a ser encontrado) --> busca recursivamente um dado na árvore e retorna 1 se encontrá-lo ou -1 caso contrário
int find(Node *root, int find_data) {
    if (root == NULL) return -1;
    else if (root->data == find_data) return 1;
    else if (find_data < root->data) 
        return find(root->left, find_data);
    else
        return find(root->right, find_data);
}
