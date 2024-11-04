/* Node: estrutura do node da árvore Min Heap
   'letter': caractere do tipo char
   'frequency': frequência do caractere do tipo int
   'left': ponteiro para o node da subárvore à esquerda
   'right': ponteiro para o node da subárvore à direita */
typedef struct Node {
    char letter;
    int frequency;
    struct Node *left, *right;
} Node;

/* MinHeap: coleção dos nodes da árvore Min Heap 
   'size': altura da árvore Min Heap
   'capacity': capacidade da árvore Min Heap
   'arr': vetor de ponteiros para os nodes da árvore Min Heap */
typedef struct {
    int size;
    int capacity;
    Node **arr;

} MinHeap;

Node *createNode(char letter, int frequency);

MinHeap *createMinHeap(int capacity);

void swapNodes(Node **node_a, Node **node_b);

void minHeapify(MinHeap *min_heap, int idx);

Node *extractMin(MinHeap *min_heap);

void insertNode(MinHeap *min_heap, Node *node);

void buildMinHeap(MinHeap *min_heap);

int isLeaf(Node *root);

MinHeap *createAndBuildMinHeap(char letters[], int frequency[], int size);

int isSizeOne(MinHeap *min_heap);

Node *buildHuffmanTree(char letters[], int frequency[], int size);

void printArr(int arr[], int n);

void printCodes(Node *root, int arr[], int top);

