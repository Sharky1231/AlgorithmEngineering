//#include </usr/local/include/valgrind/callgrind.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <cstdio>
#include <cmath>
#include <omp.h>

using namespace std;

// Limit 518869 ?
//


//int unsortedNumbers[arraySize];

// create buckets from 0 - 9
// find number of digits in biggest number - done
// if there are N digits, then we perform N repetitions


int getNumberOfDigits(int number) {
    int digits = 1;

    while (number /= 10)
        digits++;

    return digits;
}

void printElementsInArray(int array[], int sizeOfArray) {
    for (int i = 0; i < sizeOfArray; i++) {
        cout << array[i] << ", " << flush;
    }

    cout << "" << endl;
}

int addBucketToArray(vector<int>* tempVector, queue<int> &bucket, int index) {
    while (!bucket.empty()) {
        tempVector->at(index) = bucket.front();
        bucket.pop();
        index++;
    }

    return index;
}

void LSD_radix_sort(vector<int>* numbersVector){
    // RADIX SORT REPEAT AS MANY TIMES AS THERE ARE MSD BUCKETS

    int biggestNumber = numbersVector->at(0);

    // Find biggest number
    for (int i = 0; i < numbersVector->size(); i++) {
        if (numbersVector->at(i) > biggestNumber)
            biggestNumber = numbersVector->at(i);
    }

    // Get number of digits in the biggest number
    int numberOfDigits = getNumberOfDigits(biggestNumber);

    // All numbers consists of 0-9 digits, so create those buckets
    // ?? Or should we create an arrays of size unsortedNumbers ?
    // ?? Use queue insted of vector objects?
    queue<int> bucket_0;
    queue<int> bucket_1;
    queue<int> bucket_2;
    queue<int> bucket_3;
    queue<int> bucket_4;
    queue<int> bucket_5;
    queue<int> bucket_6;
    queue<int> bucket_7;
    queue<int> bucket_8;
    queue<int> bucket_9;

    int m = 10;
    int n = 1;

    int numbersVectorSize = numbersVector->size();
    vector<int> tempVector(numbersVectorSize);
    bool firstRound = true;

    for (int i = 0; i < numberOfDigits; i++) {

        for (int j = 0; j < numbersVectorSize; j++) {
            int element;
            if(firstRound) {
                element = numbersVector->at(j);
            } else
                element = tempVector.at(j);
            int mod = element % m;
            int reminder = mod / n;

            // push back vs insert?
            switch (reminder) {
                case 0:
                    bucket_0.push(element);
                    break;
                case 1:
                    bucket_1.push(element);
                    break;
                case 2:
                    bucket_2.push(element);
                    break;
                case 3:
                    bucket_3.push(element);
                    break;
                case 4:
                    bucket_4.push(element);
                    break;
                case 5:
                    bucket_5.push(element);
                    break;
                case 6:
                    bucket_6.push(element);
                    break;
                case 7:
                    bucket_7.push(element);
                    break;
                case 8:
                    bucket_8.push(element);
                    break;
                case 9:
                    bucket_9.push(element);
                    break;
                default:
                    break;
            }
        }

        firstRound = false;
        m = m * 10;
        n = n * 10;


        // clear array and add, or overwrite old entries
        int elementsInserted = 0;
        elementsInserted = addBucketToArray(&tempVector, bucket_0, elementsInserted);
        elementsInserted = addBucketToArray(&tempVector, bucket_1, elementsInserted);
        elementsInserted = addBucketToArray(&tempVector, bucket_2, elementsInserted);
        elementsInserted = addBucketToArray(&tempVector, bucket_3, elementsInserted);
        elementsInserted = addBucketToArray(&tempVector, bucket_4, elementsInserted);
        elementsInserted = addBucketToArray(&tempVector, bucket_5, elementsInserted);
        elementsInserted = addBucketToArray(&tempVector, bucket_6, elementsInserted);
        elementsInserted = addBucketToArray(&tempVector, bucket_7, elementsInserted);
        elementsInserted = addBucketToArray(&tempVector, bucket_8, elementsInserted);
        elementsInserted = addBucketToArray(&tempVector, bucket_9, elementsInserted);
    }

    for(int i = 0; i < numbersVector->size(); i++){
        numbersVector->at(i) = tempVector.at(i);
    }

}

void radixSort(vector<int> unsortedNumbers, int vectorSize){
    for (int i = 0; i < vectorSize; i++)
        unsortedNumbers.at(i) = rand() % vectorSize;

    int biggestNumber = unsortedNumbers.at(0);

    ////// RADIX SORT STARTS HERE ///////
    clock_t begin = clock();
//    CALLGRIND_ZERO_STATS ;
//    CALLGRIND_START_INSTRUMENTATION ;

    // Find biggest number
    for (int i = 0; i < vectorSize; i++) {
        if (unsortedNumbers.at(i) > biggestNumber)
            biggestNumber = unsortedNumbers.at(i);
    }

    // Get number of digits in the biggest number
    int numberOfDigits = getNumberOfDigits(biggestNumber);

    vector< vector<int> > digitGroups(10, vector<int>());
    int divideBy = ceil(pow(10, numberOfDigits));
    int andA = divideBy / 10;

    for (int i = 0; i < vectorSize; i++) {
        int element = unsortedNumbers.at(i);
        int mod = element % divideBy;
        int reminder = mod / andA;

        // push back vs insert?
        switch (reminder) {
            case 0:
                digitGroups[0].push_back(element);
                break;
            case 1:
                digitGroups[1].push_back(element);
                break;
            case 2:
                digitGroups[2].push_back(element);
                break;
            case 3:
                digitGroups[3].push_back(element);
                break;
            case 4:
                digitGroups[4].push_back(element);
                break;
            case 5:
                digitGroups[5].push_back(element);
                break;
            case 6:
                digitGroups[6].push_back(element);
                break;
            case 7:
                digitGroups[7].push_back(element);
                break;
            case 8:
                digitGroups[8].push_back(element);
                break;
            case 9:
                digitGroups[9].push_back(element);
                break;
            default:
                break;
        }

    }

//    omp_set_num_threads(4);
//#pragma omp parallel
    for(int i = 0; i < digitGroups.size(); i++){
        if(digitGroups[i].size() > 0)
            LSD_radix_sort(&digitGroups[i]);
    }

//    printElementsInArray(unsortedNumbers, arraySize);
//    CALLGRIND_STOP_INSTRUMENTATION ;
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    char msg[100];
    sprintf(msg,"%d %f",vectorSize,elapsed_secs);
//    CALLGRIND_DUMP_STATS_AT(msg) ;

    cout << "\n----Results----- " << endl;
    cout << "Radix sort took: " << elapsed_secs << " seconds" << endl;
    cout << "Biggest number: " << biggestNumber << endl;
    cout << "Number of digits: " << +numberOfDigits << endl;
}

int vectorSize = 1000;
vector<int> unsortedNumbers(vectorSize);


int main() {


//    cout << (int)14%100/10 <<  endl;
    // Populate array with random numbers between 0 and arraySize

    for (int i = 0; i < 2; i++) {
        radixSort(unsortedNumbers, vectorSize);
        vectorSize = vectorSize + 1000;
        unsortedNumbers.resize(vectorSize);
    }



    return 0;
};
