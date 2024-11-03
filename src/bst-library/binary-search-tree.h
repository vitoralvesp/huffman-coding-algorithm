/* Node: estrutura do node da árvore bst
   'data': chave de valor inteiro
   'left': ponteiro para o node da subárvore à esquerda
   'right': ponteiro para o node da subárvore à direita */
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node *createNode(int data);
Node *insert(Node *root, int new_node_data);
void preOrderTraverse(Node *root);