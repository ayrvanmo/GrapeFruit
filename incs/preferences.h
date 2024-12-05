/**
 * @file preferences.h
 * @author Pendiente
 * @brief Funciones de cabezera de preferences.c
 */

#ifndef PREFERENCES_H
#define PREFERENCES_H

typedef struct _PreferencesListNode PreferencesListNode;
typedef PreferencesListNode *PtrToPreferencesNode;
typedef PtrToPreferencesNode PreferencesPosition;
typedef PtrToPreferencesNode PreferencesList;


#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "errors.h"
#include "graph.h"
#include "utilities.h"


/** \struct _PreferencesListNode
 * @brief Lista de preferencias de un usuario
*/
struct _PreferencesListNode {
    char *key; /*!< Preferencia del nodo*/
    PreferencesPosition next; /*!< Posicion siguiente en la lista */
};

// Funciones para el manejo de una lista de preferencias
PreferencesList create_empty_preferencesList(PreferencesList preferencesList);
void delete_preferencesList(PreferencesList preferencesList);
bool is_empty_preferencesList(PreferencesList preferencesList);
void print_preferencesList(PreferencesList preferencesList);
PreferencesPosition find_preference( PreferencesList preferencesList, char *key);
PreferencesPosition find_preference_prev(PreferencesPosition P, PreferencesList preferencesList);
PreferencesPosition insert_preference(PreferencesPosition prevPosition, char* key);
void delete_preference(PreferencesPosition P, PreferencesList preferencesList);

// Funciones de interaccion con el usuario
PreferencesPosition preferencesList_first(PreferencesList preferencesList);
PreferencesPosition preferencesList_last(PreferencesList preferencesList);
PreferencesPosition preferencesList_advance(PreferencesPosition P);



#endif