#include <sys/time.h>

/* A linked list node */
struct node {
  struct process *data;
  int key;
  struct node *next;
  struct node *previous;
};

// struct node *head;
// struct node *current;
// struct node *tail;

// display the list
void printList();
// print processes data for debug
void printProcess(struct process *process);
// creates and inserts new node in list by order of burstTime
void insertByBurstTime(int key, struct node **current_node,
                       struct process *process_to_insert, struct node **tail);
// insert link at the first location
void insertFirst(int key, struct process *data);
// insert link at end of list
void insertLast(int key, struct node **current_node,
                struct process *process_to_insert);
// Function to delete a node in a Doubly Linked List.
// head_ref --> pointer to head node pointer.
// del --> pointer to node to be deleted.
void deleteNode(struct node **head_ref, struct node *del);
// delete first item
struct node *deleteFirst();
// length of List
int length();
// find a link with given key
struct node *find(int key);
// delete a link with given key
struct node *delete (int key);
// sort list
void sort();
// reverse sort list
void reverse(struct node **head_ref);
