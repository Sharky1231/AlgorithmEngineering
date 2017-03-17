//#include </usr/local/include/valgrind/callgrind.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <cstdio>
#include <cmath>

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

int addBucketToArray(vector<int>* source, vector<int> *target, int index) {
    int internalIndex = 0;
    while (internalIndex < source->size()) {
        int p = source->size();
        target->at(index) = source->at(internalIndex);
        index++;
        internalIndex++;
    }

    return index;
}

void MSD_radix_sort(vector<int> *myVector, int numberOfDigits) {

    if(myVector->size() > 1 && numberOfDigits != 0) {
        vector<int> bucket_0;
        vector<int> bucket_1;
        vector<int> bucket_2;
        vector<int> bucket_3;
        vector<int> bucket_4;
        vector<int> bucket_5;
        vector<int> bucket_6;
        vector<int> bucket_7;
        vector<int> bucket_8;
        vector<int> bucket_9;

        int divideBy = ceil(pow(10, numberOfDigits));
        int reminder = divideBy / 10;

        for (int j = 0; j < myVector->size(); j++) {
            int element = myVector->at(j);
            int mod = element % divideBy;
            int digit = mod / reminder;

            // push back vs insert?
            switch (digit) {
                case 0:
                    bucket_0.push_back(element);
                    break;
                case 1:
                    bucket_1.push_back(element);
                    break;
                case 2:
                    bucket_2.push_back(element);
                    break;
                case 3:
                    bucket_3.push_back(element);
                    break;
                case 4:
                    bucket_4.push_back(element);
                    break;
                case 5:
                    bucket_5.push_back(element);
                    break;
                case 6:
                    bucket_6.push_back(element);
                    break;
                case 7:
                    bucket_7.push_back(element);
                    break;
                case 8:
                    bucket_8.push_back(element);
                    break;
                case 9:
                    bucket_9.push_back(element);
                    break;
                default:
                    break;
            }
        }

        MSD_radix_sort(&bucket_0, numberOfDigits - 1);
        MSD_radix_sort(&bucket_1, numberOfDigits - 1);
        MSD_radix_sort(&bucket_2, numberOfDigits - 1);
        MSD_radix_sort(&bucket_3, numberOfDigits - 1);
        MSD_radix_sort(&bucket_4, numberOfDigits - 1);
        MSD_radix_sort(&bucket_5, numberOfDigits - 1);
        MSD_radix_sort(&bucket_6, numberOfDigits - 1);
        MSD_radix_sort(&bucket_7, numberOfDigits - 1);
        MSD_radix_sort(&bucket_8, numberOfDigits - 1);
        MSD_radix_sort(&bucket_9, numberOfDigits - 1);

        int startPosition = 0;
        startPosition = addBucketToArray(&bucket_0, myVector, startPosition);
        startPosition = addBucketToArray(&bucket_1, myVector, startPosition);
        startPosition = addBucketToArray(&bucket_2, myVector, startPosition);
        startPosition = addBucketToArray(&bucket_3, myVector, startPosition);
        startPosition = addBucketToArray(&bucket_4, myVector, startPosition);
        startPosition = addBucketToArray(&bucket_5, myVector, startPosition);
        startPosition = addBucketToArray(&bucket_6, myVector, startPosition);
        startPosition = addBucketToArray(&bucket_7, myVector, startPosition);
        startPosition = addBucketToArray(&bucket_8, myVector, startPosition);
        startPosition = addBucketToArray(&bucket_9, myVector, startPosition);


    }
}


void radixSort(vector<int> unsortedNumbers, int vectorSize) {
    for (int i = 0; i < vectorSize; i++)
        unsortedNumbers.at(i) = rand() % vectorSize;

    int biggestNumber = unsortedNumbers.at(0);


    // Find biggest number
    for (int i = 0; i < vectorSize; i++) {
        if (unsortedNumbers.at(i) > biggestNumber)
            biggestNumber = unsortedNumbers.at(i);
    }

//    printElementsInArray(unsortedNumbers, vectorSize);

    // Get number of digits in the biggest number
    int numberOfDigits = getNumberOfDigits(biggestNumber);

    clock_t begin = clock();
    MSD_radix_sort(&unsortedNumbers, numberOfDigits);

    // All numbers consists of 0-9 digits, so create those buckets
    // ?? Or should we create an arrays of size unsortedNumbers ?
    // ?? Use queue insted of vector objects?



//    printElementsInArray(unsortedNumbers, arraySize);
    //CALLGRIND_STOP_INSTRUMENTATION ;
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    char msg[100];
    sprintf(msg, "%d %f", vectorSize, elapsed_secs);
    //CALLGRIND_DUMP_STATS_AT(msg) ;

    cout << "\n----Results----- " << endl;
    cout << "Radix sort took: " << elapsed_secs << " seconds" << endl;
    cout << "Biggest number: " << biggestNumber << endl;
    cout << "Number of digits: " << +numberOfDigits << endl;
}

int vectorSize = 125;
vector<int> unsortedNumbers(vectorSize);


int main() {



    // Populate array with random numbers between 0 and arraySize

    for (int i = 0; i < 1; i++) {
        radixSort(unsortedNumbers, vectorSize);
        vectorSize = vectorSize + 1000;
        unsortedNumbers.resize(vectorSize);
    }


    return 0;
};
