#include "errors.h"
#include "graph.h"
#include "hash.h"
#include "friend_list.h"
#include "user.h"
#include "utilities.h"
#include "preferences.h"
#include "jaccard.h"


int main(int argc, char **argv){

    char* root_dir = get_terminal_parameters(argc, argv);
    if(root_dir == NULL){
        exit(-1);
    }
    if(strcmp(root_dir, "create") == 0){
        printf("Creando usuario\n");
        char name[MAX_NAME];
        char description[MAX_DESCRIPTION];
        int age;
        printf("ingrese un nombre (max %d caracteres): ", MAX_NAME - 1);

        if (scanf("%s", name) != 1 || strlen(name) >= MAX_NAME) {
            printf("Error: nombre no valido\n");
            exit(-1);
        }
        printf("ingrese una descripcion (max %d caracteres): ", MAX_DESCRIPTION - 1);
        if (scanf(" %[^\n]", description) != 1 || strlen(description) >= MAX_DESCRIPTION) {
            printf("Error: descripción no valida o muy larga\n");
            exit(-1);
        }
        printf("ingrese una edad (18-60): ");
        if (scanf("%d", &age) != 1 || age < 18 || age > 60 ){
            printf("Error: edad no valida\n");
            exit(-1);
        }
        UserList users = make_empty_userList(NULL);
        if (users == NULL) {
            exit(-1);
        }
        UserPosition newUser = insert_userList_user(users, users, name, description, age);
        if (newUser == NULL) {
            printf("Error: no se pudo crear el usuario\n");
            delete_userList(users);
            exit(-1);
        }
        printf("Ingresando gustos aleatorios\n");

        char interest[MAX_INTERESTS][MAX_INTEREST_NAME];
        fill_array_with_interests_from_file(interest);
        for(int i = 0; i < 10; i++){
            if (!insert_interestNode(interest[rand() % MAX_INTERESTS], newUser->interests) && search_int_in_interestTable(newUser->interests, interest[rand() % MAX_INTERESTS]) == NULL) {
                break;
            }
        }
        create_user_folder("data/users/", newUser);
        save_user_info_in_files(newUser);
        printf("Usuario creado con exito\n");
        delete_userList(users);
        exit(0);
    }


    srand(time(NULL));

    Graph graph = create_graph(NULL);
    UserList users = make_empty_userList(NULL);
    users =get_users_from_directory("data/users/", NULL);
    graph = get_conections_from_directory("data/users/", users, graph);
    graph = get_preferences_from_directory("data/users/", users, graph);

    char interest[MAX_INTERESTS][MAX_INTEREST_NAME];
    fill_array_with_interests_from_file(interest);

    char stockNames[MAX_STOCK_NAMES][MAX_NAME];
    fill_array_with_names_from_file(stockNames);
    //printf("todo bien1\n");
    //UserPosition activeUser = find_userList_user(users, root_dir);
    //printf("todo bien2\n");
    GraphPosition activeUser = find_graphNode(root_dir, graph);
    //printf("todo bien3\n");
    if(activeUser == NULL){
        printf("Usuario no encontrado\n");
        exit(-1);
    }
    //printf("todo bien4\n");


    while(1){

        printf("Usuario activo: %s\n", activeUser->user->name);
        printf("1. Ver perfil\n");
        printf("2. Ver amigos\n");
        printf("3. Ver seguidores\n");
        printf("4. Ver seguidos\n");
        printf("5. Realizar post\n");
        printf("6. Buscar usuario\n");
        printf("7. Salir\n");
        char postContent[MAX_DESCRIPTION];
        char search[MAX_NAME];
        int option;
        scanf("%d", &option);
        switch(option){
            case 1:
                printf(CLEAR_SCREEN);
                print_user(activeUser->user);
                break;
            case 2:
                printf(CLEAR_SCREEN);
                printf("Amigos del usuario: %s\n", activeUser->user->name);
                print_friendList(activeUser->user->mutuals);

                FriendPosition P = activeUser->user->mutuals->next;
                printf("\nSus Posts son:\n");
                while(P != NULL ){
                    if(P->graphNode->user->posts->next == NULL){
                        P = P->next;
                        continue;
                    }
                    printf("Usuario: %s\n", P->graphNode->user->name);
                    printf("Posts:\n");
                    print_preferencesList(P->graphNode->user->posts);
                    P = P->next;
                }
                break;
            case 3:
                printf(CLEAR_SCREEN);
                printf("Seguidores del usuario: %s\n", activeUser->user->name);
                print_friendList(activeUser->followers);
                //FriendPosition P = activeUser->followers->next;
                break;
            case 4:
                printf(CLEAR_SCREEN);
                printf("Seguidos por el usuario: %s\n", activeUser->user->name);
                print_friendList(activeUser->followers);
                break;
            case 5:
                printf(CLEAR_SCREEN);
                printf("Escribe tu post: ");
                getchar();
                if (fgets(postContent, MAX_DESCRIPTION, stdin) != NULL) {
                    if (postContent[0] == '\n') {
                        printf("Post vacio\n");
                        break;
                    }
                    // Remove trailing newline if present
                    size_t len = strlen(postContent);
                    if (len > 0 && postContent[len-1] == '\n') {
                        postContent[len-1] = '\0';
                    }
                    if (strlen(postContent) >= MAX_DESCRIPTION) {
                        printf("Post muy largo\n");
                        break;
                    }
                    insert_preference(activeUser->user->posts, postContent);
                    print_preferencesList(activeUser->user->posts);
                    printf("Post realizado %s\n", postContent);
                }
                break;
            case 6:
                printf(CLEAR_SCREEN);
                printf("Escribe el nombre del usuario a buscar: ");
                scanf("%s", search);
                if(strlen(search) > MAX_NAME){
                    printf("Nombre muy largo\n");
                    break;
                }
                if(search[0] == '\0'){
                    printf("Nombre vacio\n");
                    break;
                }
                UserPosition searchUser = find_userList_user(users, search);
                if(searchUser == activeUser->user){
                    printf("Usuario activo\n");
                }
                if(searchUser == NULL){
                    printf("Usuario no encontrado\n");
                }
                else{
                    print_user(searchUser);
                }
                break;
            case 7:
                printf(CLEAR_SCREEN);
                delete_userList(users);
                delete_graph(graph);
                exit(0);
                break;
            default:
                printf("Opcion no valida\n");
                break;
        }

        UserPosition P = users->Next;
        while(P != NULL){
            save_user_info_in_files(P);
            P = P->Next;
        }

        P = users->Next;
        create_users_batch(users, graph, interest, stockNames);
        while(P != NULL){
            make_recomendations_for_user(P, users, graph);
            P = P->Next;
        }

    }

    //printf("hola");

    //UserPosition P = users->Next;



    //create_users_batch(users, graph, interest, stockNames);
 


    //UserPosition newuser = insert_userList_user(users, users, "newuser", "newuser", 20);
    //insert_interestNode("newinterest", newuser->interests);
    //insert_interestNode("newinterest2", newuser->interests);
    //insert_graphNode(newuser, graph);
    //create_user_folder("data/users/", newuser);

    //P=users->Next;
    //while(P != NULL){
    //    make_recomendations_for_user(P, users, graph);
    //    P = P->Next;
   // }


    //print_userList(users);
    //print_graph(graph);
    //delete_userList(users);
    //delete_graph(graph);
    return 0;

}