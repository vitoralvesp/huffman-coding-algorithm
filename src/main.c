#include <stdio.h>
#include "header-files/binary-search-tree.h"

int main() {

    Node *root = createNode(10);
    preOrderTraverse(root);

    return 0;
    
}