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

int main( int argc, const char* argv[] ) {
	int i = 2;

	int m = i;
	int n = i;
	int p = i; 
	
	vector< vector < int > > A, B, res;
	// A * B
	// A = m * n, B = n * p
	while (i <= 300) {

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

	

	return 0;
}