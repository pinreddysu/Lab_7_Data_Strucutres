#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DEBUG 1
#define debug 1
#define DEBUG2 1
#define SIZE 21



typedef struct data_node{
    int num;
    int file_num;
}num_t;

typedef struct node{
    num_t heap[21];
    int size;
}heap_t;

void insert_heap (heap_t *h, num_t data);
void file_name(int start, int end);
void print_binary (heap_t h);
num_t delete(heap_t *heap1, int i);
void merged_file_write(num_t data);


/*
AUTHOR Suchit Pinreddy and Sai Arjun Shroff
FILENAME:  Assignment7.c
SPECIFICATION: implementing a binary heap to sort input in ascending order from n number of files
FOR: CS 2413 Data Structures 002

*/

int main()
{
    printf("Hello World");
    file_name(1,2);
    return 0;
}

/*
 NAME: file_name
 PARAMETERS: starting and ending number of the files that need to be counted 
 PURPOSE:  to read the content of the files whose starting and ending number is mentioned in the user defined paramter
 PRECONDITION:  integer values of the file count need be declared
 POSTCONDITION:  the data will be merged into merge.txt after calling insertion and deletion function

 */
void file_name(int start, int end){
    int flag[21] = {0};
    FILE *inp[21];
    num_t hold;
    num_t hold1;
    heap_t h1;
    for(int i = start; i<= end; i++){
        char name1[50];
        sprintf(name1, "%d.txt", i);
        inp[i] = fopen(name1, "r");
        //printf("It worked");
        if(inp[i]){
            flag[i] = 1;
        }
        /*else{
          flag[i] = 2;
            //printf("File missing");
            //continue;
        }*/
    }
    for (int j = start; j<=end; j++){
        if(flag[j] && fscanf(inp[j], "%d", &hold.num)==1){
            hold.file_num = j;
            insert_heap(&h1, hold);
            print_binary(h1);
        }
        else{
            flag[j] = 0;
        }
    }
    print_binary(h1);
    while(h1.size>0){
        hold1 = delete(&h1,1);
        merged_file_write(hold1);
        printf("Hold node, data = %d, file_num = %d\n",hold1.num, hold1.file_num);
        if(flag[hold1.file_num] && fscanf(inp[hold1.file_num], "%d", &hold1.num)>0){
            insert_heap(&h1, hold1);
            print_binary(h1);
        }
    }
}

/*
 NAME: insert_heap
 PARAMETERS: heap_t struct type pointer and the num_t data type
 PURPOSE:  to insert num_t data type into the binary heap
 PRECONDITION:  the binary heap root needs to be initialised
 POSTCONDITION:  inserts num_t data type in binary heap in ascending order from the root

 */

void insert_heap (heap_t *h, num_t data) {
  int pos,par;
  if (DEBUG) {
    printf ("\ninsert_heap - begin, data = %d file data = %d heap size is %d\n",
      data.num,data.file_num,h->size);
  }
  if (h->size < SIZE-1) {
    h->heap[h->size+1].num = data.num;
    h->heap[h->size+1].file_num = data.file_num;
    h->size += 1;
    pos = h->size;
    par = pos/2;
    int temp;
    int temp1;
    while (pos > 1 && h->heap[pos].num < h->heap[par].num) {
      if (DEBUG) {
        printf("insert_heap - pos = %d par = %d\n",pos,par);
      }
      if (DEBUG2) {
        print_binary(*h);
        putchar('\n');
      }
      temp = h->heap[pos].num;
      temp1 = h->heap[pos].file_num;
      h->heap[pos].num = h->heap[par].num;
      h->heap[pos].file_num = h->heap[par].file_num;
      h->heap[par].num = temp;
      h->heap[par].file_num = temp1;
      pos = par;
      par = pos/2;
    }
  }
  if (DEBUG) {
    printf("insert_heap - pos = %d par = %d\n",pos,par);
    printf ("insert_heap -   end, data = %d heap size is %d\n",
      data.num,h->size);
  }
}


/*
 NAME: print_binary
 PARAMETERS: struct type heap_t parameter
 PURPOSE:  to print the binary heap array 
 PRECONDITION:  the binary heap root needs to be initialised with a value
 POSTCONDITION:  prints out the heap from the root(index value =1) to the size of heap

 */

