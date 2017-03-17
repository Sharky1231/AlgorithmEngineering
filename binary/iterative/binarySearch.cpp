//
// Created by Sharky on 27/02/2017.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <cstdio>
#include <algorithm>
#include </usr/local/include/valgrind/callgrind.h>

using namespace std;


static int maxSize = 2000000;
static int maxNumber = maxSize*100;

int findMiddle(int min, int max){
    if((min + max) % 2 == 0){
        return (min + max) / 2;
    }
    else{
        return (min + max + 1) / 2;
    }

}


int binarySearch_iterative(int* array, int min, int max, int target) {


    cout << "elements: " << max << "\n";
    cout << "target: " << target << "\n";
    clock_t begin = clock();
    CALLGRIND_ZERO_STATS;
    CALLGRIND_START_INSTRUMENTATION;


   

    while (min != max) {

        int middleIndex = findMiddle(min, max);

        if(target == array[middleIndex]){
            return array[middleIndex];
        } else if(target > array[middleIndex]) {
            min = middleIndex;
        } else if(target < array[middleIndex]) {
            max = middleIndex - 1;
        }
    }

    CALLGRIND_STOP_INSTRUMENTATION;
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    char msg[100];
    sprintf(msg,"%d %f", max, elapsed_secs);
    CALLGRIND_DUMP_STATS_AT(msg);
    
    cout << "pred: " << array[min] << "\n";

    return array[min];

}


int binarySearch_recursive(int* array, int min, int max, int target){

    int middleIndex = findMiddle(min, max);

    if(min == max){
        return array[min];
        
    }

    if(target == array[middleIndex]){
        return array[middleIndex];
    }

    else if(target > array[middleIndex]) {
        binarySearch_recursive(array, middleIndex, max, target);
    }
    else if(target < array[middleIndex]){
        binarySearch_recursive(array, min, middleIndex-1, target);
    }
}


int binarySearch_recursive_callgrind(int* array, int min, int max, int target) {
    
    clock_t begin = clock();
    CALLGRIND_ZERO_STATS;
    CALLGRIND_START_INSTRUMENTATION;
    
    int result = binarySearch_recursive(array, min, max, target);

    CALLGRIND_STOP_INSTRUMENTATION;
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    char msg[100];
    sprintf(msg,"%d %f", max, elapsed_secs);
    CALLGRIND_DUMP_STATS_AT(msg);
    cout << "elements: " << max << "\n";
    cout << "pred: " << result << "\n";
    return result;
}



int main() {

    srand(time(0));

    for (int j = 2; j < maxSize; j+=100000) {
        int numbers[j];

        for (int i = 0; i < j; i++) {
            numbers[i] = rand() % maxNumber;
        }

        sort(numbers, numbers + j);
        //int pred = binarySearch_recursive_callgrind(numbers, 0, j, rand() % maxNumber);
        int pred = binarySearch_iterative(numbers, 0, j, rand() % maxNumber);
    } 


   /* int numbers[10];
    for (int i = 0; i < 10; i++) {
        numbers[i] = rand() % 100;
    }

    int pred = binarySearch_iterative(numbers, 0, 10, rand() % 100);*/
    

    
    return 0;
};

