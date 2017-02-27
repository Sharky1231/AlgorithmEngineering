//
// Created by Sharky on 27/02/2017.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <cstdio>

using namespace std;


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



int main() {
    int arraySize = 2000;
    int sortedNumbers[arraySize];

    for (int i = 0; i < arraySize; i++)
        sortedNumbers[i] = i;

    int position = binarySearch(sortedNumbers, 0, arraySize, 1332);

    cout << "Position: " << position << endl;
    return 0;
};

