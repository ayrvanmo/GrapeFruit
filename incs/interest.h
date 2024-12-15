 /**
 * @file interest.h
 * @author Pendiente
 * @brief Funciones de cabezera de interest.c
 */

#ifndef INTEREST_H
#define INTEREST_H

#define INTEREST_TABLE_SIZE 10


typedef struct _interestNode InterestNode;
typedef InterestNode *PtrToInterestNode;
typedef PtrToInterestNode InterestPosition;
typedef PtrToInterestNode InterestList;
typedef struct _interestTable* InterestTable;


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
struct _interestNode{
    char *key; /*!< interes asociada al hash key */
    //PreferencesPosition users ; /*!< Lista de usarios asociados a el interes */
    //int interestCount; /*!< Número de intereses asociados al nodo */
    InterestList next; /*!< Siguiente nodo de la lista */
};

/** \struct InterestTable
 *  @brief Estructura que representa un bloque de la tabla hash de la tabla de intereses
 */
struct _interestTable{
    InterestList interestList; /*!< Lista de intereses asociadas al hash key */
    int interestNumber; /*!< Conteo de cuantas listas de intereses están asociadas al hash key */
};

/* Funciones de manejo de tablas hash */
InterestList init_empty_interestList();
InterestTable init_interestTable();
void print_interestTable(InterestTable interestTable);
InterestPosition insert_interestNode(char*key, InterestTable interestTable);
InterestPosition insert_int_to_interestList(InterestPosition prevPosition, char* key);
InterestPosition search_int_in_interestTable(InterestTable interestTable, char* key);
InterestList find_previous_int(InterestTable interestTable, char* key);
void delete_interest_node(InterestTable interestTable, char* key);
void delete_interestTable(InterestTable interestTable);

/* Funciones de manejo usuarios */
void print_interestList(InterestList interestList);




#endif
