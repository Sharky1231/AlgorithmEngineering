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


static int arraySize = 20000;

int findMiddle(int min, int max){
    if((min + max) % 2 == 0){
        return (min + max) / 2;
    }
    else{
        return (min + max + 1) / 2;
    }

}




int binarySearch(int* array, int min, int max, int target){

   

    int middleIndex = findMiddle(min, max);

    if(min == max){
        if(target == array[min]){
            return min;
        }

        return -1;
    }

    if(target == array[middleIndex]){
        return middleIndex;
    }

    else if(target > array[middleIndex])
        binarySearch(array, middleIndex+1, max, target);

    else if(target < array[middleIndex]){
        binarySearch(array, min, middleIndex-1, target);
    }
}


int binarySearch_callgrind(int* array, int min, int max, int target) {
    
    clock_t begin = clock();
    CALLGRIND_ZERO_STATS;
    CALLGRIND_START_INSTRUMENTATION;
    
    CALLGRIND_STOP_INSTRUMENTATION;
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    char msg[100];
    sprintf(msg,"%d %f", numberOfElements, elapsed_secs);
    CALLGRIND_DUMP_STATS_AT(msg);
}



int main() {

    int numbers[arraySize];

    for (int i = 0; i < arraySize; i++)
        numbers[i] = rand();

    numbers = sort(numbers, numbers + arraySize);
    int position = binarySearch(sortedNumbers, 0, arraySize, 1332);

    cout << "Position: " << position << endl;
    return 0;
};