void print_binary (heap_t h) {
  printf("\nBinary Heap:\n  size %d\n  ",h.size);
  if (h.size > 0) {
    int i;
    for (i=1; i <= h.size; i++)
      printf("%d file numb %d \n",h.heap[i].num, h.heap[i].file_num);
    putchar('\n');
  }
  else
    printf("Empty\n");
}


/*
 NAME: delete
 PARAMETERS: struct type heap_t pointer and  parent node i
 PURPOSE:  to delete the root value(priority value) from the heap and replacing it with the last index value
 PRECONDITION:  the binary heap root needs to be initialised with a value
 POSTCONDITION:  deletes the root value and replaces it with the second most significant value

 */



num_t delete(heap_t *heap1, int i){
    num_t temp;
    num_t temp1;
    temp = heap1->heap[1];
    heap1->heap[1] = heap1->heap[heap1->size];
    //heap1->heap[heap1->size+1] = 0;
    heap1->size -=1;
    int now = i;
    int left = i*2;
    int right = left + 1;
    while(left <= heap1->size){
        if (left < heap1->size){
            if (heap1->heap[now].num <= heap1->heap[left].num && heap1->heap[now].num <= heap1->heap[right].num){
                return temp;
            }
            else if(heap1->heap[right].num<=heap1->heap[left].num){
                temp1 = heap1->heap[now];
                heap1->heap[now] = heap1->heap[right];
                heap1->heap[right] = temp1;
                now =  right;
            }
            else if(left < heap1->size){
                temp1 = heap1->heap[now];
                heap1->heap[now] = heap1->heap[left];
                heap1->heap[left] = temp1;
                now =  left;
            }
        }
        else if(heap1->heap[now].num>=heap1->heap[left].num){
            temp1 = heap1->heap[now];
            heap1->heap[now] = heap1->heap[left];
            heap1->heap[left] = temp1;
            now =  left;
        }
        
        //int now = i;
        int left = 2*now;
        int right = left + 1;
    }
    return temp;
}


/*
 NAME: merged_file_write
 PARAMETERS: struct type num_t data
 PURPOSE:  to print out the output into the merged file output
 PRECONDITION:  data node
 POSTCONDITION:  output in the merged text file in ascending order.


 */
 
 
 

void merged_file_write(num_t data){
    FILE *outfile;
    //int nodes;
    outfile = fopen("merged.txt", "a");
    //nodes = total_nodes(root);
    fprintf(outfile, "%d\t", data.num);
    //inorder(root,outfile);
    fclose(outfile);
}



/*
Report

Sai Arjun Shroff

void insert_heap (heap_t *h, num_t data)- designed and  implemented
void file_name(int start, int end)- designed and modified
void print_binary (heap_t h)-designed and modified
void merged_file_write(num_t data)-designed and  modified
 
Overall styling of the code in a structured manner following the template
Worked on determining the Binary  heap analysis.


Test cases-
1. example 1.txt, 2.txt, merged.txt built 
2.one of the m.txt files of sorted integers is empty, merged.txt built
3. 



Suchit Pinreddy


void file_name(int start, int end); designed and modified
void print_binary (heap_t h);-designed and modified
num_t delete(heap_t *heap1, int i); designed and implemented
void merged_file_write(num_t data);-designed and modified

Worked on determining the Binary  heap analysis..

Test cases-

1. 3<=n<=12 files of sorted integers, merged.txt built Failed
2.one of the m.txt files of sorted integers is missing, merged.txt built
 

*/


/*

2)
ii)
1)example 1.txt, 2.txt, merged.txt built – passed
output
1	3	19	21	25	25	101	
2)3<=n<=12 files of sorted integers, merged.txt built – passed/failed - failed

3)one of the m.txt files of sorted integers is empty, merged.txt built -passed
output
1	19	25	
4)one of the m.txt files of sorted integers is missing, merged.txt built-passed
output
1	19	25	

iii)
1. Big O of inserting all m integers in files 1.txt to n.txt into a binary min heap of size n -O(nlog(n))
2. Big O of the storage requirements for a binary min heap of size n -O(n)
3. How could this program be extended to perform an external file merge sort on one file of m unordered integers? 
-> If the first number in file taken and can check if it is in assending order if it is it can swap file num merging the file




*/