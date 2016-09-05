#ifndef MYQUICKSORT_H
#define MYQUICKSORT_H

#include <iostream>
#include <stdio.h>
#include <string.h>
using std::cout;
using std::endl;

namespace sorty{
 void printArray(int *start, int length){
  for(int i=0; i<length;i++){
    cout<<start[i]<< " ";
  }
  cout<<endl;
}

//swap values at two pointer locations;
void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int partition(int arrayToSort[], int start, int end)
{
  int pivot = arrayToSort[end];
  int smallPosition = start;
  for(int k = start; k<end; k++){
    if(arrayToSort[k] <= pivot){
      swap(&arrayToSort[k], &arrayToSort[smallPosition]);
      smallPosition++;
    }
  }
  swap(&arrayToSort[smallPosition], &arrayToSort[end]);
  return smallPosition;

}

 void quickSortHelper(int *arrayToSort, int start, int end)
 {
    if(start <  end){
      int pivot = partition(arrayToSort, start, end);
      quickSortHelper(arrayToSort, start, pivot-1);
      quickSortHelper(arrayToSort, pivot+1, end);
    }
 }


 void myQuickSort(int *arrayToSort, int length)
 {
   quickSortHelper(arrayToSort, 0, length-1);
 }
}

#endif
