#include <stdio.h>
#include <stdlib.h>
#include "coursework.h"
#include "linkedlist.h"

int main() {
  //defining Variables
  struct node *head = NULL;
  struct node *current = NULL;
  struct node *tail = NULL;
  struct timeval *StartTime = (struct timeval *)malloc(sizeof(struct timeval));
  struct timeval *EndTime = (struct timeval *)malloc(sizeof(struct timeval));
  struct process *myProcessPtr;
  //int n = 0, sumRT, sumTAT;
  float averageRTinsec, averageTATinsec, n = 0, sumRT, sumTAT;

  FILE *f = fopen("task1a.txt", "w");
  if (f == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  //creating 10 Processes by calling generateProcess
  for (int i = 0; i < 10; i++) {
    myProcessPtr = generateProcess();
    head = insertByBurstTime(head, myProcessPtr, i);
  }

// Running Processes through CPU
  struct node *currentProcessPtr = NULL;
  currentProcessPtr = head;

  while (currentProcessPtr != NULL) { // stop if list is empty
    int BurstTime = currentProcessPtr->data->iBurstTime;
    simulateSJFProcess(currentProcessPtr->data, StartTime, EndTime);
    if (currentProcessPtr->data->iState == FINISHED) {
        //Calculate ResponseTime and TurnAroundTime
        int ResponseTime = getDifferenceInMilliSeconds(currentProcessPtr->data->oTimeCreated, *StartTime);
        int TurnAroundTime = getDifferenceInMilliSeconds(currentProcessPtr->data->oTimeCreated, *EndTime);

        //print data to file
        fprintf(f, "Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Response Time = %d, Turn Around Time = %d \n",
        currentProcessPtr->data->iProcessId, BurstTime, currentProcessPtr->data->iBurstTime, ResponseTime, TurnAroundTime);

        //to data to calculate Averages
        n = n+1;
        sumRT +=  ResponseTime;
        sumTAT += TurnAroundTime;

        // and get rid of run processes
      if (currentProcessPtr->next != NULL) {
        currentProcessPtr = currentProcessPtr->next;
        deleteNode(&head, currentProcessPtr->previous);
      } else{
        struct node *tmp = currentProcessPtr;
        currentProcessPtr = currentProcessPtr->next;
        deleteNode(&head, tmp);
      }
    }
  }

   //Calculateing and printing Averages
    float averageRT = sumRT / n;
    fprintf(f, "Average Response Time =\"%.6f\" \n", averageRT);

    float averageTAT = sumTAT / n;
    fprintf(f, "Average Turn Around Time =\"%.6f\" \n", averageTAT);

  fclose(f);
}
