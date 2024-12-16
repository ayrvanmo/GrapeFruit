/**
 * @file preferences.c
 * @author Pendiente
 * @brief Funciones relacionadas con los comentarios de un usuario
 */


#include "preferences.h"

PreferencesList create_empty_preferencesList(PreferencesList preferencesList)
{
    if(!is_empty_preferencesList(preferencesList)){
        delete_preferencesList(preferencesList);
    }
    PreferencesList newList = (PreferencesList) malloc(sizeof(struct _PreferencesListNode));
    if(newList == NULL){
        print_error(200, NULL, NULL);
    }

    newList->next = NULL;
    return newList;
}

void delete_preferencesList(PreferencesList preferencesList)
{
    if(is_empty_preferencesList(preferencesList)){
        return;
    }
    PreferencesPosition aux = preferencesList->next;
    while(aux != NULL){
        delete_preference(aux, preferencesList);
        aux = preferencesList->next;
    }
    free(preferencesList);
}

bool is_empty_preferencesList(PreferencesList preferencesList)
{
    return preferencesList == NULL;
}

void print_preferencesList(PreferencesList preferencesList)
{
    PreferencesPosition P = preferencesList_first(preferencesList);
        printf("La lista de posts del usuario es la siguiente:\n");

    while(P != NULL){
        printf("Post: %s\n ", P->key);
        P = preferencesList_advance(P);
    }
}

PreferencesPosition find_preference( PreferencesList preferencesList, char *key)
{
    PreferencesPosition P = preferencesList->next;
    while(P != NULL && strcmp(P->key, key) != 0){
        P = P->next;
    }
    return P;
}

PreferencesPosition find_preference_prev(PreferencesPosition P, PreferencesList preferencesList)
{
    PreferencesPosition TmpCell = preferencesList;
    while(TmpCell->next != P){
        TmpCell = TmpCell->next;
    }
    return TmpCell;
}

PreferencesPosition insert_preference(PreferencesPosition prevPosition, char* key)
{
    PreferencesPosition newNode = (PreferencesPosition) malloc(sizeof(struct _PreferencesListNode));
    if(newNode == NULL){
        print_error(200, NULL, NULL);
    }
    newNode->key = (char*) malloc(strlen(key) + 1);
    if(newNode->key == NULL){
        print_error(200, NULL, NULL);
    }
    strcpy(newNode->key, key);
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    return newNode;
}

void delete_preference(PreferencesPosition P, PreferencesList preferencesList)
{
    if(P == NULL){
        print_error(203, NULL, NULL);
    }
    PreferencesPosition prev = find_preference_prev(P, preferencesList);
    prev->next = P->next;
    free(P->key);
    free(P);
}

// INTERACCION CON USUARIO

PreferencesPosition preferencesList_first(PreferencesList preferencesList)
{
    return preferencesList->next;
}

PreferencesPosition preferencesList_last(PreferencesList preferencesList)
{
    PreferencesPosition P = preferencesList;
    while(P->next != NULL){
        P = P->next;
    }
    return P;
}

PreferencesPosition preferencesList_advance(PreferencesPosition P)
{
    return P->next;
}
