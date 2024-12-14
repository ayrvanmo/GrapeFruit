#include "jaccard.h"



double calculate_jaccard(UserPosition user1, UserPosition user2)
{
    int insersection_count = 0;
    int union_count = 0;

    for(int i = 0; i< INTEREST_TABLE_SIZE; i++){
        InterestList auxList = user1->interests[i].interestList;
        if(auxList->next != NULL){
            auxList = auxList->next;
        }

        while( auxList->key != NULL){
            union_count++;

            if(search_int_in_interestTable(user2->interests, auxList->key) != NULL){
                insersection_count++;
            }

            auxList = auxList->next;
            if(auxList == NULL){
                break;
            }
        }
    }

    for(int i = 0; i<INTEREST_TABLE_SIZE ; i++){
        InterestList auxList = user2->interests[i].interestList;
        if(auxList->next != NULL){
            auxList = auxList->next;
        }

        while( auxList->key != NULL){
            if(search_int_in_interestTable(user1->interests, auxList->key) == NULL){
                union_count++;
            }
            auxList = auxList->next;
            if(auxList == NULL){
                break;
            }
        }

    }

    if(union_count == 0){
        return 0;
    }

    return (double)insersection_count/union_count;

}