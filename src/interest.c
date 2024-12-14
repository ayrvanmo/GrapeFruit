/**
 * @file interest.c
 * @author Pendiente
 * @brief Funciones relacionadas con los intereses de los usuarios
 */

#include "interest.h"

/**
 * @brief Funcion pra inicializar una lista de intereses vacía
 * @return InterestList Lista de intereses a inicializar
 */
InterestList init_empty_interestList()
{
    InterestList newInterestList = (InterestList)malloc(sizeof(InterestNode));
    if(!newInterestList)
    {
        print_error(200, NULL, NULL);
    }
    newInterestList->key = NULL;
    newInterestList->next = NULL;
    return newInterestList;
}

/**
 * @brief Funcion para inicializar una tabla de intereses vacía
 * @return InterestTable Tabla de intereses a inicializar
 */
InterestTable init_interestTable()
{
    InterestTable newInterestTable = malloc(sizeof(struct _interestTable)*INTEREST_TABLE_SIZE);
    if(!newInterestTable)
    {
        print_error(200, NULL, NULL);
    }
    for(int i=0; i<INTEREST_TABLE_SIZE;i++){
        newInterestTable[i].interestList = init_empty_interestList();
        newInterestTable[i].interestNumber = 0;
    }
    return newInterestTable;
}

void print_interestTable(InterestTable interestTable)
{
    for(int i=0; i<INTEREST_TABLE_SIZE;i++){
        printf("Hash key: %d\n", i);
        print_interestList(interestTable[i].interestList);
    }
}

InterestPosition insert_interestNode(char*key, InterestTable interestTable)
{
    int index = jenkins_hash(key) % INTEREST_TABLE_SIZE;
    InterestPosition P = insert_int_to_interestList(interestTable[index].interestList, key);
    if(P!=NULL){
        interestTable[index].interestNumber++;
    }
    return P;
}

InterestPosition insert_int_to_interestList(InterestPosition prevPosition, char* key)
{
    InterestPosition newNode = (InterestPosition)malloc(sizeof(struct _interestNode));
    if(newNode == NULL)
    {
        print_error(200, NULL, NULL);
    }
    newNode->key = malloc(strlen(key) + 1);
    if(newNode->key == NULL)
    {
        print_error(200, NULL, NULL);
    }
    strcpy(newNode->key, key);
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    return newNode;
}


InterestPosition search_int_in_interestTable(InterestTable interestTable, char* key)
{

    unsigned int hashKey = jenkins_hash(key) % INTEREST_TABLE_SIZE;

    InterestPosition P = interestTable[hashKey].interestList->next;

    while(P != NULL && strcmp(P->key, key) != 0)
    {
        P = P->next;
    }
    //printf("exitoso\n");
    return P;
}

InterestList find_previous_int(InterestTable interestTable, char* key)
{
    int hashKey = jenkins_hash(key) % INTEREST_TABLE_SIZE;
    InterestList P = interestTable[hashKey].interestList;
    while(P->next != NULL && strcmp(P->next->key, key) != 0)
    {
        P = P->next;
    }
    return P;
}

void delete_interest_node(InterestTable interestTable, char* key)
{
    int hashKey = jenkins_hash(key) % INTEREST_TABLE_SIZE;
    InterestList P = find_previous_int(interestTable, key);
    if(P == NULL)
    {
        print_error(203, NULL, NULL);
    }
    InterestList TmpCell = P->next;
    P->next = TmpCell->next;
    free(TmpCell->key);
    free(TmpCell);
    interestTable[hashKey].interestNumber--;
}

void delete_interestTable(InterestTable interestTable)
{
    for(int i=0; i<INTEREST_TABLE_SIZE;i++){
        InterestList P = interestTable[i].interestList;
        while(P != NULL){
            InterestList TmpCell = P;
            P = P->next;
            free(TmpCell->key);
            free(TmpCell);
        }
    }
    free(interestTable);
}

void print_interestList(InterestList interestList)
{
    InterestList P = interestList;
    while(P != NULL){
        printf("Interes: %s\n", P->key);
        P = P->next;
    }
}

