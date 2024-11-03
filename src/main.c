#include <stdio.h>
#include <stdlib.h>
#include "bst-library/binary-search-tree.h"

/* bubble_sort: realiza a ordenação de dois vetores, um vetor de caracteres e outro de inteiros, simultaneamente
   'letters': vetor de caracteres com os caracteres do conteúdo do arquivo (sem repetição)
   'letters_occ': vetor de inteiros com o total de ocorrências de cada caractere do conteúdo do arquivo */
void bubble_sort(char letters[], int letters_occ[])
{
    for (int i = 0; i < 54; i++)
    {
        for (int j = 0; j < 54; j++)
        {
            if ((letters[j] > letters[j + 1]) && (letters[j] != '\0') && (letters[j+1] != '\0'))
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

/* check_letters: verifica se um caractere já foi inserido no vetor de caracteres
   'letters': vetor de caracteres com os caracteres do conteúdo do arquivo (sem repetição)
   'caracter': caractere a ser encontrado no vetor de caracteres
   'return i': retorno da posição do caractere encontrado no vetor de caracteres
   'return 0': retorno -1 indica que o caractere não foi encontrado no vetor de caracteres  */
int check_letters(char letters[], char caracter) {
    for (int i = 0; i < 54; i++)
        if (caracter == letters[i]) return i;
    return -1;
}



int main()
{

    FILE *file_ptr;
    int menu_option;

    while (1)
    {

        printf("\n---\nMENU:\n[ 1 ] Read & Analyse File\n[ 2 ] Create BST\n[ 3 ] Encode File\n[ 4 ] Exit\n\nOption: ");
        scanf("%d", &menu_option);

        if (menu_option == 4)
        {
            printf("---\n\nExiting Program...\n\n");
            if (file_ptr != NULL)
                fclose(file_ptr);
            break;
        }

        switch (menu_option)
        {

        case 1:

            // char filepath[100];

            printf("---\n\nREADING FILE\n");

            // printf("\nEnter file path: ");
            // scanf("%99s", filepath);
            // printf("Searching for File \"%s\"...\n", filepath);
            // file_ptr = fopen(filepath, "r");

            printf("Searching for File in \"../docs/input-files/in-the-end-by-linkin-park.txt\"...\n");
            file_ptr = fopen("../../docs/input-files/in-the-end-by-linkin-park.txt", "r");

            if (file_ptr == NULL)
            {
                printf("\nERROR: Cannot Open/Read File\n\n");
                exit(1);
            }
            else
            {
                char buffer[100];
                char letters[54];
                int letters_occ[54];
                int k = 0;
                int pos = 0;
                int capital = 0;
                int lowercase = 0;

                printf("\nFile Opened Succesfully!\n\nFile Content:\n");

                // Preenchendo os vetores com valores padrão '\0' e 0
                for (int k = 0; k < 54; k++)
                {
                    letters[k] = '\0';
                    letters_occ[k] = 0;
                }

                while (fgets(buffer, sizeof(buffer), file_ptr))
                {

                    printf("%s", buffer);

                    for (int i = 0; buffer[i] != '\0'; i++)
                    {
                        capital = (buffer[i] >= 65 && buffer[i] <= 90);
                        lowercase = (buffer[i] >= 97 && buffer[i] <= 122);
                        pos = check_letters(letters, buffer[i]);
            
                        // Se o caractere existir no vetor de caracteres, contabilizar +1
                        if (pos != -1) {
                            letters_occ[pos] += 1;

                          // Se o caractere não existir no vetor de caracteres, adicionar
                        } else if ((pos == -1) && (capital || lowercase) && (buffer[i] != '\n') && (buffer[i] != '\0')) {
                            letters[k] = buffer[i];
                            letters_occ[k] = 1;
                            k++;
                        }
                    }
                }

                bubble_sort(letters, letters_occ);

                printf("\n\nLetters Frequence:\n");
                for (int m = 0; letters[m] != '\0'; m++)
                    printf("%c: %d\n", letters[m], letters_occ[m]);
            }

            // printf("\n");
            break;

        case 2:
            break;
        case 3:
            break;
        default:
            break;
        }
    }

    return 0;
}