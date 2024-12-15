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
#include <sys/types.h>
#include <sys/stat.h>
#include "graph.h"
#include "errors.h"
#include "utilities.h"
#include "preferences.h"
#include "interest.h"
#include "jaccard.h"


#define MAX_NAME 30
#define MAX_STOCK_NAMES 71
#define MAX_DESCRIPTION 200
#define MAX_INTEREST_NAME 25
#define MAX_INTERESTS 26

/** \struct _UserNode
 *  @brief Estructura que representa una lista de usuarios
*/
struct _UserNode {
    int friendCount;
    int preferencesCount;
    int age;
    char* name;
    char* description;
    InterestTable interests;
    PreferencesList posts;
    FriendList mutuals;
    PtrToUserNode Next;
};

// funciones para el manejo de usuarios
UserList make_empty_userList(UserList L);
UserPosition insert_userList_user(UserList L, UserPosition Prev, char* name, char* description, int age);
void delete_userList(UserList L);
void print_userList(UserList L);
UserList get_users_from_directory(char *directory, UserList list);
Graph get_conections_from_directory(char *directory, UserList list, Graph graph);
Graph get_preferences_from_directory(char *directory, UserList list, Graph graph);
int count_usersList(UserList L);
void delete_userList_user(UserList L, UserPosition user);
UserPosition find_userList_user(UserList L, char* userName);
UserPosition find_userList_prev_user(UserList L, UserPosition user);
void make_recomendations_for_user(UserPosition user, UserList list, Graph graph);
void create_users_batch(UserList list, Graph graph, char interests[MAX_INTERESTS][MAX_INTEREST_NAME], char names[MAX_STOCK_NAMES][MAX_NAME]);
void fill_array_with_interests_from_file(char array[MAX_INTERESTS][MAX_INTEREST_NAME]);
void fill_array_with_names_from_file(char array[MAX_STOCK_NAMES][MAX_NAME]);
void create_users_batch(UserList list, Graph graph, char interests[MAX_INTERESTS][MAX_INTEREST_NAME], char names[MAX_STOCK_NAMES][MAX_NAME]);
void create_user_folder(char *directory, UserPosition user);
void save_connections_in_files(Graph graph, UserPosition user);
void print_user(UserPosition user);
void save_user_info_in_files(UserPosition User);

#endif