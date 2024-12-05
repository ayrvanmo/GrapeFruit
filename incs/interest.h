/**
 * @file interest.h
 * @author Pendiente
 * @brief Funciones de cabezera de interest.c
 */

#ifndef INTEREST_H
#define INTEREST_H

#define INTEREST_TABLE_SIZE 10

typedef struct _InterestNode InterestNode;
typedef InterestNode* InterestList;
typedef struct _InterestTable InterestTableNode;
typedef InterestTableNode* InterestTable;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "errors.h"
#include "hash.h"


/**
* @struct _InterestNode
* @brief Nodo de la lista de intereses asociadas a un hash key
*/
struct _InterestNode{
    char *key; /*!< interes asociada al hash key */
    UserPosition users; /*!< Lista de usarios asociados a el interes */
    unsigned int userCount; /*!< Número de usarios asociados a el interes */
    InterestList next; /*!< Siguiente nodo de la lista */
};

/** \struct InterestTable
 *  @brief Estructura que representa un bloque de la tabla hash de la tabla de intereses
 */
struct _InterestTable{
    InterestList interestList; /*!< Lista de intereses asociadas al hash key */
    unsigned int interestNumber; /*!< Conteo de cuantas listas de intereses están asociadas al hash key */
};

/* Funciones de manejo de tablas hash */
InterestList init_empty_interestTable();
InterestTable init_interestTable();
void print_interestTable(InterestTable interestTable);
InterestList insert_int_to_interestTable(InterestTable interestTable, char* key);
InterestList search_int_in_interestTable(InterestTable interestTable, char* key);
InterestList find_previous_int(InterestTable interestTable, char* key);
void delete_interest_node(InterestTable interestTable, char* key);
void delete_interestTable(InterestTable interestTable);

/* Funciones de manejo usuarios */
InterestList insert_user_to_interestList(InterestList interestList, UserPosition user);
void print_interestList(InterestList interestList);
void delete_user_from_interestList(InterestList interestList, UserPosition user);
UserPosition find_user_in_interestList(InterestList interestList, char* userName);
UserPosition find_previous_user_in_interestList(InterestList interestList, char* userName);



#endif
