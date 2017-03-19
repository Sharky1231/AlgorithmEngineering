#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <cstdio>
#include <algorithm>
#include </usr/local/include/valgrind/callgrind.h>

using namespace std;


static int maxSize = 1800000;
static int maxNumber = maxSize*100;

int findMiddle(int min, int max){
    if((min + max) % 2 == 0){
        return (min + max) / 2;
    }
    else{
        return (min + max + 1) / 2;
    }

}

int binarySearch_recursive(vector<int>* myVector, int min, int max, int target){

    int middleIndex = findMiddle(min, max);

    if(min == max){
        return myVector->at(min);
        
    }

    if(target == myVector->at(middleIndex)){
        return myVector->at(middleIndex);
    }

    else if(target > myVector->at(middleIndex)) {
        binarySearch_recursive(myVector, middleIndex, max, target);
    }
    else if(target < myVector->at(middleIndex)){
        binarySearch_recursive(myVector, min, middleIndex-1, target);
    }
}


int binarySearch_recursive_callgrind(vector<int>* numbers, int min, int max, int target) {
    
    clock_t begin = clock();
    CALLGRIND_ZERO_STATS;
    CALLGRIND_START_INSTRUMENTATION;
    
    int result = binarySearch_recursive(numbers, min, max, target);

    CALLGRIND_STOP_INSTRUMENTATION;
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    char msg[100];
    sprintf(msg,"1 %d %f", max, elapsed_secs);
    CALLGRIND_DUMP_STATS_AT(msg);
    cout << "elements: " << max << "\n";
    cout << "pred: " << result << "\n";
    return result;
}

vector<int> numbers(0);

int main() {

    srand(time(0));

    for (int j = 2; j < maxSize; j+=100000) {
        numbers.resize(j);

        for (int i = 0; i < j; i++) {
            numbers.at(i) = rand() % maxNumber;
        }

        sort(numbers.begin(), numbers.begin() + j);
        int pred = binarySearch_recursive_callgrind(&numbers, 0, j, rand() % maxNumber);
    }
    
    return 0;
};

