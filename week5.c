
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <minigrind.h>

typedef struct person{
    char *name;
    float height;
} person;

person *removeAllPersons(person *persons, int nrPersons){
    if(persons != NULL){
        for(int i = 0; i < nrPersons; i++){
            free(persons[i].name);
            persons[i].name = NULL;
            persons[i].height = 0.0;
        }
        free(persons);
    }
    return NULL;
}

void printPersons(person persons[], int nrPersons, int from, int to){
    // int i = 0;
    // int n = 0;
    // int printCheck = 0;
    
    
    // for(i = 0; i < from; i++);
    // n = i;
    
    
    // printf("[");
    
    // while(i < nrPersons && i <= to && persons[i].name != NULL){
    //     printf("(\"%s\",%0.3f),", persons[i].name, persons[i].height);
    //     i++;
    // }
    // if(n < i){
    //     printf("\b");
    // }
    // printf("]\n");
    
    // for(int i = from; i < to; i++){
    //     if(persons[i].name != NULL){
    //         printf("(\"%s\",%0.3f),", persons[i].name, persons[i].height);
    //         printCheck += 1;
    //     }
    // }
    // if(printCheck == 0){
    //     printf("]\n");
    // }else{
    //     printf("\b");
    //     printf("]\n");
    // }
    
    
    
    
    
    
    int maxPrint = 0;
    int currentPrint = 0;
    int i = 0;
    for(int j = 0; j < to; j++){
        if(persons[j].name != NULL){
            maxPrint += 1;
        }
    }
    printf("[");
    if(maxPrint == 0){
        printf("]\n");
    }else{
        while(i < to){
            if(persons[i].name != NULL && currentPrint < maxPrint - 1){
                printf("(\"%s\",%0.3f),", persons[i].name, persons[i].height);
                currentPrint ++;
            }else if(persons[i].name != NULL){
                printf("(\"%s\",%0.3f)]\n", persons[i].name, persons[i].height);
            }
            i++;
        }
        // printf("]\n");
        // if(persons[i].name != NULL){
        //     printf("(\"%s\",%0.3f)]\n", persons[i].name, persons[i].height);
        // }else{
        //     printf("]\n");
        // }
    }
}

void insertPerson(person persons[], int nrPersons, int newEntry, char *newName, float newHeight){
    persons[newEntry].name = (char*) malloc((strlen(newName) + 1) * sizeof(char));
    strcpy(persons[newEntry].name, newName);
    persons[newEntry].height = newHeight;
}

void maxHeight(person persons[], int nrPersons, float *max){
    //max = &persons[0].height;
    for(int i = 0; i < nrPersons; i++){
        if(*max < persons[i].height){
            *max = persons[i].height;
        }
    }
}

void replacePerson(person persons[], int nrPersons, int newEntry, char *newName, float newHeight){
    free(persons[newEntry].name);
    persons[newEntry].name = NULL;
    persons[newEntry].height = 0.0;
    persons[newEntry].name = (char*) malloc((strlen(newName) + 1) * sizeof(char));
    strcpy(persons[newEntry].name, newName);
    persons[newEntry].height = newHeight;
}

void bubbleSort(person persons[], int nrPersons, int *swapped){
    char tempName[80] = {'\0'};
    float tempHeight = 0;
    
    if(nrPersons == 1){
        *swapped = 0;
        return;
    }
    for(int i = 0; i < nrPersons - 1; i++){
        if(persons[i].height > persons[i + 1].height){
            strcpy(tempName, persons[i].name);
            free(persons[i].name);
            persons[i].name = NULL;
            strcpy(persons[i].name, persons[i + 1].name);
            free(persons[i + 1].name);
            persons[i + 1].name = NULL;
            strcpy(persons[i + 1].name, tempName);
            
            tempHeight = persons[i].height;
            persons[i].height = persons[i + 1].height;
            persons[i + 1].height = tempHeight;
        }else if(persons[i].height == persons[i + 1].height && strcmp(persons[i].name, persons[i + 1].name) > 0){
            strcpy(tempName, persons[i].name);
            free(persons[i].name);
            persons[i].name = NULL;
            strcpy(persons[i].name, persons[i + 1].name);
            free(persons[i + 1].name);
            persons[i + 1].name = NULL;
            strcpy(persons[i + 1].name, tempName);
            
            tempHeight = persons[i].height;
            persons[i].height = persons[i + 1].height;
            persons[i + 1].height = tempHeight;
        }
    }
    printPersons(persons, nrPersons, 0, nrPersons + *swapped);
    nrPersons -= 1;
    (*swapped) +=1;
    bubbleSort(persons, nrPersons, swapped);
    
}

