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
    struct timeval * StartTime = (struct timeval*) malloc(sizeof(struct timeval));
    struct timeval * EndTime = (struct timeval*) malloc(sizeof(struct timeval));
    struct process * myProcessPtr;

 //Creating 10 Processes by calling generateProcess
    for( a = 0; a < 10; a = a + 1 ) {
        myProcessPtr = generateProcess();
        insertByBurstTime(a, &head, myProcessPtr, &tail);
    }
    printList(head);


    struct node *currentProcessPtr = NULL;
    currentProcessPtr = head;

    while (currentProcessPtr != NULL) { //stop if list is empty

        //while (myProcessPtr->iState == 1) {  //skip node if already run and istate changed
            printf("getting ready to run SJF\n");
            simulateSJFProcess(myProcessPtr, StartTime, EndTime);
            if (myProcessPtr->iState == FINISHED) {
                deleteNode(&head, currentProcessPtr);
                currentProcessPtr->next = currentProcessPtr;
            }
        //}

    //printList(head);

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
