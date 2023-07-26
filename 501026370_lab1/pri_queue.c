#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"
/** @file pri_queue.c */
static Node_ptr_t head = NULL;
/**
 * Insert a Node into a priority queue.
 * @param priority
 * @param data
 * @author STUTI PATEL
 */
void PQ_insert(int priority, char * data) {
    Node_ptr_t new; //Creating new node pointer, new 
    Node_ptr_t tmp; //Creating temporary node, tmp
    new=(Node_ptr_t)malloc(sizeof(Node_t)); //Setting the memory size of node new as Node_t (according to pri_queue.h)
    new->data = data; //initializing "data" variable for node new as data
    new->priority = priority;//initializing "priority" variable for node new as priority 
    
    tmp=(Node_ptr_t)malloc(sizeof(Node_t));
    tmp->data = data;
    tmp->priority = priority;
    //When head node is null, move to the next node (new)
    if (head == NULL){
        new->next = NULL;
        head=new;
    }
    
    /*Otherwise if the priority of head node is less than priority of new node, 
    set node next to node new as head node*/
    else if ((head->priority) < (new->priority)){
        new->next = head;
        head=new;
    }
    
    //
    else{
        for (tmp=head;tmp->next->next != NULL && new->priority < tmp->next->priority; tmp=tmp->next){
        }
        new->next = tmp->next;
        tmp->next = new;
    }
}
/**
 * Delete and return the node with the highest priority.
 * @return The highest priority Node.
 */
Node_ptr_t PQ_delete() {
    Node_ptr_t return_n = head;
    head=head->next;
    return return_n;
}

/**
 * Do NOT modify this function.
 * @return A pointer to the head of the list.  (NULL if list is empty.)
 */
Node_ptr_t PQ_get_head() {
    return head;
}

/**
 * Do NOT modify this function.
 * @return the number of items in the queue
 */
int PQ_get_size() {
    int size = 0;
    Node_ptr_t tmp;
//    if(head != NULL){
//        fprintf(stderr, "head priority is: %d\n",head->priority);
//    }
    for(tmp = head; tmp != NULL; tmp = tmp->next, size++){
    }
    return size;
}