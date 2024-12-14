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
    srand(time(NULL));

    Graph graph = create_graph(NULL);
    UserList users = make_empty_userList(NULL);
    users =get_users_from_directory("data/users/", NULL);
    graph = get_conections_from_directory("data/users/", users, graph);
    graph = get_preferences_from_directory("data/users/", users, graph);

    char interest[MAX_INTERESTS][MAX_INTEREST_NAME];
    fill_array_with_interests_from_file(interest);

    for(int i = 0; i<MAX_INTERESTS; i++){
    //   printf("%s\n", interest[i]);
    }

    char stockNames[MAX_STOCK_NAMES][MAX_NAME];
    fill_array_with_names_from_file(stockNames);

    for(int i = 0; i<MAX_STOCK_NAMES; i++){
    //    printf("%s\n", stockNames[i]);
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

    print_userList(users);
    //print_graph(graph);
    delete_graph(graph);
    delete_userList(users);
    return 0;

}