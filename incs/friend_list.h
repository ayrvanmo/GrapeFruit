/**
 * @file friend_list.h
 * @author Pendiente
 * @brief Cabeceras para funciones de friend_list.c
*/

#ifndef FRIEND_LIST_H
#define FRIEND_LIST_H

typedef struct _FriendListNode FriendListNode;
typedef FriendListNode *PtrToFriendNode;
typedef PtrToFriendNode FriendPosition;
typedef PtrToFriendNode FriendList;


#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "errors.h"
#include "graph.h"
#include "utilities.h"


/** \struct _FriendListNode
 * @brief Estructura para manejar una lista de enlaces a nodos de un grafo
*/
struct _FriendListNode {
    PtrToGraphNode graphNode; /*!< Nodo de grafo */
    FriendPosition next; /*!< Posicion siguiente en la lista */
};

// Funciones para el manejo de una lista de enlaces
FriendList create_empty_friendList(FriendList friendList);
void delete_friendList(FriendList friendList);
bool is_empty_friendList(FriendList friendList);
void print_friendList(FriendList friendList);
FriendPosition find_friendList_node(FriendList friendList, GraphNode graphNode);
FriendPosition find_friendList_prev_node(FriendPosition P, FriendList FriendList);
FriendPosition insert_friendList_node(FriendPosition prevPosition, PtrToGraphNode graphNode);
void delete_friendList_node(FriendPosition P, FriendList friendList);

// Funciones de interaccion con el usuario
FriendPosition friendList_first(FriendList friendList);
FriendPosition friendList_last(FriendList friensList);
FriendPosition friendList_advance(FriendPosition P);
PtrToGraphNode get_graphNode(FriendPosition P);




#endif