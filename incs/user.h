/**
 * @User user.h
 * @author Pendiente
 * @brief Cabecera para funciones de user.c
 */

#ifndef USER_H
#define USER_H

typedef struct _UserNode UserNode;
typedef UserNode *PtrToUserNode;
typedef PtrToUserNode UserList;
typedef PtrToUserNode UserPosition;

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "graph.h"
#include "errors.h"
#include "utilities.h"
#include "preferences.h"

/** \struct _UserNode
 *  @brief Estructura que representa una lista de usuarios
*/
struct _UserNode {
    int friendCount;
    int preferencesCount;
    char* name;
    FriendList mutuals;
    PreferencesList preferences;
    PtrToUserNode Next;
};

// funciones para el manejo de usuarios
UserList make_empty_userList(UserList L);
UserPosition insert_userList_user(UserList L, UserPosition Prev, char* name);
void delete_userList(UserList L);
void print_userList(UserList L);
UserList get_users_from_directory(char *directory, UserList list);
int count_usersList(UserList L);
void delete_userList_user(UserList L, UserPosition user);
UserPosition find_userList_user(UserList L, char* userName);
UserPosition find_userList_prev_user(UserList L, UserPosition user);


#endif