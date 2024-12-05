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
    newInterestList->userCount = 0;
    newInterestList->users = NULL;
    return newInterestList;
}

/**
 * @brief Funcion para inicializar una tabla de intereses vacía
 * @return InterestTable Tabla de intereses a inicializar
 */
InterestTable init_interestTable()
{
    InterestTable newInterestTable = malloc(sizeof(struct _InterestTable)*INTEREST_TABLE_SIZE);
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

InterestList insert_int_to_interestTable(InterestTable interestTable, char* key)
{
    int hashKey = jenkins_hash(key);
    InterestList newInterest = malloc(sizeof(InterestNode));
    if(!newInterest)
    {
        print_error(200, NULL, NULL);
    }
    newInterest->key = key;
    newInterest->next = interestTable[hashKey].interestList->next;
    interestTable[hashKey].interestList->next = newInterest;
    interestTable[hashKey].interestNumber++;
    return newInterest;
}

InterestList search_int_in_interestTable(InterestTable interestTable, char* key)
{
    int hashKey = jenkins_hash(key);
    InterestList P = interestTable[hashKey].interestList->next;
    while(P != NULL && strcmp(P->key, key) != 0)
    {
        P = P->next;
    }
    return P;
}

InterestList find_previous_int(InterestTable interestTable, char* key)
{
    int hashKey = jenkins_hash(key);
    InterestList P = interestTable[hashKey].interestList;
    while(P->next != NULL && strcmp(P->next->key, key) != 0)
    {
        P = P->next;
    }
    return P;
}

void delete_interest_node(InterestTable interestTable, char* key)
{
    int hashKey = jenkins_hash(key);
    InterestList P = find_previous_int(interestTable, key);
    if(P == NULL)
    {
        print_error(203, NULL, NULL);
    }
    InterestList TmpCell = P->next;
    P->next = TmpCell->next;
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
            free(TmpCell);
        }
    }
    free(interestTable);
}

// MANEJO DE USUARIOS
InterestList insert_user_to_interestList(InterestList interestList, UserPosition user)
{
    UserPosition P = interestList->users;
    while(P != NULL && strcmp(P->name, user->name) != 0) // ESTA PARTE SE PODRIA MEJORAR CON OTRO TIPO DE BUSQUEDA MAS EFICIENTE
    {
        P = P->Next;
    }
    if(P == NULL)
    {
        user->Next = interestList->users;
        interestList->users = user;
        interestList->userCount++;
    }
    return interestList;
}

void print_interestList(InterestList interestList)
{
    UserPosition P = interestList->users;
    while(P != NULL)
    {
        printf("%s\n", P->name);
        P = P->Next;
    }
}

void delete_user_from_interestList(InterestList interestList, UserPosition user)
{
    UserPosition P = find_previous_user_in_interestList(interestList, user->name);
    if(P == NULL)
    {
        print_error(203, NULL, NULL);
    }
    P->Next = user->Next;
    free(user);
    interestList->userCount--;
}

UserPosition find_user_in_interestList(InterestList interestList, char* userName)
{
    UserPosition P = interestList->users;
    while(P != NULL && strcmp(P->name, userName) != 0)
    {
        P = P->Next;
    }
    return P;
}

UserPosition find_previous_user_in_interestList(InterestList interestList, char* userName)
{
    UserPosition P = interestList->users;
    while(P->Next != NULL && strcmp(P->Next->name, userName) != 0)
    {
        P = P->Next;
    }
    return P;
}