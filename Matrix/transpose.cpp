#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <omp.h>
#include </usr/local/include/valgrind/callgrind.h>
using namespace std;

int maxNumber = 10;

// It is assumed the vector is properly dimensioned
void printMatrix( vector < vector < int > > matrix ) {
	
	vector<int> first = matrix[0];

	int coloumns = matrix.size();
	int rows = first.size();

	printf("\n");

	for (int i = 0; i < coloumns; ++i) {
		
		printf( "| " );

		for (int j = 0; j < rows; ++j) {
			cout << matrix[i][j] ;
            printf( " " );
		}

		printf("| \n");
	}
	printf("\n");
}

//Makes matrix with random entrances, size defined by parameters
vector < vector < int > > makeRandomMatrix(int rows, int coloumns) {

	vector < vector < int > > matrix;

	matrix.resize(rows);
	
	for (int i = 0; i < rows; ++i) {
		matrix[i].resize(coloumns);
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < coloumns; ++j) {
			matrix[i][j] = rand() % maxNumber;
		}
	}

	return matrix;
	
}


vector < vector < int > > makeZeroMatrix(int rows, int coloumns) {

	vector < vector < int > > matrix;

	matrix.resize(rows);
	
	for (int i = 0; i < rows; ++i) {
		matrix[i].resize(coloumns);
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < coloumns; ++j) {
			matrix[i][j] = 0;
		}
	}

	return matrix;
	
}

vector < vector < int > > transposeMatrix(vector < vector < int > > matrix){
	
	int rows = matrix.size();
	int coloumns = matrix[0].size();
	vector < int > row;
	
	vector < vector < int > > resultMatrix;
	resultMatrix.resize(coloumns);

	for (int i = 0; i < coloumns; i++){
		resultMatrix[i].resize(rows);
	}
 
	for (int i = 0; i < rows; i++){

		for (int j = 0; j < coloumns; j++){
			resultMatrix[j][i] = matrix[i][j];
		}
	}
	return resultMatrix;
}


//Basic matrix multiplication, assumes properly dimensioned matrices

vector < vector < int > > multiplyMatrices_basic( vector < vector < int > > matrixLeft,  vector < vector < int > > matrixRight )
{

	vector<int> firstLeft = matrixLeft[0];
	vector<int> firstRight = matrixRight[0];

	int rowsLeft  = matrixLeft.size();
	int coloumnsLeft = firstLeft.size();
	int rowsRight = matrixRight.size();
	int coloumnsRight = firstRight.size();

	int i, j, k;

	vector< vector < int > > res;
	res.resize(rowsLeft );

	// Initialize result matrix to correct size and filled with 0
	for(i = 0; i < rowsLeft ; ++i)
	{
		res[i].resize(coloumnsRight);
		for(j = 0; j < coloumnsRight; ++j)
		{
			res[i][j] = 0;
		}
	} 

	//Actual multiplication begins here
	
	clock_t begin = clock();
    CALLGRIND_ZERO_STATS;
    CALLGRIND_START_INSTRUMENTATION;

	// Multiplying matrices
	//#pragma omp parallel for
	for(i = 0; i < rowsLeft ; ++i)
	{
		for(j = 0; j < coloumnsRight; ++j)
		{
			for(k=0; k < rowsRight; ++k)
			{
				res[i][j] += matrixLeft[i][k] * matrixRight[k][j];
			}
		}
	} 

	// multiplication done
	CALLGRIND_STOP_INSTRUMENTATION;
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	int numberOfElements = rowsLeft * coloumnsLeft + rowsRight * coloumnsRight;
    char msg[100];
    sprintf(msg,"%d %f", numberOfElements, elapsed_secs);
    CALLGRIND_DUMP_STATS_AT(msg);

    cout << "\n----Results----- " << endl;
    cout << "Matrix multiplication took: " << elapsed_secs << " seconds" << endl;
	cout << "Matrix A size: " << rowsLeft << "x" << coloumnsLeft << "\n";
	cout << "Matrix B size: " << rowsRight << "x" << coloumnsRight << "\n";
	return res;
}

vector < vector < int > > multiplyMatrices_transpose(vector < vector < int > > A, vector < vector < int > > B) {

	
	vector<int> firstA = A[0];
	vector<int> firstB = B[0];

	int rowsLeft  = A.size();
	int coloumnsLeft = firstA.size();
	int rowsRight = B.size();
	int coloumnsRight = firstB.size();

	vector < vector < int > > res = makeZeroMatrix(rowsLeft, coloumnsRight);

	

	clock_t begin = clock();
    CALLGRIND_ZERO_STATS;
    CALLGRIND_START_INSTRUMENTATION;

	
	vector < vector < int > > C = transposeMatrix(B);

	for(int i = 0; i < rowsLeft ; ++i)
	{
		for(int j = 0; j < coloumnsRight; ++j)
		{
			for(int k = 0; k < rowsRight; ++k)
			{
				res[i][j] += A[i][k] * C[j][k];
			}
		}
	} 

	CALLGRIND_STOP_INSTRUMENTATION;
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	int numberOfElements = rowsLeft * coloumnsLeft + rowsRight * coloumnsRight;
    char msg[100];
    sprintf(msg,"2 %d %f", numberOfElements, elapsed_secs);
    CALLGRIND_DUMP_STATS_AT(msg);

	cout << "\n----Results----- " << endl;
    cout << "Matrix multiplication took: " << elapsed_secs << " seconds" << endl;
	cout << "Matrix A size: " << rowsLeft << "x" << coloumnsLeft << "\n";
	cout << "Matrix B size: " << rowsRight << "x" << coloumnsRight << "\n";

	return res;

} 



int main( int argc, const char* argv[] ) {

	int i = 5;

	int m = i;
	int n = i;
	int p = i; 
	
	vector< vector < int > > A, B, res;
	// A * B
	// A = m * n, B = n * p
	int maxSize = 1000;
	int increment = 50;
	while (i <= maxSize) {

		

		A = makeRandomMatrix(m, n);
		B = makeRandomMatrix(n, p);  

		switch (i % 3) {
			case 0 : 
				m += increment;
				break;
			case 1 : 
				n += increment;
				break;
			case 2 : 
				p += increment;
				break;
		}

		cout << "i: " <<  i << "\n";
		i += 50;

		cout << "m: " << m << "\n"; 
		cout << "n: " << n << "\n";
		cout << "p: " << p << "\n";  
		//printMatrix(A);
		//printMatrix(B);

		cout << "\n \n \n";

		//res = makeZeroMatrix(m, p);
		//printMatrix(res);
		//multiplyMatrices_recursive_callgrind(A, B, res, m, n, p);
		//res = multiplyMatrices_recursive(A, B, res, 0, m, 0, n, 0, n, 0, p, 0, m, 0, p);
		//res = multiplyMatrices_basic(A, B);
		res = multiplyMatrices_transpose(A, B);

	}
	
	/*A = makeRandomMatrix(4, 2);
	printMatrix(A);
	B = makeRandomMatrix(2, 8);
	printMatrix(B);  
	res = makeZeroMatrix(4, 8);

	multiplyMatrices_recursive(A, B, res, 0, 4, 0, 2, 0, 2, 0, 8, 0, 4, 0, 8);
	printMatrix(res);
	printMatrix(multiplyMatrices_basic(A, B));*/

	/*A = makeRandomMatrix(160, 160);
	B = makeRandomMatrix(160, 160);
	res = multiplyMatrices_transpose(A, B);

	res = multiplyMatrices_basic(A, B);*/
	
	return 0;
}