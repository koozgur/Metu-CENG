#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct QueryNode
{
    char *query;
    struct QueryNode *prev;
    struct QueryNode *next;
} QueryNode;

typedef struct CountNode
{
    int count;
    struct CountNode *prev;
    struct CountNode *next;
    QueryNode **querylist;
} CountNode;


char character;
int i= 0, j = 0, k = 0, a;
int initialize_length;
int current_line;
char* input_string;
int input_number;
int searching, minimum_count_value, null_var;
char* deleted_string;
int empty;

QueryNode* QueryTable[10];
QueryNode* created_query;
CountNode** HEAD;
CountNode* created_count;
CountNode* copy_head;
QueryNode* node_of_deletion_next;
QueryNode* update_that;
QueryNode* traverse_to_print;

QueryNode* make_query_node(char* string){
    int i = 0;
    QueryNode* ptr;
    ptr = (QueryNode*)malloc(sizeof(QueryNode));
    ptr -> query = (char*)malloc(sizeof(char)* 6);
    strcpy(ptr-> query, string);
    ptr -> prev = NULL;
    ptr -> next = NULL;
    return ptr;
}

CountNode* make_count_node(int number){
    CountNode* ptr;
    ptr = (CountNode*)malloc(sizeof(CountNode));
    ptr -> count = number;
    ptr -> prev = NULL;
    ptr -> next = NULL;
    ptr -> querylist = (QueryNode**)malloc(sizeof(QueryNode* ));
    *(ptr -> querylist) = NULL;
    return ptr;
}

void insert_count(CountNode** head, CountNode* node){
    CountNode* head_copy = *head;
    if(*head == NULL){
        *head = node;
        return;
    }
    else{
        while(head_copy != NULL){
            if(head_copy -> count == node -> count){
                return;}
            head_copy = head_copy -> next;
        }
        head_copy = *head;
        if(node -> count < (*head) -> count){
            node -> next = *head;
            (* head) -> prev = node;
            *head = node;
            return;
        }
        while(head_copy-> next && (node-> count > head_copy -> count)) /* son node'a kadar gidecek */
            head_copy = head_copy -> next;
        if(node -> count < head_copy -> count){/* hemen önüne insert*/
            (head_copy -> prev) -> next = node;
            node -> next = head_copy;
            node-> prev = head_copy -> prev;
            head_copy -> prev = node;
        } 
        else{  /* sona insert*/ 
            head_copy -> next = node;
            node -> prev = head_copy;
        }
        return;
    }
    
}

void insert_query(QueryNode** head, QueryNode* node){
    QueryNode* ptr = *head; /* structa giden */
    int i = 0;
    if(ptr == NULL){
        *head = node;
        return;
    }
    else{
        while(1){
            if(strcmp(node -> query, ptr -> query) < 0){
                if(i == 0){
                    node -> next = *head;
                    (*head) -> prev = node;
                    *head = node;
                    return;
                }
                else{
                    node -> prev = ptr -> prev;
                    node -> next = ptr;
                    (ptr -> prev) -> next = node;
                    ptr -> prev = node;
                    return;
                }
           }
           if(ptr -> next == NULL)
              break;
           i++;
           ptr = ptr -> next;
        }
        ptr -> next = node;
        node -> prev = ptr;
        return;
    }
}

int return_query_count(CountNode** head, char* string){
    CountNode* ptr = *head;
    QueryNode* down_ptr;
    int number;
    int found = 0;
    while(ptr != NULL){
        number = ptr -> count;
        down_ptr = *(ptr -> querylist);
        while(down_ptr != NULL){
            if(strcmp(down_ptr -> query,string) == 0){
                found = 1;
                break;}
            down_ptr = down_ptr -> next;    
        }
        if(found == 1)
            return number;
        ptr = ptr -> next;
    }
    return 0;
    
}

char* remove_query(CountNode** main_head){
    CountNode* head = *main_head;
    QueryNode** head_q;
    char *del_string;
    del_string = malloc(sizeof(char) * 6);
    head_q = (*main_head) -> querylist;
    while( *head_q == NULL){
        head = head-> next;
        head_q = head -> querylist;
    }
    if( (*head_q) -> next == NULL){
        strcpy(del_string,(*head_q) -> query);
        /*del_string = (*head_q) -> query; */
        *head_q = NULL;
    }
    else{
        strcpy(del_string,(*head_q) -> query);
        /*del_string = (*head_q) -> query;*/
        ((*head_q)->next) -> prev = *head_q;
        *head_q = (*head_q) -> next;
    }
    return del_string;
}

QueryNode** search_for_count(CountNode** head, int number){
    CountNode* ptr = *head;
    while(ptr!=NULL){
        if(ptr -> count == number)
            return ptr -> querylist;
        else
           ptr = ptr -> next;
    }
    printf(" hatalı sonuç!");
}