float minHeight(person persons[], int nrPersons){
    float minHeight = 0;
    int contentChecker = 0;
    int stop = 0;
    int index = 0;
    
    for(int i = 0; i < nrPersons; i++){
        if(persons[i].name != NULL){
            contentChecker += 1;
        }
    }
    if(contentChecker == 0){
        return minHeight;
    }
    while(stop != 1){
        if(persons[index].name != NULL){
            minHeight = persons[index].height;
            stop = 1;
        }else{
            index++;
        }
    }
    for(int i = index; i < nrPersons; i++){
        if(persons[i].name != NULL && persons[i].height < minHeight){
            minHeight = persons[i].height;
        }
    }
    return minHeight;
}

int main(void){
    char cmd = 'a';
    person *persons = NULL;
    int nrPersons = 0;
    int newEntry = 0;
    char newName[80] = {'\0'};
    float newHeight = 0;
    float max = 0;
    float min = 0;
    float range = 0;
    int swapped = 0;
    //int i = 0;
    
    do{
        printf("Command? ");
        scanf(" %c", &cmd);
        switch(cmd){
            case 'q':
                removeAllPersons(persons, nrPersons);
                printf("Bye!\n");
                break;
            case 'n':
                persons = removeAllPersons(persons, nrPersons);
                nrPersons = 0;
                max = 0;
                min = 0;
                range = 0;
                printf("Entries? ");
                scanf(" %d", &nrPersons);
                if(nrPersons > 0){
                    persons = (person*) malloc(nrPersons * sizeof(person));
                    if(persons == NULL){
                        printf("malloc returned NULL");
                        return 0;
                    }
                    for(int i = 0; i < nrPersons; i++){
                        persons[i].name = NULL;
                        persons[i].height = 0.0;
                    }
                }
                break;
            case 'p':
                printPersons(persons, nrPersons, 0, nrPersons);
                break;
            case 'i':
                printf("Index? ");
                scanf(" %d", &newEntry);
                printf("Name? ");
                scanf(" %s", newName);
                printf("Height? ");
                scanf(" %f", &newHeight);
                if(newHeight <= 0.0){
                    printf("Height must be larger than zero\n");
                }else if(persons[newEntry].name != NULL || persons[newEntry].height != 0.0){
                    printf("Entry %d is already occupied by (\"%s\",%0.3f)\n", newEntry, persons[newEntry].name, persons[newEntry].height);
                }else{
                    insertPerson(persons, nrPersons, newEntry, newName, newHeight);
                }
                break;
            case 'h':
                maxHeight(persons, nrPersons, &max);
                min = minHeight(persons, nrPersons);
                range = max - min;
                printf("Min: %0.3f\n", min);
                printf("Max: %0.3f\n", max);
                printf("Range: %0.3f\n", range);
                break;
            case 'r':
                printf("Index? ");
                scanf(" %d", &newEntry);
                printf("Name? ");
                scanf(" %s", newName);
                printf("Height? ");
                scanf(" %f", &newHeight);
                if(newHeight <= 0.0){
                    printf("Height must be larger than zero\n");
                }else if(persons[newEntry].name != NULL || persons[newEntry].height != 0.0){
                    replacePerson(persons, nrPersons, newEntry, newName, newHeight);
                }else{
                    insertPerson(persons, nrPersons, newEntry, newName, newHeight);
                }
                break;
                case 'b':
                    bubbleSort(persons, nrPersons, &swapped);
                    printf("Swapped %d times\n", swapped);
                    swapped = 0;
                    break;
            
            default:
                printf("Unknown command '%c'\n", cmd);
                break;
        }
    }while(cmd != 'q');
    return 0;
}