#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define HEAD 33     //initial head position
#define LAST_CYLINDER 99
FILE *input_file;
FILE *output_file; 
int arr[25];        //array to store the sequence 


void FCFS(int array[], int head); 
void SCAN(int array[], int head); 
void C_SCAN(int array[], int head); 

void FCFS(int array[], int head) {
    int i;
    int seek = 0;
    int current = 0;
    int distance = 0;

    for (i = 0; i < 25; i++) {
        current = array[i]; 
        distance = abs(current - head); 
        seek = seek + distance; 
        head = current; //update the head
    }

    fprintf(output_file, "\n"); 
    fprintf(output_file, "FCFS Algorithm\n"); 
    fprintf(output_file, "Initial head position = %d\n", HEAD); 
    fprintf(output_file, "Seek Sequence is:\n"); 

    //printing sequence for FCFS is the same as printing from input.txt 
    for (i = 0; i < 25; i++) {
        fprintf(output_file, "%d\n", array[i]); 
    }

    fprintf(output_file, "Total head movement for FCFS = %d\n", seek);
    fprintf(output_file, "\n"); 
}

/////////////////////////////////////////////////////////////////////////

void SCAN(int array[], int head) {
    int i, j, temp, index; 
    int seek = 0;
    int current = 0;
    int distance = 0;
    
    //sorting array in ascending order 
    for (i = 0; i < 25; i++) {  
        for (j = 0; j < 25; j++) {
            if (array[j] > array[i]) {
                temp = array[i]; 
                array[i] = array[j]; 
                array[j] = temp; 
            }
        }
    }

    //get max value in array that is smaller than HEAD
    for (i = 0; i < 25; i++) {
       if (array[i] > (HEAD + 1)) {   //break as soon as value is greater than HEAD 
           break;
       }
       index = i;               //this is the index where algorthim will go first from the initial head position 
    }
    
    //since head is always 33, it will always go left first 
    for (i = index; i >= 0; --i) {
        current = array[i]; 
        distance = abs(current - head); 
        seek = seek + distance; 
        head = current; //update the head
    }

    seek = seek + head; //add last element before transition
    head = 0;           //set head to 0 so first caluculation after transition just adds that element
    
    for (i = index + 1; i < 25; i++) {
        current = array[i]; 
        distance = abs(current - head); 
        seek = seek + distance; 
        head = current; //update the head
    }

    fprintf(output_file, "SCAN Algorithm\n"); 
    fprintf(output_file, "Initial head position = %d\n", HEAD); 
    fprintf(output_file, "Seek Sequence is:\n"); 
   
    //printing from right to left
    for (i = index; i >= 0; --i) {
        fprintf(output_file, "%d\n", array[i]); 
    }
    //printing from left to right 
    for (i = index + 1; i < 25; i++) {
        fprintf(output_file, "%d\n", array[i]); 
    }

    fprintf(output_file, "Total head movement for SCAN = %d\n", seek);
    fprintf(output_file, "\n"); 
   
}

/////////////////////////////////////////////////////////////////////////

void C_SCAN(int array[], int head) {
    int i, j, temp, index; 
    int seek = 0;
    int current = 0;
    int distance = 0; 

    //sorting array in ascending order 
    for (i = 0; i < 25; i++) {  
        for (j = 0; j < 25; j++) {
            if (array[j] > array[i]) {
                temp = array[i]; 
                array[i] = array[j]; 
                array[j] = temp; 
            }
        }
    }

    //get min value in array that is smaller than HEAD
    for (i = 24; i >= 0; --i) {
       if (array[i] < (HEAD + 1)) {       //break as soon as value is greater than HEAD 
           break;
       }
       index = i;                   //this is the index where algorthim will go first from the initial head position 
    }

    //since head is 33, it will always go right first 
    for (i = index; i < 25; i++) {
        current = array[i]; 
        distance = abs(current - head); 
        seek = seek + distance; 
        head = current; //update the head
    }
    
    seek = seek + (LAST_CYLINDER - head);   //must account for 99 - element_before_transition
    seek = seek + LAST_CYLINDER;            //add 99 
    head = 0;                               //set head to 0 so first caluculation after transition just adds that element
    
    for (i = 0; i < index; i++) {
        current = array[i]; 
        distance = abs(current - head); 
        seek = seek + distance; 
        head = current; //update the head
    }

    fprintf(output_file, "C_SCAN Algorithm\n"); 
    fprintf(output_file, "Initial head position = %d\n", HEAD); 
    fprintf(output_file, "Seek Sequence is:\n"); 

   //printing from right to left
    for (i = index; i < 25; i++) {
        fprintf(output_file, "%d\n", array[i]); 
    }
    //printing from left to right 
    for (i = 0; i < index; i++) {
        fprintf(output_file, "%d\n", array[i]); 
    }

    fprintf(output_file, "Total head movement for C_SCAN = %d", seek);
}

/////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    int i;
    input_file = fopen("input.txt", "r"); 
    output_file = fopen("output.txt", "w+"); 

    if (input_file == NULL) {
        fprintf(stdout, "File is empty or cannot be opened.\n"); 
    }
    else {
        for (i = 0; i < 25; i++) {
            fscanf(input_file, "%d", &arr[i]);  //read data from input.txt and store in array
        }
    }

    // for (i = 0; i < 25; i++) {
    //     printf("%d\n", arr[i]); 
    // }

    FCFS(arr, HEAD); 
    SCAN(arr, HEAD); 
    C_SCAN(arr, HEAD);
    fclose(input_file); 
    fclose(output_file); 
}
