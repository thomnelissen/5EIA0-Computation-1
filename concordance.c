```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "predefined.h"

int nrWords(entry_t concordance[]){
    int index = 0;
    for(int i = 0; i < MAXWORDS; i++){
        if(concordance[i].word != NULL){
            index++;
        }
    }
    return index;
}

void addWord(entry_t concordance[], char *word){
    if(nrWords(concordance) == MAXWORDS){
        return;
    }
    for(int i = 0; i <= nrWords(concordance); i++){
        if(concordance[i].word == NULL){
            concordance[i].word = (char*) malloc((strlen(word) + 1) * sizeof(char));
            strcpy(concordance[i].word, word);
            for(int j = 0; j < MAXINDEX; j++){
                concordance[i].indices[j] = -1;
            }
            return;
        }else if(strcmp(word, concordance[i].word) < 0){
            for(int j = nrWords(concordance) - 1; j >= i; j--){
                concordance[j + 1].word = (char*) malloc((strlen(concordance[j].word) + 1) * sizeof(char));
                strcpy(concordance[j + 1].word, concordance[j].word);
                free(concordance[j].word);
                concordance[j].word = NULL;
                for(int k = 0; k < MAXINDEX; k++){
                    concordance[j + 1].indices[k] = concordance[j].indices[k];
                }
            }
            concordance[i].word = (char*) malloc((strlen(word) + 1) * sizeof(char));
            strcpy(concordance[i].word, word);
            for(int k = 0; k < MAXINDEX; k++){
                concordance[i].indices[k] = -1;
            }
            return;
        }else if(strcmp(word, concordance[i].word) == 0){
            return;
        }
    }
}

void removeAllWords(entry_t concordance[]){
    for(int i = 0; i < MAXWORDS; i++){
        if(concordance[i].word != NULL){
            free(concordance[i].word);
            concordance[i].word = NULL;
        }
    }
}

void printConcordance(entry_t concordance[]){
    if(nrWords(concordance) == 0){
        printf("The concordance is empty\n");
    }else{
        printf("Concordance\n");
        for(int i = 0; i < MAXWORDS; i++){
            if(concordance[i].word != NULL){
                printf("%10s:", concordance[i].word);
                for(int j = 0; j < MAXINDEX; j++){
                        if(concordance[i].indices[j] != -1){
                            printf(" %d", concordance[i].indices[j]);
                        }
                    }
                printf("\n");
            }
        }
    }
}

void addIndex(entry_t concordance[], char *word, int index){
    int indexWord = -1;
    for(int i = 0; i < MAXWORDS; i++){
        if(concordance[i].word != NULL){
            if(strcmp(word, concordance[i].word) == 0){
                indexWord = i;
                break;
            }
        }
    }
    if(indexWord == -1){
        printf("Word %s not found\n", word);
        return;
    }
    for(int j = 0; j < MAXINDEX; j++){
        if(concordance[indexWord].indices[j] == -1){
            concordance[indexWord].indices[j] = index;
            return;
        }
    }
}

void readFile(entry_t concordance[], char *filename, int *index){
    int inserted = 0;
    FILE *pfile = fopen(filename, "r");
    if(pfile == NULL){
        printf("Cannot open file %s\n", filename);
        return;
    }
    do{
        char word[100] = {'\0'};
        if(fscanf(pfile, "%s", &word[0]) == EOF){
            fclose(pfile);
            printf("Inserted %d words\n", inserted);
            return;
        }
        addWord(concordance, word);
        addIndex(concordance, word, *index);
        (*index)++;
        inserted++;
    }while(1);
}

void removeWord(entry_t concordance[], char *word){
    int indexWord = -1;
    for(int i = 0; i < MAXWORDS; i++){
        if(concordance[i].word != NULL){
            if(strcmp(word, concordance[i].word) == 0){
                indexWord = i;
                break;
            }
        }
    }
    if(indexWord == -1){
        printf("Word %s not found\n", word);
        return;
    }
    for(int j = 0; j < MAXINDEX; j++){
        concordance[indexWord].indices[j] = -1;
    }
    free(concordance[indexWord].word);
    concordance[indexWord].word = NULL;
}

char *findWordAtIndex(entry_t concordance[], int index){
    char* word = NULL;
    for(int i = 0; i < MAXWORDS; i++){
        if(concordance[i].word != NULL){
            for(int j = 0; j < MAXINDEX; j++){
                if(concordance[i].indices[j] == index){
                    word = concordance[i].word;
                    return word;
                }
            }
        }
    }
    return word;
}

void printOriginalText(entry_t concordance[]){
    int maxIndex = -1;
    int printed = 0;
    for(int i = 0; i < MAXWORDS; i++){
        if(concordance[i].word != NULL){
            for(int j = 0; j < MAXINDEX; j++){
                if(concordance[i].indices[j] > maxIndex){
                    maxIndex = concordance[i].indices[j];
                }
            }
        }
    }
    if(maxIndex == -1){
        return;
    }
    for(int index = 0; index <= maxIndex; index++){
        for(int i = 0; i < MAXWORDS; i++){
            if(concordance[i].word != NULL){
                for(int j = 0; j < MAXINDEX; j++){
                    if(concordance[i].indices[j] == index){
                        printf("%s", concordance[i].word);
                        printed = 1;
                    }
                }
            }
        }
        if(index == maxIndex){
            if(printed != 0){
                printf("\n");
                printed = 0;
            }else{
                printf("?\n");
            } 
        }else{
            if(printed != 0){
                printf(" ");
                printed = 0;
            }else{
                printf("? ");
            }
        }
    }
}

int findMinIndex(entry_t concordance[], int from){
    int minIndex = concordance[from].indices[0];
    int minIndexWord = from;
    for(int i = from; i <= nrWords(concordance); i++){
        if(concordance[i].word != NULL){
            if(concordance[i].indices[0] < minIndex){
                minIndex = concordance[i].indices[0];
                minIndexWord = i;
            }
        }
    }
    return minIndexWord;
}

void sortConcordance(entry_t concordance[]){
    int minIndexWord = -1;
    if(nrWords(concordance) == 0){
        return;
    }
    for(int i = 0; i <= nrWords(concordance); i++){
        minIndexWord = findMinIndex(concordance, i);
        if(minIndexWord != i){
            char word1[100] = {'\0'};
            char word2[100] = {'\0'};
            int indices1[MAXINDEX];
            int indices2[MAXINDEX];
            strcpy(word1, concordance[i].word);
            strcpy(word2, concordance[minIndexWord].word);
            for(int j = 0; j < MAXINDEX; j++){
                indices1[j] = concordance[i].indices[j];
                indices2[j] = concordance[minIndexWord].indices[j];
            }
            if(strcmp(word1, word2) != 0){
                free(concordance[i].word);
                concordance[i].word = NULL;
                free(concordance[minIndexWord].word);
                concordance[minIndexWord].word = NULL;
                concordance[i].word = (char*) malloc((strlen(word2) + 1) * sizeof(char));
                strcpy(concordance[i].word, word2);
                concordance[minIndexWord].word = (char*) malloc((strlen(word1) + 1) * sizeof(char));
                strcpy(concordance[minIndexWord].word, word1);
                for(int j = 0; j < MAXINDEX; j++){
                    concordance[i].indices[j] = indices2[j];
                    concordance[minIndexWord].indices[j] = indices1[j];
                }
            }
        }
    }
}



int main (void)
{
    entry_t concordance[MAXWORDS] = {NULL};
    char word[100] = {'\0'};
    char cmd = 'z';
    int index = 0;
    char *wordAtIndex = NULL;
    int fileIndex = 0;
    char fileName[100] = {'\0'};
    
    do{
        printf("Command? ");
        scanf(" %c", &cmd);
        switch(cmd){
            case 'q':
                removeAllWords(concordance);
                printf("Bye!\n");
                break;
            case 'w':
                printf("Word? ");
                scanf("%s", word);
                addWord(concordance, word);
                break;
            case 'p':
                printConcordance(concordance);
                break;
            case 'i':
                printf("Word index? ");
                scanf("%s", word);
                scanf(" %d", &index);
                addIndex(concordance, word, index);
                break;
            case 'r':
                printf("File name? ");
                scanf("%s", fileName);
                readFile(concordance, fileName, &fileIndex);
                break;
            case 'W':
                printf("Word? ");
                scanf("%s", word);
                removeWord(concordance, word);
                break;
            case 'f':
                printf("Index? ");
                scanf(" %d", &index);
                wordAtIndex = findWordAtIndex(concordance, index);
                if(wordAtIndex == NULL){
                    printf("There is no word at index %d\n", index);
                }else{
                    printf("The word at index %d is %s\n", index, wordAtIndex);
                }
                break;
            case 'o':
                 printOriginalText(concordance);
                 break;
            case 's':
                sortConcordance(concordance);
                break;
            
            default:
                printf("Unknown command \'%c\'\n", cmd);
                break;
        }
    }while(cmd != 'q');
    return 0;
}
```