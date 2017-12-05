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

	//start linked list
    struct node *head = NULL;
    struct node *current = NULL;
    struct node *tail = NULL;


 //Creating 10 Processes by calling generateProcess
    struct process * myProcessPtr;

    for( a = 0; a < 9; a = a + 1 ) {

        myProcessPtr = generateProcess();
        //insertFirst(a,myProcessPtr);
        insertByBurstTime(a, &head, myProcessPtr, tail);
        printList(head);
    }


   
    //for (every item in list) or while (list is not empty)
        //while (myProcessPtr->iState == NEW)
            //void simulateSJFProcess(struct process * oTemp, struct timeval * oStartTime, struct timeval * oEndTime);
            //and write output to file



    //write to file
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

    fclose(f);
}
