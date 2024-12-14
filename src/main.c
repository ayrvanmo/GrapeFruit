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
    Graph graph = create_graph(NULL);
    UserList users = make_empty_userList(NULL);
    users =get_users_from_directory(root_dir, NULL);
    graph = get_conections_from_directory(root_dir, users, graph);
    graph = get_preferences_from_directory(root_dir, users, graph);
    printf("hola");

    UserPosition P = users->Next;



    //print_userList(users);
    //print_graph(graph);
    delete_graph(graph);
    delete_userList(users);
    return 0;

}