

//implement the RR algorithm
// A fixed time is allotted to every process that arrives in the queue. This fixed time is known as time slice or time quantum.

	// The first process that arrives is selected and sent to the processor for execution.
// If it is not able to complete its execution within the time quantum provided, then an interrupt is generated using an automated timer.

	//The process is then stopped and is sent back at the end of the queue.
// However, the state is saved and context is thereby stored in memory.
// This helps the process to resume from the point where it was interrupted.

	//The scheduler selects another process from the ready queue and dispatches it to the processor for its execution.
// It is executed until the time Quantum does not exceed.

//The same steps are repeated until all the process are finished.

//calculate average response time and and turnaround time
//print to output to file

#include<stdio.h>
#include<stdlib.h>
#include"linkedlist.h"
#include"coursework.h"


int main() {
    // defining Variables
    int i, a;

    struct node *head = NULL;
    struct node *current = NULL;
    struct node *tail = NULL;
    struct timeval *StartTime;
    struct timeval *EndTime;
    struct process *myProcessPtr;

    //Creating 10 Processes by calling generateProcess and entering them in to the back of the linked list.
    for (a = 0; a < 10; a = a + 1) {
        myProcessPtr = generateProcess();
        printProcess(myProcessPtr);
        insertLast(a, &head, myProcessPtr);
    }
    printList(head);


   while (head != NULL) {
       printf("about to run round robin");
       simulateRoundRobinProcess(myProcessPtr, StartTime, EndTime);  	// The first process that arrives is selected and sent to the processor for execution.
       printf(" ran Round Robin");

       if (head->data->iBurstTime == 0) {
           current = tail;         //The process is then stopped and is sent back at the end of the queue.
           current->next = head;
           current->next = current;  //can I do this?
       } else {
           deleteNode(head, current);
       }
   }

    //The scheduler selects another process from the ready queue and dispatches it to the processor for its execution.
    

}
