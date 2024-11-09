/*

CÓDIGO DE HUFFMAN
---
Integrantes:
Vitor Alves Pereira, 10410862
Eduardo Takashi Missaka, 10417877
Tiago Silveira Lopez, 10417600
---
Referências:
[ 1 ] https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
[ 2 ] https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/huffman.html

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_HT (100)

/* Node: estrutura do node da árvore Min Heap */
typedef struct Node {
    char letter;
    int frequency;
    struct Node *left, *right;
} Node;

/* MinHeap: coleção dos nodes da árvore Min Heap */
typedef struct {
    int size;
    int capacity;
    Node **arr;

} MinHeap;

/* createNode: cria um novo node para a árvore Min Heap */
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

/* createMinHeap: cria uma árvore Min Heap */
MinHeap *createMinHeap(int capacity) {
    MinHeap *min_heap = (MinHeap *)malloc(sizeof(MinHeap));

    if (min_heap != NULL) {
        min_heap->size = 0;
        min_heap->capacity = capacity;
        min_heap->arr = (Node **)malloc(min_heap->capacity * sizeof(Node *));

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

/* isSizeOne: função auxiliar para verificar se a altura da árvore é equivalente a 1 */
int isSizeOne(MinHeap *min_heap) 
{ 
    return (min_heap->size == 1); 
} 

/* extractMin: extrai o menor node da árvore Min Heap*/
Node *extractMin(MinHeap *min_heap) {
    Node *aux = min_heap->arr[0];
    min_heap->arr[0] = min_heap->arr[min_heap->size - 1];
    --min_heap->size;
    minHeapify(min_heap, 0);

    return aux;
}

/* insertNode: insere um node na árvore Min Heap */
void insertNode(MinHeap *min_heap, Node *node) {
    ++min_heap->size;
    int i = min_heap->size - 1;

    while (i && node->frequency < min_heap->arr[(i - 1) / 2]->frequency) {
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

/* printArr: função auxiliar para imprimir um vetor */
void printArr(int arr[], int n) 
{ 
    for (int i = 0; i < n; ++i) 
        printf("%d", arr[i]); 
} 

/* isLeaf: verifica se o node é uma folha */
int isLeaf(Node *root) {
    return !(root->left) && !(root->right);
}

/* createAndBuildMinHeap: função auxiliar para criar a árvore Min Heap */
MinHeap *createAndBuildMinHeap(char letters[], int frequency[], int size) {
    MinHeap *min_heap = createMinHeap(size);
    for (int i = 0; i < size; i++)
        min_heap->arr[i] = createNode(letters[i], frequency[i]);
    min_heap->size = size;
    buildMinHeap(min_heap);
    return min_heap;
}


/* buildHuffmanTree: cria a árvore min heap de acordo com o Código de Huffman */
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

/* search: função auxiliar para buscar um caractere na árvore min heap e imprimir o seu código */
void search(int letter, Node *root, int arr[], int top) {
    if (root->letter == letter) {
        printArr(arr, top);
    }
    if (root->left) {
        arr[top] = 0;
        search(letter, root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        search(letter, root->right, arr, top + 1);
    }
}

/* HuffmanCodes: busca por um caractere percorrendo a árvore Min Heap para imprimir o códigos gerado */
void HuffmanCodes(char letter, char data[], int freq[], int size) { 
    Node *root = buildHuffmanTree(data, freq, size);
    int arr[100];
    int top = 0; 
    search(letter, root, arr, top);
}

/* bubble_sort: realiza a ordenação de dois vetores, um vetor de caracteres e outro de inteiros, simultaneamente */
void bubble_sort(char letters[], int letters_occ[])
{
    for (int i = 0; i < 54; i++)
    {
        for (int j = 0; j < 54; j++)
        {
            if ((letters[j] > letters[j + 1]) && (letters[j] != '\0') && (letters[j + 1] != '\0'))
            {
                char aux_char = letters[j];
                int aux_int = letters_occ[j];

                letters[j] = letters[j + 1];
                letters_occ[j] = letters_occ[j + 1];

                letters[j + 1] = aux_char;
                letters_occ[j + 1] = aux_int;
            }
        }
    }
}

/* check_letters: verifica se um caractere já foi inserido no vetor de caracteres */
int check_letters(char letters[], char caracter)
{
    for (int i = 0; i < 54; i++)
        if (caracter == letters[i])
            return i;
    return -1;
}

int main()
{

    FILE *file_ptr;
    int menu_option;
    char letters[54];
    char buffer[100];
    int letters_occ[54];

    // Preenchendo os vetores com valores padrão '\0' e 0
    for (int k = 0; k < 54; k++)
    {
        letters[k] = '\0';
        letters_occ[k] = 0;
    }

    while (1)
    {

        printf("---\nMENU:\n[ 1 ] Read & Analyse File\n[ 2 ] Encode Characters\n[ 3 ] Encode File\n[ 4 ] Exit\n\nOption: ");
        scanf("%d", &menu_option);

        if (menu_option == 4)
        {
            printf("---\nExiting Program...\n\n");
            fclose(file_ptr);
            break;
        }

        switch (menu_option)
        {

        case 1:
            printf("---\nREADING FILE\n");

            printf("Searching for File in \"../../docs/input-files/in-the-end-by-linkin-park.txt\"...\n");
            file_ptr = fopen("../../docs/input-files/in-the-end-by-linkin-park.txt", "r");

            if (file_ptr == NULL)
            {
                printf("\nERROR: Cannot Open/Read File\n\n");
                exit(1);
            }
            else
            {
                int k = 0;
                int pos = 0;

                printf("\nFile Opened Succesfully!\n\nFile Content:\n");

                while (fgets(buffer, sizeof(buffer), file_ptr))
                {

                    printf("%s", buffer);

                    for (int i = 0; buffer[i] != '\0'; i++)
                    {
                        pos = check_letters(letters, buffer[i]);

                        // Se o caractere existir no vetor de caracteres, contabilizar +1
                        if (pos != -1)
                        {
                            letters_occ[pos] += 1;

                            // Se o caractere não existir no vetor de caracteres, adicionar
                        }
                        else if ((pos == -1) && (buffer[i] != '\0'))
                        {
                            letters[k] = buffer[i];
                            letters_occ[k] = 1;
                            k++;
                        }
                    }
                }

                bubble_sort(letters, letters_occ);


                printf("\n\nCharacters Frequency:\n");
                for (int m = 0; letters[m] != '\0'; m++) {
                    if (letters[m] == ' ') printf(" : %d\n", letters_occ[m]);
                    else if (letters[m] == '\n') printf("\\n: %d\n", letters_occ[m]);
                    else printf("%c: %d\n", letters[m], letters_occ[m]);
                }
            }

            break;

        case 2:
            printf("---\nHuffman Coding:\n");
            int size = sizeof(letters) / sizeof(letters[0]);
            for (int k = 0; letters[k] != '\0'; k++) {
                if (letters[k] == ' ') printf(" : ");
                else if (letters[k] == '\n') printf("\\n: ");
                else printf("%c: ", letters[k]);
                HuffmanCodes(letters[k], letters, letters_occ, size);
                printf("\n");
            }
            break;

        case 3:
            printf("---\nFile Encoded:\n");
            rewind(file_ptr);
            while (fgets(buffer, sizeof(buffer), file_ptr)) {
                for (int i = 0; buffer[i] != '\0'; i++)
                    HuffmanCodes(buffer[i], letters, letters_occ, size);
            }
            printf("\n");
            break;

        default:
            printf("---\nWrong Menu Option!!! Try Again only with 1 to 4 options...\n");
            break;
        }
    }

    return 0;
}