/*In task 1, it is assumed that all processes are available upon start-up. This is usually not the case in practice,
nor can it be assumed that an infinite number of processes can simultaneously co-exist in an operating system
(which typically have an upper limit on the number of processes that can exist at any one time, determined by the
size of the process table).

You are therefore asked to implement the SJF algorithm from task 1a using a bounded buffer
(of which the size models the maximum number of processes that can co-exist). The bounded buffer must be implemented as
a linked list ordered by burst time and with a maximum capacity of N elements (where N equal to the maximum number of
processes and defined by BUFFER_SIZE in the header file coursework.h).

Since both the producer (which creates the processes)
and the consumer (which removes the processes and “runs” them by calling simulateSJFProcess()) manipulate the same data
structure/variables, synchronisation will be required. You are free to choose how you implement this synchronisation, but it
must be as efficient as possible. A correct implementation of task 2 must:

 Contain a producer thread that generates processes and places them in the buffer of ready processes whenever there is space
available; a consumer thread that removes processes from the ready list and runs them (i.e. calls simulateSJFProcess()). The
producer can only add processes to the buffer if spaces are available, the consumer can only remove processes from the buffer
if processes are available. The producer and consumer must run in separate threads and with maximum parallelism.

 Correctly use the simulateSJFProcess() function and correctly calculate (and display) the average response/turnaround times.
 Clearly separate the implementation of the linked lists (adding/removing elements) from the implementation of the process
scheduling algorithm (i.e. do not place everything in one single method).

 Declare, initialise, and utilise all semaphores/mutexes correctly. The type of synchronisation method
should be considered carefully to ensure maximum performance of your code.
 The synchronisation of your code must be correct, as efficient as possible, and no deadlocks should
occur.
 Join the producer and consumer with the main thread in a correct manner, ensuring that the main thread
cannot finish before the producer and consumer are both finished.
 Generate output similar to the sample file provided on Moodle for requirement 2, but for 1000 jobs.*/


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
  int i, Buffer = 0;
  int n = 0, sumRT, sumTAT;
  double num[10];
  float averageRTinsec, averageTATinsec;

  FILE *f = fopen("task1a.txt", "w");
  if (f == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  while (Buffer != BUFFER_SIZE) {
    myProcessPtr = generateProcess();
    head = insertByBurstTime(head, myProcessPtr, i);
    Buffer++;
  }

  for (i = 0; i < 1000; i++) {

    // Running Processes through CPU
    while (Buffer != 0) {
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

            //to calculate Averages
            n = n+1;
            sumRT += num[n] = ResponseTime;
            sumTAT += num[n] = TurnAroundTime;

            // and get rid of run processes
          if (currentProcessPtr->next != NULL) {
            currentProcessPtr = currentProcessPtr->next;
            deleteNode(&head, currentProcessPtr->previous);
            Buffer = Buffer - 1;
          } else{
            struct node *tmp = currentProcessPtr;
            currentProcessPtr = currentProcessPtr->next;
            deleteNode(&head, tmp);
            Buffer = Buffer - 1;
          }
        }
      }
    }
    fclose(f);
  }
}
/*
  3. Mutex
To solve this issue, we should create a new semaphory to solve the mutual exclusion problem
(no more than one producer has access to the buffer at one given time.) , thus the variable semaphory is named “mutex”.

When a process wants to enter critical region , it uses the mutex_lock() to lock the the variable mutex. If mutex is
locked it waits it’s turn. The mutex solution works well because it offers another processes to accesss the processor ,
simply because it avoids the busy waiting solution.

semaphore mutex = 1
semaphore full = 0
semaphore empty = BUFFER_SIZE

procedure producer() {
    while (true) {
        item = produceItem()
        down(empty)
        down(mutex)
        putItemIntoBuffer(item)
        up(mutex)
        up(full)
    }
 }

procedure consumer() {
    while (true) {
        down(full)
        down(mutex)
        item = removeItemFromBuffer()
        up(mutex)
        up(empty)
        consumeItem(item)
    }
}
*/
