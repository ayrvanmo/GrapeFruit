/**
 * @file link_list.c
 * @author
 * @brief Funciones para el manejo de una lista de enlaces(amistades) a nodos de un grafo
*/

#include "friend_list.h"

/**
 * @brief Funcion para vaciar una lista de enlaces(amistades)
 * @param FriendList Lista de enlaces(amistades)
 * @return Puntero a una lista vacia
*/
FriendList create_empty_friendList(FriendList friendList)
{
    if(!is_empty_friendList(friendList)){
        delete_friendList(friendList);
    }
    FriendList newList = (FriendList) malloc(sizeof(struct _FriendListNode));
    if(newList == NULL){
        print_error(200, NULL, NULL);
    }
    newList->next = NULL;
    newList->graphNode = NULL;
    return newList;
}

/**
 * @brief Funcion para eliminar una lista de enlaces(amistades)
 * @param FriendList Lista de enlaces(amistades) a eliminar
*/
void delete_friendList(FriendList friendList)
{
    if(is_empty_friendList(friendList)){
        return;
    }
    FriendPosition aux = friendList->next;
    while(aux != NULL){
        delete_friendList_node(aux, friendList);
        aux = friendList->next;
    }
    free(friendList);
}

/**
 * @brief Funcion para verificar si una lista de enlaces(amistades) esta vacia
 * @param FriendList Lista de enlaces(amistades)
 * @return TRUE si la lista esta vacia, FALSE en caso contrario
*/
bool is_empty_friendList(FriendList FriendList)
{
    return FriendList == NULL;
}

/**
 * @brief Funcion para imprimir una lista de enlaces(amistades)
 * @param FriendList Lista de enlaces(amistades)
*/
void print_friendList(FriendList FriendList) {
    FriendPosition P = friendList_first(FriendList);

    while (P != NULL) {
        printf("        Nodo: %s", P->graphNode->user->name);
        P = P->next;
    }
}

/**
 * @brief Funcion para encontrar un nodo en una lista de enlaces(amistades)
 * @param FriendList Lista de enlaces(amistades)
 * @param graphNode Nodo de grafo que se desea buscar en la lista
 * @return Puntero al nodo si se encuentra, NULL en caso contrario
*/
FriendPosition find_friendList_node(FriendList FriendList, GraphNode graphNode)
{
    if(is_empty_friendList(FriendList)){
        return NULL;
    }
    FriendPosition P = friendList_first(FriendList);
    while (P != NULL && strcmp(P->graphNode->user->name, graphNode.user->name) != 0) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Funcion para obtener el anterior enlace de una lista de enlaces(amistades)
 * @param P Puntero al enlace posterior al que se desea acceder
 * @return Puntero al anterior enlace de la lista
*/
FriendPosition find_friendList_prev_node(FriendPosition P, FriendList friendList)
{
    FriendPosition aux = friendList;
    while (aux != NULL && aux->next != P) {
        aux = aux->next;
    }
    return aux;
}

/**
 * @brief Funcion para insertar un nodo en una lista de enlaces(amistades)
 * @param prevPosition Puntero al enlace anterior al que se desea insertar el nuevo enlace
 * @param graphNode Nodo de grafo al que apunta el enlace a insertar
 * @return Puntero al nuevo enlace insertado
*/
FriendPosition insert_friendList_node(FriendPosition prevPosition, PtrToGraphNode graphNode)
{
    FriendPosition newNode = (FriendPosition) malloc(sizeof(struct _FriendListNode));
    if(newNode == NULL){
        print_error(200, NULL, NULL);
    }

    newNode->graphNode = graphNode;

    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    return newNode;
}


/**
 * @brief Funcion para eliminar un enlace de una lista de enlaces(amistades)
 * @param P Puntero al enlace que se desea eliminar
 * @param FriendList Lista de enlaces(amistades) a la que pertenece @p P
*/
void delete_friendList_node(FriendPosition P, FriendList friendList)
{
    if(P == NULL){
        print_error(203, NULL, NULL);
    }
    FriendPosition prevNode = find_friendList_prev_node(P, friendList);
    if(prevNode == NULL){
        print_error(301, NULL, NULL);
        return;
    }

    prevNode->next = P->next;
    free(P);
}


// Funciones de interaccion con el usuario

/**
 * @brief Funcion para obtener el primer enlace de una lista de enlaces(amistades)
 * @param FriendList Lista de enlaces(amistades)
 * @return Puntero al primer enlace de la lista
*/
FriendPosition friendList_first(FriendList friendList)
{
    return friendList->next;
}

/**
 * @brief Funcion para obtener el ultimo enlace de una lista de enlaces(amistades)
 * @param FriendList Lista de enlaces(amistades)
 * @return Puntero al ultimo enlace de la lista
*/
FriendPosition friendList_last(FriendList friendList)
{
    FriendPosition P = friendList->next;
    while (P->next != NULL) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Funcion para obtener el siguiente enlace de una lista de enlaces(amistades)
 * @param P Puntero al enlace anterior al que se desea acceder
 * @return Puntero al siguiente enlace de la lista
*/
FriendPosition friendList_advance(FriendPosition P)
{
    return P->next;
}

/**
 * @brief Funcion para obtener el nodo de un grafo a partir de un enlace
 * @param P Puntero al enlace
 * @return Nodo de grafo
*/
PtrToGraphNode get_graphNode(FriendPosition P)
{
    if(P == NULL){
        print_error(203, NULL, NULL);
    }
    return P->graphNode;
}