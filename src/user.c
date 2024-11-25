/**
 * @User Users.c
 * @author
 * @brief Funciones para manejo de usuarios
*/
#include "user.h"

// /**
//  * @brief Consigue los usuarios de un directorio
//  * @param directory Directorio donde comienza la busqueda
//  * @param list Lista de usuarios
//  * @return Lista de usuarios
//  */
// UserList get_Users_from_directory(char *directory, UserList list)
// {
//     DIR *Dir;
//     struct dirent *Entry;

//     Dir = opendir(directory);

//     if(Dir == NULL){
//         print_error(305,directory,NULL);
//         return NULL;
//     }

//     if (list == NULL) {
//         list = make_empty_UserList(NULL);
//     }

//     while ((Entry = readdir(Dir)) != NULL) {
//         if (strcmp(Entry->d_name, ".") == 0 || strcmp(Entry->d_name, "..") == 0){
//             continue;
//         }

//         if (Entry->d_type == 8) { // usuario
//             unsigned long entryId;
//             char* entryPath;
//             char* entryName;

//             size_t routeLength = strlen(directory) + strlen(Entry->d_name) + 2;
//             entryPath = malloc(routeLength);
//             if (entryPath == NULL) {
//                 print_error(200,NULL,NULL);
//                 continue;
//             }

//             snprintf(entryPath, routeLength, "%s%s", directory, Entry->d_name);
//             entryId = Entry->d_ino;
//             entryName = get_only_UserName(entryPath);
//             if (entryName == NULL) {
//                 free(entryPath);
//                 continue;
//             }
//             insert_UserList_User(list, list, entryPath, entryName, entryId);
//         }

//         if (Entry->d_type == 4) {  // subdirectorio
//             size_t Length = strlen(directory) + strlen(Entry->d_name) + 2;
//             char *SubDir = malloc(Length);

//             if (SubDir == NULL) {
//                 print_error(200,NULL,NULL);
//                 continue;
//             }

//             snprintf(SubDir, Length, "%s/%s", directory, Entry->d_name);
//             get_Users_from_directory(SubDir, list);
//             free(SubDir);
//         }
//     }
//     closedir(Dir);
//     return list;
// }

/**
 * @brief Inserta un user en la lista de usuarios
 * @param L Lista en la que se desea insertar el usuario
 * @param Prev Nodo previo al que se desea insertar el usuario
 * @param UserPath Ruta del usuario
 * @param name Nombre del usuario
 * @param id Identificador del usuario
 * @return Puntero al usuario creado
*/
UserPosition insert_userList_user(UserList L, UserPosition Prev, char* userPath, char* name, unsigned long id)
{
    UserPosition TmpCell;
    TmpCell = malloc(sizeof(struct _UserNode));

    if (TmpCell == NULL){
        print_error(200,NULL,NULL);
    }

    TmpCell->userPath = userPath;
    TmpCell->name = name;
    TmpCell->id = id;
    TmpCell->Next = Prev->Next;
    Prev->Next = TmpCell;
    L->userCount++;
    return TmpCell;
}

/**
 * @brief imprime la lista de usuarios
 * @param L Lista de usuarios
 */
void print_userList(UserList L)
{
    UserPosition P = L->Next;
    printf("Lista de usuarios:\n");

    while (P != NULL) {
        printf("usuario: %s, Inodo(ID): %lu, Nombre: %s\n", P->userPath, P->id, P->name);
        P = P->Next;
    }
    printf("Numero de usuarios: %d\n", count_usersList(L));
}

/**
 * @brief Elimina la lista de usuarios
 * @param L Lista de usuarios
 */
void delete_userList(UserList L)
{
    UserPosition P = L->Next;

    while (P != NULL) {
        delete_userList_user(L, P);
        P = L->Next;
    }
    free(L);
}

/**
 * @brief Crea una lista de usuarios vacia
 * @param L Lista de usuarios
 * @return Lista de usuarios vacia
 */
UserList make_empty_userList(UserList L)
{
    if (L != NULL){
        delete_userList(L);
    }
    L = malloc(sizeof(struct _UserNode));
    if (L == NULL) {
        print_error(200,NULL,NULL);
    }
    L->Next = NULL;
    L->userCount = 0;
    return L;
}

/**
 * @brief Cuenta el numero de usuarios en la lista de usuarios
 * @param L Lista de usuarios
 * @return Numero de usuarios
 */
int count_usersList(UserList L)
{
    return L->userCount;
}

/**
 * @brief Elimina un usuario de la lista de usuarios
 * @param L Lista de usuarios
 * @param UserName Nombre del usuario a eliminar
 */
void delete_userList_user(UserList L, UserPosition user)
{
    if(user == NULL){
        print_error(203, NULL, NULL);
    }
    UserPosition prevNode = find_userList_prev_user(L, user);
    if(prevNode == NULL){
        print_error(301, NULL, NULL);
        return;
    }
    free(user->name);
    free(user->userPath);
    prevNode->Next = user->Next;
    free(user);
}

/**
 * @brief Encuentra un usuario en la lista de usuarios
 * @param L Lista de usuarios
 * @param UserName Nombre del usuario a buscar
 */
UserPosition find_userList_user(UserList L, char* userName)
{
    UserPosition P = L->Next;
    while (P != NULL && strcmp(P->name, userName) != 0) {
            P = P->Next;
    }
    return P;
}

/**
 * @brief Encontrar el usuario anterior a @p user en @p L
 * @param L Lista de usuarios
 * @param User Puntero a la estructura que contiene información sobre el usuario
 * @return Puntero a la estructura que contiene información sobre el usuario
*/
UserPosition find_userList_prev_user(UserList L, UserPosition user)
{
    UserPosition aux = L;
    while (aux != NULL && aux->Next != user)
    {
        aux = aux->Next;
    }
    return aux;
}
