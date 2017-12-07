#include "linkedlist.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coursework.h"

// display the list
void printList(struct node *ptr) {
  printf("[ ");
  while (ptr != NULL) {
    printf("(Key: %d, ProcessId: %d, BurstTime: %d) ", ptr->key,
           ptr->data->iProcessId, ptr->data->iBurstTime);
    ptr = ptr->next;
  }
  printf(" ]\n");
}

void printProcess(struct process *process) {
  printf("{");
  printf("ProcessId: %d ", process->iProcessId);
  // printf("TimeCreated: %ld", process->oTimeCreated);
  printf("BurstTime: %d ", process->iBurstTime);
  // printf("oNext: %ld", process->oNext);
  printf("iState: %d ", process->iState);
  printf("iEventType: %d ", process->iEventType);
  printf("}\n");
}

// Function to insert the given data and return a pointer to the head node.
struct node *insertByBurstTime(struct node *head, struct process *data,
                               int key) {
  // reserve memory for the newNode & set the data
  struct node *newNode = (struct node *)malloc(sizeof(struct node));
  newNode->data = data;
  newNode->key = key;  // This is redundant btw. data->iProcessId will also give
                       // you the index.

  // Special case - the list is empty
  if (head == NULL) {
    newNode->next = NULL;  // Set next and previous pointers to NULL
    newNode->previous = NULL;
    // This node is the only node so return it as the head node.
    return newNode;
  }

  if (head->data->iBurstTime >= newNode->data->iBurstTime) {
    // If the node's needs to be inserted at the beginning of the list set the
    // next pointer of the newNode to point to the current head and set the
    // previous pointer to NULL. (It's now the beginning of the list)
    newNode->next = head;
    newNode->previous = NULL;
    // Update head's previous pointer to point to newNode
    head->previous = newNode;
    // Since it's at the front, this node now becomes the head node
    head = newNode;
  } else {
    // Figure out where to insert the new node using a temporary current node
    struct node *current = head;
    while (current->next != NULL &&
           current->next->data->iBurstTime < newNode->data->iBurstTime) {
      current = current->next;
    }
    // newNode lies between current and current->next
    newNode->previous = current;
    newNode->next = current->next;
    // It might happen that newNode's position is at the end.
    // In that case we cannot update the current->next's (which is NULL)
    // previous pointer
    if (current->next != NULL) {
      current->next->previous = newNode;
    }
    // Update the next pointer of current to point to this new node.
    current->next = newNode;
  }
  // Finally return the head pointer.
  return head;
}

/*
// insert link at the first location
void insertFirst(int key, struct process *data) {
  // create a link
  struct node *link = (struct node *)malloc(sizeof(struct node));

  link->key = key;
  link->data = data;

  // point it to old first node
  link->next = head;

  // point first to new first node
  head = link;
}
*/

// insert link at the last location
void insertLast(int key, struct node **current_node,
                struct process *process_to_insert) {
  // creates link and add info
  if (*current_node == NULL) {
    *current_node = (struct node *)malloc(sizeof(struct node));
    (*current_node)->key = key;
    (*current_node)->data = process_to_insert;

    // link it to other nodes
    (*current_node)->next = NULL;
    (*current_node)->previous = NULL;

  } else if ((*current_node)->next != NULL) {
    insertLast(key, &((*current_node)->next), process_to_insert);

  } else {
    struct node *insert_me = (struct node *)malloc(sizeof(struct node));
    insert_me->key = key;
    insert_me->data = process_to_insert;

    // link it to other nodes

    (*current_node)->next = insert_me;
    insert_me->next = NULL;
    insert_me->previous = (*current_node);
  }
}

// delete a link with given key
/* Function to delete a node in a Doubly Linked List.
head_ref --> pointer to head node pointer.
del --> pointer to node to be deleted. */
void deleteNode(struct node **head_ref, struct node *del) {
  // base case 
  if (*head_ref == NULL || del == NULL) return;

  // If node to be deleted is head node 
  if (*head_ref == del) *head_ref = del->next;

  // Change next only if node to be deleted is NOT the last node 
  if (del->next != NULL) del->next->previous = del->previous;

  // Change previous only if node to be deleted is NOT the first node 
  if (del->previous != NULL) del->previous->next = del->next;

  // Finally, free the memory occupied by del
  free(del);
  return;
}

/*

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



void sort() {

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
}

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

*/
