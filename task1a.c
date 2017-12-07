#include <stdio.h>
#include <stdlib.h>
#include "coursework.h"
#include "linkedlist.h"

int main() {
  // defining Variables
  struct node *head = NULL;
  struct node *current = NULL;
  struct node *tail = NULL;
  struct timeval *StartTime = (struct timeval *)malloc(sizeof(struct timeval));
  struct timeval *EndTime = (struct timeval *)malloc(sizeof(struct timeval));
  struct process *myProcessPtr;

  // Creating 10 Processes by calling generateProcess
  for (int i = 0; i < 10; i++) {
    myProcessPtr = generateProcess();
    head = insertByBurstTime(head, myProcessPtr, i);
  }
  printList(head);

  struct node *currentProcessPtr = NULL;
  currentProcessPtr = head;

  while (currentProcessPtr != NULL) {  // stop if list is empty

    // while (myProcessPtr->iState == 1) {  //skip node if already run and
    // istate changed
    printf("Getting ready to run SJF for process: %d\n",
           currentProcessPtr->data->iProcessId);
    simulateSJFProcess(currentProcessPtr->data, StartTime, EndTime);
    if (currentProcessPtr->data->iState == FINISHED) {
      printf(
          " -- Process: %d (index %d) finished. Creation time: %d, StartTime: "
          "%d, EndTime, %d\n",
          currentProcessPtr->data->iProcessId, currentProcessPtr->key,
          currentProcessPtr->data->oTimeCreated, *StartTime, *EndTime);

      if (currentProcessPtr->next != NULL) {
        currentProcessPtr = currentProcessPtr->next;
        deleteNode(&head, currentProcessPtr->previous);
      } else {
        struct node *tmp = currentProcessPtr;
        currentProcessPtr = currentProcessPtr->next;
        deleteNode(&head, tmp);
      }
    }
  }

  // and write output to file

  /*//write to file
  FILE *f = fopen("task1a.txt", "w");
  if (f == NULL) {
          printf("Error opening file!\n");
          exit(1);
  }
  // print some text
  const char *text = "Write this to the file";
  fprintf(f, "Some text: %s\n", text);

  // print integers and floats
  int m = 1;
  float py = 3.1415927;
  fprintf(f, "Integer: %d, float: %f\n", i, py);

  // printing single characters
  char c = 'A';
  fprintf(f, "A character: %c\n", c);

  fclose(f);*/
}
