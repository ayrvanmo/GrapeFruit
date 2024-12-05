/**
 * @file graph.h
 * @author Pendiente
 * @brief Cabeceras para funciones de graph.c
*/
#ifndef GRAPH_H
#define GRAPH_H

// Provisorio
#define GRAPH_HASH_SIZE 10 // CONSTANTE PARA VER EL TAMANHO DE LA TABLA

typedef struct _graphNode GraphNode;
typedef GraphNode *PtrToGraphNode;
typedef PtrToGraphNode GraphPosition;
typedef PtrToGraphNode GraphList;
typedef struct _graphHasTable* Graph;

#include <stdbool.h>
#include <string.h>
#include "friend_list.h"
#include "user.h"
#include "hash.h"
#include "errors.h"

/** \struct _graphNode
 * @brief Nodo perteneciente al grafo
*/
struct _graphNode {
    UserPosition user; /*!<Puntero a la estructura que contiene información sobre el usuario */
    FriendList follows; /*!< Lista de nodos adyacentes al nodo */
    FriendList followers; /*!< Lista de nodos que lo incluyen como adyacente */
    int followsNumber; /*!< Numero de nodos adyacentes al nodo */
    int followersNumber; /*!< Numero de nodos que lo incluyen como adyacente */
    GraphPosition next; /*!< Posición siguiente en la lista de nodos del grafo */
};

/** \struct _graphHasTable
 *  @brief Estructura para representar un grafo como tabla hash
 */
struct _graphHasTable{
    GraphList nodeList; /*!< Lista de nodos asociados al hash key */
    unsigned int nodeNumber; /*!< Conteo de cuantas nodos están asociados al hash key */
};

// Funciones de lista de nodos
GraphList create_empty_graphList(GraphList graphList);
void delete_graphList(GraphList graphList);
bool is_empty_graphList(GraphList graphList);
void print_graphList(GraphList graphList);
void print_graphNode(GraphPosition P);
GraphPosition find_graphList_node(GraphList graphList, char *name);
GraphPosition find_graphList_prev_node(GraphPosition P, GraphList graphList);
GraphPosition insert_graphList_node(GraphPosition prevPosition, UserPosition user);
void delete_graphList_node(GraphPosition P, GraphList graphList);

// Funciones de interaccion con el usuario
GraphPosition graphList_first(GraphList graphList);
GraphPosition graphList_last(GraphList graphList);
GraphPosition graphList_advance(GraphPosition P);
FriendList get_adjacentList(GraphPosition P);
FriendList get_incidentList(GraphPosition P);
char *get_name(GraphPosition P);

// Funciones del grafo general
Graph create_graph(Graph graph);
void print_graph(Graph graph);
GraphPosition insert_graphNode(UserPosition user, Graph graph);
GraphPosition find_graphNode(char *name, Graph graph);
void delete_graphNode(char *name, Graph graph);
void delete_graph(Graph graph);
FriendPosition create_graph_edge(GraphPosition node1, GraphPosition node2);
void remove_graph_edge(GraphPosition node1, GraphPosition node2);

#endif