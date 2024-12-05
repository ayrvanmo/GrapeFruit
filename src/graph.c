/**
 * @file graph.c
 * @author Pendiente
 * @brief Funciones relacionadas con el grafo de Usuarios
*/
#include "graph.h"

/**
 * @brief Funcion para crear una lista de nodos
 * @param GraphList Puntero a una lista de nodos si se quiere vaciar
 * @return Puntero al centinela de la lista
*/
GraphList create_empty_graphList(GraphList graphList)
{
    if(!is_empty_graphList(graphList)){
        delete_graphList(graphList);
    }
    GraphList newList = (GraphList) malloc(sizeof(struct _graphNode));
    if(newList == NULL){
        print_error(200, NULL, NULL);
    }

    newList->next = NULL;
    return newList;
}

/**
 * @brief Funcion para verificar si una lista de nodos está vacía
 * @param graphList Puntero a la lista de nodos
 * @return TRUE si la lista está vacía, FALSE en caso contrario
*/
bool is_empty_graphList(GraphList graphList)
{
    return graphList == NULL;
}

/**
 * @brief Funcion para borrar una lista de nodos
 * @param graphList Puntero a la lista de nodos
*/
void delete_graphList(GraphList graphList)
{
    if(is_empty_graphList(graphList)){
        return;
    }
    GraphPosition aux = graphList->next;
    while(aux != NULL){
        delete_graphList_node(aux, graphList);
        aux = graphList->next;
    }
    free(graphList); // No se necesitan liberar adyacencias y incidencias porque no fueron alocadas en el centinela
}

/**
 * @brief Funcion para imprimir una lista de nodos por consola
 * @param graphList Puntero a la lista de nodos
*/
void print_graphList(GraphList graphList)
{
    GraphPosition P = graphList_first(graphList);

    while (P != NULL) {
        printf("Nodo: %s", P->user->name);
        P = P->next;
    }
}

/**
 * @brief Funcion para imprimir un nodo de la lista de nodos
 *
 * @param P Puntero al nodo a imprimir
*/
void print_graphNode(GraphPosition P)
{
    printf("Nodo: %s", P->user->name);
    printf("Lista de adyacencias [%d]:\n", P->followsNumber);
    print_friendList(P->follows);
    printf("Lista de incidencias [%d]:\n", P->followersNumber);
    print_friendList(P->followers);
}

