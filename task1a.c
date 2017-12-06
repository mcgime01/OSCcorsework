/**************************************************************
 * Program implementing SJF algorithm
 * Coarse work: Task 1 for Operating Systems and Concerency
 * Fall 2017
 * by Meghan McGinnis
 **************************************************************/
//implement SJF algorithm

//calculate average response and turnaround time

//write process info to file as it is executed.
//use of Dynamic Memory


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
    struct timeval * StartTime;
    struct timeval * EndTime;
    struct process * myProcessPtr;

 //Creating 10 Processes by calling generateProcess
    for( a = 0; a < 10; a = a + 1 ) {
        myProcessPtr = generateProcess();
        insertByBurstTime(a, &head, myProcessPtr, &tail);
    }
    printList(head);
   
    while (head != NULL) {
        printf(" head is still going strong");
        while (myProcessPtr->iState == 1) {
            printf("getting ready to run SJF");
            simulateSJFProcess(myProcessPtr, StartTime, EndTime);
            printf("finished SJF");
        }
    }

            //and write output to file



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
