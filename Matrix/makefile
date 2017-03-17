VALGRIND = valgrind --tool=callgrind --cache-sim=yes --branch-sim=yes --instr-atstart=no

all : matrix.pdf

clean : 
	rm -f callgrind.out.* *~ matrix-experiments.done matrix matrix.data *.pdf

matrix : recurs.cpp iterative.cpp transpose.cpp
	g++ -g -O0 -fopenmp recurs.cpp -o recurs
	g++ -g -O0 -fopenmp iterative.cpp -o iterative
	g++ -g -O0 -fopenmp transpose.cpp -o transpose

matrix-experiments.done : matrix
	rm -f callgrind.out.*
	touch matrix-experiments.done
	$(VALGRIND) ./recurs
	$(VALGRIND) ./iterative
	$(VALGRIND) ./transpose

matrix.data : matrix-experiments.done
	rm -f matrix.data 
	for f in `find . -name "callgrind.out.*.*"`; \
	   do echo `cat $$f | egrep "Client|totals" \
	            | sed -e 's/.*: *//' \
	            | tr '\n' ' '` >> matrix.data; done
	sort -k1,1 -k2n matrix.data > matrix.data.tmp
	mv matrix.data.tmp matrix.data

matrix.pdf : matrix.data matrix.gnuplot
	gnuplot "matrix.gnuplot"
