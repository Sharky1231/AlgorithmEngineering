#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <cstdio>
#include <algorithm>
#include </usr/local/include/valgrind/callgrind.h>

using namespace std;


static int maxSize = 1000000;
static int maxNumber = maxSize*100;

int findMiddle(int min, int max){
    if((min + max) % 2 == 0){
        return (min + max) / 2;
    }
    else{
        return (min + max + 1) / 2;
    }

}


int binarySearch_iterative(vector<int>* myVector, int min, int max, int target) {


    cout << "elements: " << max << "\n";
    cout << "target: " << target << "\n";
    clock_t begin = clock();
    CALLGRIND_ZERO_STATS;
    CALLGRIND_START_INSTRUMENTATION;

    while (min != max) {

        int middleIndex = findMiddle(min, max);

        if (target == myVector->at(middleIndex)) {
            return myVector->at(middleIndex);
        } else if (target > myVector->at(middleIndex)) {
            min = middleIndex;
        } else if (target < myVector->at(middleIndex)) {
            max = middleIndex - 1;
        }
    }

    CALLGRIND_STOP_INSTRUMENTATION;
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    char msg[100];
    sprintf(msg, "2 %d %f", max, elapsed_secs);
    CALLGRIND_DUMP_STATS_AT(msg);

    cout << "pred: " << myVector->at(min) << "\n";

    return myVector->at(min);
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

        int pred = binarySearch_iterative(&numbers, 0, j, rand() % maxNumber);
    }
    
    return 0;
};

