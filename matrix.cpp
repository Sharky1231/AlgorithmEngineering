#include <stdio.h>
#include <iostream>
using namespace std;

void printMatrix(int matrix[][10], int sizeRow){

    for (int i = 0; i < sizeRow; ++i) {
        for (int j = 0; j < 10; ++j){
            cout << matrix[i][j];
            cout << " ";
        }
    }
}

//Basic matrix multiplication, taken from: https://www.programiz.com/cpp-programming/examples/matrix-multiplication-function
void multiplyMatrices(int firstMatrix[][10], int secondMatrix[][10], int mult[][10], int rowFirst, int columnFirst, int rowSecond, int columnSecond)
{
	int i, j, k;

	// Initializing elements of matrix mult to 0.
	for(i = 0; i < rowFirst; ++i)
	{
		for(j = 0; j < columnSecond; ++j)
		{
			mult[i][j] = 2;
		}
	}

	// Multiplying matrix firstMatrix and secondMatrix and storing in array mult.
	for(i = 0; i < rowFirst; ++i)
	{
		for(j = 0; j < columnSecond; ++j)
		{
			for(k=0; k<columnFirst; ++k)
			{
				mult[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
			}
		}
	}

	printMatrix(mult, 10);
}




int main( int argc, const char* argv[] ) {
    int first[10][10];
	printMatrix(first, 10);
	printf("\n");
	printf("\n");

	int second[10][10];
	int res[10][10];
	printMatrix(second, 10);
	printf("\n");
	printf("\n");

	multiplyMatrices(first, second, res, 10, 10, 10, 10);
    return 1;
}