void remove_query_middle(CountNode** main_head, int value, QueryNode* be_removed){
    CountNode* ptr = *main_head;
    QueryNode** ptr_2;
    QueryNode* ptr_3;
    while(ptr !=NULL){
        if(ptr -> count == value)
            break;
        ptr = ptr -> next;
    }
    ptr_2 = ptr -> querylist;
    if( strcmp((*ptr_2) -> query,be_removed -> query) == 0){
        if( (*ptr_2) -> next!= NULL){
            ((*ptr_2) -> next) -> prev = *ptr_2;
            *ptr_2 = (*ptr_2) -> next;
            return;}
        else{
            (*ptr_2) = NULL;
            return;
        }
    }
    ptr_3 = *ptr_2;
    while( ptr_3 -> next != NULL){
        if( strcmp(ptr_3 -> query,be_removed -> query) == 0)
            break;
        ptr_3 = ptr_3 -> next;
    }
    if(ptr_3 -> next == NULL){
        (ptr_3 -> prev) -> next = NULL;
        return;
    }
    else{
        (ptr_3 -> prev) -> next = ptr_3 -> next;
        (ptr_3 -> next) -> prev = ptr_3 -> prev;
        return;
    }
}


int main() {
    input_string = (char *)malloc(sizeof(char)* 6);
    HEAD = (CountNode**)malloc(sizeof(CountNode*));
    *HEAD = NULL;
    for(i = 0; i < 10; i++ ){
        QueryTable[i] = NULL;
    }
    scanf(" %d ", &initialize_length);
    if(initialize_length > 0){
        i = 0;
        for(current_line = 1; current_line <= initialize_length;current_line++, i++){
            a = 0;
            scanf(" %s", input_string);
            created_query = make_query_node(input_string);
            scanf(" %d", &input_number);
            created_count = make_count_node(input_number);
            
            insert_count(HEAD, created_count);
            insert_query(search_for_count(HEAD, input_number), created_query); /* insert edilecek count no.su bulundu */
            QueryTable[i] = created_query;
        }
        
    }
    scanf(" %d", &input_number);
    for(i = 0 ; i < input_number ; i++){
        copy_head = *HEAD;
        a = 0;
        scanf(" %s", input_string);
        searching = 0;
        null_var = 0;
        j = 0;
        while(j < 10){
            if(QueryTable[j] != NULL){
                if(strcmp(QueryTable[j] -> query, input_string) == 0){
                    searching = 1;
                }
            }
            else
                null_var = 1;
            j++;
        }
        if(searching == 0 && null_var == 1){ /* bulamadı ve boşluk var */
            created_query = make_query_node(input_string);
            for(k = 0; k < 10 ; k++){
                if(QueryTable[k] == NULL){
                     QueryTable[k] = created_query;
                     break;
                 }
            }
            if( (*HEAD) -> count == 1)
                insert_query((*HEAD) -> querylist, created_query);
            else{
                created_count = make_count_node(1);
                insert_count(HEAD, created_count);
                insert_query( (*HEAD) -> querylist, created_query);
            }
        }
        else if(searching == 0 && null_var == 0 ){ /*en ufak silinir */  /*bu parça bakılacak */
            deleted_string = malloc(sizeof(char) * 6);
            strcpy(deleted_string, remove_query(HEAD));
            k = 0;
            while(k < 10){
                if(strcmp(QueryTable[k] -> query,deleted_string) == 0){
                    QueryTable[k] = NULL;
                    break;
                }
                k++;
            }
            for(k = 0; k< 10; k++){
                if(QueryTable[k] == NULL){
                    created_query = make_query_node(input_string);
                    QueryTable[k] = created_query;
                    break;
                }
             }
             if( (*HEAD) -> count == 1)
                insert_query( (*HEAD) -> querylist, created_query);
            else{
                created_count = make_count_node(1);
                insert_count(HEAD, created_count);
                insert_query( (*HEAD) -> querylist, created_query);
            }
            
        }
        else if(searching == 1){
            /* içeridedir update edilir */
            a = return_query_count(HEAD, input_string);
            /* int a içeren count node var mı diye bak yoksa oluştur varsa direkt insert at */
            copy_head = *HEAD;
            searching = 0;
            while(copy_head != NULL){
                if(copy_head -> count == a+1){
                    searching = 1;
                    break;
                }
                copy_head = copy_head -> next;
            }
            for(k = 0; k< 10; k++){
                if(strcmp(QueryTable[k] -> query,input_string) == 0){
                    update_that = QueryTable[k];
                    break;}
            }
            remove_query_middle(HEAD,a,update_that);
    
            if(searching == 0){
                created_count = make_count_node(a+1);
                insert_count(HEAD, created_count);
                insert_query(created_count-> querylist, update_that);
            }
            else if(searching == 1){
                insert_query(copy_head -> querylist, update_that);
            }
        }    
        
    }
    copy_head = *HEAD;
    
    while(copy_head != NULL){
        empty = 1;
        traverse_to_print = *(copy_head -> querylist);
        if(traverse_to_print != NULL){
            printf("%d",copy_head -> count);
            empty = 0;
        }
        while(traverse_to_print !=NULL){
            printf(" %s", traverse_to_print -> query);
            traverse_to_print = traverse_to_print -> next;
        }
        if(empty == 0)
            printf("\n");
        copy_head = copy_head -> next;
    }
    return 0;
}
