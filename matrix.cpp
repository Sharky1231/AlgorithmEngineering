#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <time.h>
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

	cout << rows;
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


//Matrix addition, assumes properly dimensioned matrices 
vector < vector < int > > addMatrices(vector < vector < int > > matrixLeft, vector < vector < int > > matrixRight) {
	
	vector<int> firstLeft = matrixLeft[0];

	int rowsLeft  = matrixLeft.size();
	int coloumnsLeft = firstLeft.size();
	
	for (int i = 0; i < rowsLeft; ++i) {
		for (int j = 0; j < coloumnsLeft; ++j) {
			matrixLeft[i][j] += matrixRight[i][j];
		}
	}

	return matrixLeft;
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

// A * B, Multiply matrixes multiply matrices recursively, assumes properly dimensioned matrices
vector < vector < int > > multiplyMatrices_recursive( vector < vector < int > > matrixLeft,  vector < vector < int > > matrixRight ) {
	

	
	vector<int> firstLeft = matrixLeft[0];
	vector<int> firstRight = matrixRight[0];
	
	int rowsLeft  = matrixLeft.size();
	int coloumnsLeft = firstLeft.size();
	int rowsRight = matrixRight.size();
	int coloumnsRight = firstRight.size();

	if (rowsLeft == 1 && coloumnsLeft == 1 && coloumnsRight == 1) {
		matrixLeft[0][0] *= matrixRight[0][0];
		return matrixLeft;
		
	}

	if (rowsLeft >= max(coloumnsLeft, coloumnsRight)) {
		//Split A horizontally, Multiply both with B
		
		int splitPoint = rowsLeft/2;

		vector < int > row;
		vector < vector < int > > A1; 
		vector < vector < int > > A2;
		A1.resize(splitPoint);
		A2.resize(rowsLeft-splitPoint);

		for (int i = 0; i < splitPoint; ++i) {
			row = matrixLeft[i];
			A1[i] = row;
		}

		for (int i = splitPoint; i < rowsLeft; ++i) {
			row = matrixLeft[i];
			A2[i-splitPoint] = row;
		}

		vector < vector < int > > topRes = multiplyMatrices_recursive(A1, matrixRight); 
		vector < vector < int > > botRes = multiplyMatrices_recursive(A2, matrixRight);

		int topResSize = botRes.size();
		//use topRes to store all
		int botResSize = botRes.size();
		for (int i = 0; i < botResSize; ++i) {
			topRes.push_back(botRes[i]); //Can we optimize this?
		}

		return topRes;
	}

	//Split A vertically, B Horizontally, multiply and add
	if (coloumnsLeft >= max(rowsLeft, coloumnsRight)) {
		

		int splitPoint = rowsRight/2;

		vector < int > row;
		vector < vector < int > > B1; 
		vector < vector < int > > B2;
		B1.resize(splitPoint);
		B2.resize(rowsRight-splitPoint);

		for (int i = 0; i < splitPoint; ++i) {
			row = matrixRight[i];
			B1[i] = row;
		}

		for (int i = splitPoint; i < rowsRight; ++i) {
			row = matrixRight[i];
			B2[i-splitPoint] = row;
		}


		splitPoint = coloumnsLeft/2;

		vector < vector < int > > A1;	
		vector < vector < int > > A2;
		A1.resize(rowsLeft);
		A2.resize(rowsLeft);

		for (int i = 0; i < rowsLeft; ++i) {
			A1[i].resize(splitPoint);
			A2[i].resize(coloumnsLeft - splitPoint);
			for (int j = 0; j < splitPoint; ++j) {
				A1[i][j] = matrixLeft[i][j];
			}
			for (int j = splitPoint; j < coloumnsLeft; ++j) {
				A2[i][j-splitPoint] = matrixLeft[i][j];
			}
		}
		
		vector < vector < int > > left = multiplyMatrices_recursive(A1, B1);
		vector < vector < int > > right = multiplyMatrices_recursive(A2, B2);

		vector < vector < int > > res = addMatrices(left, right);
		return res;

	}

	//Split B vertically, multiply both by A

	int splitPoint = coloumnsRight/2;

	vector < vector < int > > B1;	
	vector < vector < int > > B2;
	B1.resize(rowsRight);
	B2.resize(rowsRight);

	for (int i = 0; i < rowsRight; ++i) {
		B1[i].resize(splitPoint);
		B2[i].resize(coloumnsRight - splitPoint);
		for (int j = 0; j < splitPoint; ++j) {
			B1[i][j] = matrixRight[i][j];
		}
		for (int j = splitPoint; j < coloumnsRight; ++j) {
			B2[i][j-splitPoint] = matrixRight[i][j];
		}
	}

	vector < vector < int > > leftRes = multiplyMatrices_recursive(matrixLeft, B1);
	vector < vector < int > > rightRes = multiplyMatrices_recursive(matrixLeft, B2);

	int rightResRows = rightRes.size();
	int rightResColoumns = rightRes[0].size();


	for (int i = 0; i < rightResRows; ++i) {
		for (int j = 0; j < rightResColoumns; ++j) {
			leftRes[i].push_back(rightRes[i][j]);
		}
	}
	
	return leftRes;
}


int main( int argc, const char* argv[] ) {


	/*vector< vector < int > > leftMatrix = makeRandomMatrix(10, 20);
	vector< vector < int > > rightMatrix = makeRandomMatrix(20, 10);
	
	vector< vector < int > > leftMatrix1 = makeRandomMatrix(20, 20);
	vector< vector < int > > rightMatrix1 = makeRandomMatrix(20, 10);

	vector< vector < int > > leftMatrix2 = makeRandomMatrix(20, 20);
	vector< vector < int > > rightMatrix2 = makeRandomMatrix(20, 40);

	vector< vector < int > > leftMatrix3 = makeRandomMatrix(20, 40);
	vector< vector < int > > rightMatrix3 = makeRandomMatrix(40, 40);

	vector< vector < int > > leftMatrix4 = makeRandomMatrix(20, 50);
	vector< vector < int > > rightMatrix4 = makeRandomMatrix(50, 40);

	vector< vector < int > > leftMatrix5 = makeRandomMatrix(30, 50);
	vector< vector < int > > rightMatrix5 = makeRandomMatrix(50, 40);

	vector< vector < int > > leftMatrix6 = makeRandomMatrix(30, 50);
	vector< vector < int > > rightMatrix6 = makeRandomMatrix(50, 60);

	vector< vector < int > > res = multiplyMatrices_basic(leftMatrix, rightMatrix);
	vector< vector < int > > res1 = multiplyMatrices_basic(leftMatrix1, rightMatrix1);
	vector< vector < int > > res2 = multiplyMatrices_basic(leftMatrix2, rightMatrix2);
	vector< vector < int > > res3 = multiplyMatrices_basic(leftMatrix3, rightMatrix3);
	vector< vector < int > > res4 = multiplyMatrices_basic(leftMatrix4, rightMatrix4);
	vector< vector < int > > res5 = multiplyMatrices_basic(leftMatrix5, rightMatrix5);
	vector< vector < int > > res6 = multiplyMatrices_basic(leftMatrix6, rightMatrix6);
    */
	int i = 2;

	int m = i;
	int n = i;
	int p = i; 
	
	vector< vector < int > > A, B, res;
	// A * B
	// A = m * n, B = n * p
	while (i <= 300) {

		/*switch (i % 3) {
			
			case 1 :
				++m;
				break;
			case 2 :
				++n;
				break;
			case 3 :
				++p;
				break;
		}*/

		/*if (i <= 10) 
			++m;
		else if (i > 10 && i <= 20) 
			++n;
		else if (i > 20 && i <= 30)
			++p;
		else if (i > 30 && i <= 40)
			++m;
		else if (i > 40 && i <= 50)
			++n;
		else if (i > 50 && i <= 60)
			++p;
		else if (i > 60 && i <= 70)
			++m;
		else if (i > 70 && i <= 80)
			++n;
		else if (i > 80 && i <= 90)
			++p;
		else if (i > 90 && i <= 100)
			++m;*/

		if (i <= 100)
			++m;
		else if (i > 100 && i <= 200)
			++n;
		else if (i <=300)
			++p;
		

		A = makeRandomMatrix(m, n);
		B = makeRandomMatrix(n, p);  
		res = multiplyMatrices_recursive(A, B);
		printMatrix(res);
		++i;
		cout << i << "\n";
	}

	
	/*printf("res: ");
	printMatrix(res);
	printMatrix(res1);
	printMatrix(res2);
	printMatrix(res3);
	printMatrix(res4);
	printMatrix(res6);
	printMatrix(res6);*/
	

	return 0;
}