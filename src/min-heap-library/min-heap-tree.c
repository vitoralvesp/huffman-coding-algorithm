#include <stdio.h>
#include <stdlib.h>
#include "min-heap-tree.h"

/* createNode: cria um novo node para a árvore bst
   'letter': caractere do tipo char
   'frequency': frequência do caractere do tipo int
   'new_node': novo node criado após a alocação de memória */
Node *createNode(char letter, int frequency)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node != NULL)
    {
        new_node->letter = letter;
        new_node->frequency = frequency;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    else
        printf("ERROR: Memory Allocation for New Node Failed!!!\n");
    
    return new_node;
}

/* createMinHeap: cria uma árvore Min Heap
   'capacity': capacidade da árvore Min Heap 
   'min_heap': nova árvore Min Heap craida após a alocação e memória */
MinHeap *createMinHeap(int capacity) {
    MinHeap *min_heap = (MinHeap *)malloc(sizeof(MinHeap));

    if (min_heap != NULL) {
        min_heap->size = 0;
        min_heap->capacity = capacity;
        min_heap->arr = (MinHeap **)malloc(min_heap->capacity * sizeof(MinHeap *));

    } else
        printf("ERROR: Memory Allocation for New Min Heap Failed!!!\n");

    return min_heap;

}

/* swapNodes: troca a posição dos nodes na árvore Min Heap */
void swapNodes(Node **node_a, Node **node_b) {
    Node *aux = *node_a;
    *node_a = *node_b;
    *node_b = aux;
}

/* minHeapify: organiza a árvore Min Heap */
void minHeapify(MinHeap *min_heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if ((left < min_heap->size) && (min_heap->arr[left]->frequency < min_heap->arr[smallest]->frequency))
        smallest = left;
  
    if ((right < min_heap->size) && (min_heap->arr[right]->frequency < min_heap->arr[smallest]->frequency)) 
        smallest = right; 
  
    if (smallest != idx) { 
        swapNodes(&min_heap->arr[smallest], &min_heap->arr[idx]); 
        minHeapify(min_heap, smallest);
    }
}

/* extractMin: extrai o menor node da árvore Min Heap*/
MinHeap *extractMin(MinHeap *min_heap) {
    MinHeap *aux = min_heap->arr[0];
    min_heap->arr[0] = min_heap->arr[min_heap->size - 1];
    --min_heap->size;
    minHeapify(min_heap, 0);

    return aux;
}

/* insertNode: insere um node na árvore Min Heap */
void insertNode(MinHeap *min_heap, Node *node) {
    ++min_heap->size;
    int i = min_heap->size - 1;

    while ((i && node->frequency < min_heap->arr[(i - 1) / 2]->frequency)) {
        min_heap->arr[i] = min_heap->arr[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    min_heap->arr[i] = node;

}

/* buildMinHeap: cria a árvore Min Heap */
void buildMinHeap(MinHeap *min_heap) {
    int n = min_heap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; i--)
        minHeapify(min_heap, i);

}

/* isLeaf: */
int isLeaf(Node *root) {
    return !(root->left) && !(root->right);
}

/* */
MinHeap *createAndBuildMinHeap(char letters[], int frequency[], int size) {
    MinHeap *min_heap = createMinHeap(size);
    for (int i = 0; i < size; i++)
        min_heap->arr[i] = createNode(letters[i], frequency[i]);
    min_heap->size = size;
    buildMinHeap(min_heap);
    return min_heap;
}

/* */
int isSizeOne(MinHeap *min_heap) 
{ 
    return (min_heap->size == 1); 
} 


/* */
Node *buildHuffmanTree(char letters[], int frequency[], int size) {
    Node *left;
    Node *right;
    Node *top;

    MinHeap *min_heap = createAndBuildMinHeap(letters, frequency, size);

    while (!isSizeOne(min_heap)) {
        left = extractMin(min_heap);
        right = extractMin(min_heap);
        top = createNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        insertNode(min_heap, top);
    }
    return extractMin(min_heap);

}

/* */
void printArr(int arr[], int n) 
{ 
    int i; 
    for (i = 0; i < n; ++i) 
        printf("%d", arr[i]); 
  
    printf("\n"); 
} 

void printCodes(Node *root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    } else if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    } else if (isLeaf(root)) {
        printf("%c: ", root->letter);
        printArr(arr, top);
    }
}