/**
 * @brief Funcion para buscar un nodo en una lista de nodos (por su nombre)
 * @param graphList Puntero a la lista de nodos
 * @param name Nombre del nodo a buscar
 * @return Puntero al nodo encontrado, NULL en caso de no encontrarlo
*/
GraphPosition find_graphList_node(GraphList graphList, char *name)
{
    if(is_empty_graphList(graphList)){
        return NULL;
    }
    GraphPosition P = graphList_first(graphList);
    while (P != NULL && strcmp(P->user->name, name) != 0) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Funcion para encontrar el nodo anterior a un nodo en una lista de nodos
 * @param P Nodo del que se buscara el anterior
 * @param graphList Puntero a la lista de nodos
 * @return Puntero al nodo anterior a @p P
*/
GraphPosition find_graphList_prev_node(GraphPosition P, GraphList graphList)
{
    GraphPosition aux = graphList;
    while (aux != NULL && strcmp(aux->next->user->name, P->user->name) != 0){
        aux = aux->next;
    }
    return aux;
}

/**
 * @brief Funcion para insertar un nodo en una lista de nodos
 * @param prevPosition Puntero al nodo anterior al que se desea insertar el nuevo nodo
 * @param user Usuario contenido en el nodo
 * @return Puntero al nodo insertado
*/
GraphPosition insert_graphList_node(GraphPosition prevPosition, UserPosition user)
{
    GraphPosition newNode = (GraphPosition) malloc(sizeof (struct _graphNode));
    if(newNode == NULL){
        print_error(200, NULL, NULL);
    }
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    newNode->follows = create_empty_friendList(NULL);
    newNode->followers = create_empty_friendList(NULL);
    newNode->user = user;
    newNode->followsNumber = 0;
    newNode->followersNumber = 0;
    return newNode;
}

/**
 * @brief Funcion para borrar un nodo de una lista de nodos
 * @param P Puntero al nodo a borrar
 * @param graphList Puntero a la lista de nodos a la que pertenece @p P
*/
void delete_graphList_node(GraphPosition P, GraphList graphList)
{
    if(P == NULL){
        print_error(203, NULL, NULL);
    }
    GraphPosition prevNode = find_graphList_prev_node(P, graphList);
    if(prevNode == NULL){
        print_error(301, NULL, NULL);
        return;
    }

    prevNode->next = P->next;
    delete_friendList(P->follows);
    delete_friendList(P->followers);
    free(P);
}

// Funciones de interaccion con el usuario

/**
 * @brief Funcion para obtener el primer enlace de una lista de nodos
 * @param GraphList Lista de nodos del grafo
 * @return Puntero al primer enlace de la lista
*/
GraphPosition graphList_first(GraphList graphList)
{
    return graphList->next;
}

/**
 * @brief Funcion para obtener el ultimo enlace de una lista de nodos
 * @param GraphList Lista de nodos del grafo
 * @return Puntero al ultimo enlace de la lista
*/
GraphPosition graphList_last(GraphList graphList)
{
    GraphPosition P = graphList->next;
    while (P->next != NULL) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Funcion para obtener el siguiente enlace de una lista de nodos
 * @param P Puntero al nodo anterior al que se desea acceder
 * @return Puntero al siguiente nodo de la lista
*/
GraphPosition graphList_advance(GraphPosition P)
{
    return P->next;
}

/**
 * @brief Funcion para para obtener la lista de adyacencias de un nodo
 * @param P Puntero al nodo del que se desea obtener la lista de adyacencias
 * @return Puntero a la lista de adyacencias
*/
FriendList get_adjacentList(GraphPosition P)
{
    return P->follows;
}

/**
 * @brief Funcion para obtener la lista de incidencias de un nodo
 * @param P Puntero al nodo del que se desea obtener la lista de incidencias
 * @return Puntero a la lista de incidencias
*/
FriendList get_incidentList(GraphPosition P){
    return P->followers;
}

/**
 * @brief Funcion para obtener el nombre de un nodo
 * @param P Puntero al nodo del que se desea obtener el nombre
 * @return Puntero al nombre del nodo
*/
char *get_name(GraphPosition P)
{
    return P->user->name;
}


// Funciones del grafo general
/**
 * @brief Funcion para crear un grafo
 * @param graph Grafo a crear
 * @return Grafo creado
*/
Graph create_graph(Graph graph)
{
    if(graph != NULL)
    {
        delete_graph(graph);
    }

    graph = (Graph)malloc(sizeof(struct _graphHasTable) * GRAPH_HASH_SIZE);

    if(!graph){
        print_error(200,NULL,NULL);
    }

    for(int i = 0; i < GRAPH_HASH_SIZE; i++)
    {
        graph[i].nodeList = create_empty_graphList(NULL);
        graph[i].nodeNumber = 0;
    }

    return graph;
}

/**
 * @brief Funcion para imprimir un grafo por consola
 * @param graph Grafo a imprimir
*/
void print_graph(Graph graph)
{
    // Impresion completa
    for(int i = 0; i < GRAPH_HASH_SIZE; i++)
    {
        printf("-----------------------------\n");
        printf("Hash key: %d\n", i);
        print_graphList(graph[i].nodeList);
        printf("\n\n");
    }
    // Cantidad de nodos
    for(int i = 0; i < GRAPH_HASH_SIZE; i++)
    {
        printf("%d: %d nodos\n", i, graph[i].nodeNumber);
    }
}

/**
 * @brief Funcion para insertar un nodo en un grafo
 * @param user Usuario contenido en el nodo
 * @param graph Grafo en el que se desea insertar el nodo
 * @return Puntero al nodo insertado
*/
GraphPosition insert_graphNode(UserPosition user, Graph graph)
{
    int index = jenkins_hash(user->name) % GRAPH_HASH_SIZE;
    GraphPosition P = insert_graphList_node(graph[index].nodeList, user);
    if(P!=NULL){
        graph[index].nodeNumber++;
    }
    return P;
}

/**
 * @brief Busca un nodo en el grafo basado en el nombre del Usuario que contiene
 * @param name Nombre del Usuario a buscar
 * @param graph Grafo en el que se busca el nodo de nombre @p name
*/
GraphPosition find_graphNode(char *name, Graph graph)
{
    int index = jenkins_hash(name) % GRAPH_HASH_SIZE;
    return find_graphList_node(graph[index].nodeList, name);
}

/**
 * @brief Funcion para borrar un nodo de un grafo
 * @param name Nombre del Usuario contenido en el nodo
 * @param graph Grafo en el que se busca el nodo de nombre @p name
*/
void delete_graphNode(char *name, Graph graph)
{
    int index = jenkins_hash(name) % GRAPH_HASH_SIZE;
    GraphPosition P = find_graphList_node(graph[index].nodeList, name);
    if(P == NULL){
        print_error(301, NULL, NULL);
        return;
    }
    delete_graphList_node(P, graph[index].nodeList);
    graph[index].nodeNumber--;
}

/**
 * @brief Funcion para borrar un grafo
 * @param graph Grafo a borrar
*/
void delete_graph(Graph graph)
{
    for(int i = 0; i < GRAPH_HASH_SIZE; i++)
    {
        delete_graphList(graph[i].nodeList);
    }
    free(graph);
}

/**
 * @brief Funcion para crear un enlace entre dos nodos de un grafo
 * @param node1 Nodo de origen del enlace
 * @param node2 Nodo de destino del enlace
 * @return Puntero al enlace creado (En la lista de adyacencias de @p node1)
*/
FriendPosition create_graph_edge(GraphPosition node1, GraphPosition node2)
{
    FriendPosition nodeTo = insert_friendList_node(node1->follows, node2);
    if(nodeTo == NULL){
        print_error(303, NULL, NULL);
        return NULL;
    }
    FriendPosition nodeFrom = insert_friendList_node(node2->followers, node1);
    if(nodeFrom == NULL){
        print_error(303, NULL, NULL);
        return NULL;
    }
    node1->followsNumber++;
    node2->followersNumber++;
    return nodeTo;
}

/**
 * @brief Funcion para eliminar un enlace entre dos nodos de un grafo
 *
 * @param node1 Nodo de origen del enlace
 * @param node2 Nodo de destino del enlace
*/
void remove_graph_edge(GraphPosition node1, GraphPosition node2)
{
    FriendPosition nodeTo = find_friendList_node(node1->follows, *node2);
    if(nodeTo == NULL){
        print_error(301, NULL, NULL);
        return;
    }
    delete_friendList_node(nodeTo, node1->follows);
    node1->followsNumber--;

    FriendPosition nodeFrom = find_friendList_node(node2->followers, *node1);
    if(nodeFrom == NULL){
        print_error(301, NULL, NULL);
        return;
    }
    delete_friendList_node(nodeFrom, node2->followers);
    node2->followersNumber--;
}