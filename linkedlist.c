#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkedlist.h"
#include "coursework.h"

//struct node {
//struct process * data;
//int key;
//struct node * next;

struct node *head = NULL;
struct node *current = NULL;
struct node *tail = NULL;


//display the list
void printList(struct node *ptr) {

	printf("[ ");

	//start from the beginning
	if (ptr == NULL){
        printf("ptr equals null");
    }

    while(ptr != NULL) {
		printf("(Key: %d, ProcessId: %d, BurstTime: %d) ",ptr->key, ptr->data->iProcessId, ptr->data->iBurstTime);
		ptr = ptr->next;
	}

	printf(" ]\n");
}

//insert process into linked list in order of burstTime
void insertByBurstTime(int key, struct node **current_node, struct process *process_to_insert, struct node *tail) {
    // head->
    // head-> (node1) <- tail
    // head-> (node1) -> (node2) <- tail

    // Handle an empty linked list
    if (*current_node == NULL) {
       //creates link and add info
		*current_node = (struct node*) malloc(sizeof(struct node));
		(*current_node)->key = key;
		(*current_node)->data = process_to_insert;
        //link it to other nodes
		(*current_node)->next = NULL;
        printf("current_node was Null \n");
        return;
    } else if ((*current_node)->data->iBurstTime < process_to_insert->iBurstTime) {
        // current_node isn't empty, current_node->iBurstTime is smaller than process_to_insert's
        // End of the list, insert after current_node
        if ((*current_node)->next == NULL) {
            struct node *next_node = (struct node*) malloc(sizeof(struct node));
			(*current_node)->key = key;
            next_node->data = process_to_insert;
			(*current_node)->next = next_node;
            printf("current_node->next was null");
            return;
        } else {
            // there is something after current_node->next, recurse:
            struct node *tail = NULL;
            insertByBurstTime(key, &(*current_node)->next, process_to_insert, tail);
            printf("current_node->nest was not empty");
        }
    } else {
        // current_node isn't empty, current_node->iBurstTime is larger than process_to_insert's
        struct node *insert_me = (struct node*) malloc(sizeof(struct node));
        insert_me->key = key;
        insert_me->data = process_to_insert;

        // head -> next
        // head -> insert_me -> next
        // Break apart & re-link the linked list
        struct node *next = (*current_node)->next;
		(*current_node)->next = insert_me;
        insert_me->next = next;
        printf("just a normal insert was done");
    }
}


//insert link at the first location
void insertFirst(int key, struct process *data) {
	//create a link
	struct node *link = (struct node*) malloc(sizeof(struct node));

	link->key = key;
	link->data = data;

	//point it to old first node
	link->next = head;

	//point first to new first node
	head = link;
}

//insert link at the last location
void insertLast(int key, struct process *data) {
    //create a link
    struct node *link = (struct node*) malloc(sizeof(struct node));

    link->key = key;
    link->data = data;

    //point new tail to old tail node
    link->next = tail;

    //point tail to new tail node
    tail = link;
}

//delete first item
struct node* deleteFirst() {

	//save reference to first link
	struct node *tempLink = head;

	//mark next to first link as first
	head = head->next;

	//return the deleted link
	return tempLink;
}


int length() {
	int length = 0;
	struct node *current;

	for(current = head; current != NULL; current = current->next) {
		length++;
	}

	return length;
}

//find a link with given key
struct node* find(int key) {

	//start from the first link
	struct node* current = head;

	//if list is empty
	if(head == NULL) {
		return NULL;
	}

	//navigate through list
	while(current->key != key) {

		//if it is last node
		if(current->next == NULL) {
			return NULL;
		} else {
			//go to next link
			current = current->next;
		}
	}

	//if data found, return the current Link
	return current;
}

//delete a link with given key
struct node* delete(int key) {

	//start from the first link
	struct node* current = head;
	struct node* previous = NULL;

	//if list is empty
	if(head == NULL) {
		return NULL;
	}

	//navigate through list
	while(current->key != key) {

		//if it is last node
		if(current->next == NULL) {
			return NULL;
		} else {
			//store reference to current link
			previous = current;
			//move to next link
			current = current->next;
		}
	}

	//found a match, update the link
	if(current == head) {
		//change first to point to next link
		head = head->next;
	} else {
		//bypass the current link
		previous->next = current->next;
	}

	return current;
}

/*void sort() {

	int i, j, k, tempKey, tempData;
	struct node *current;
	struct node *next;

	int size = length();
	k = size ;

	for ( i = 0 ; i < size - 1 ; i++, k-- ) {
		current = head;
		next = head->next;

		for ( j = 1 ; j < k ; j++ ) {

			if ( current->data > next->data ) {
				tempData = current->data;
				current->data = next->data;
				next->data = tempData;

				tempKey = current->key;
				current->key = next->key;
				next->key = tempKey;
			}

			current = current->next;
			next = next->next;
		}
	}
}*/

void reverse(struct node** head_ref) {
	struct node* prev   = NULL;
	struct node* current = *head_ref;
	struct node* next;

	while (current != NULL) {
		next  = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}

	*head_ref = prev;
}

