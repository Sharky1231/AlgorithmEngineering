VALGRIND = valgrind --tool=callgrind --cache-sim=yes --branch-sim=yes --instr-atstart=no

all : matrix.pdf

clean : 
	rm -f callgrind.out.* *~ matrix-experiments.done matrix matrix.data *.pdf

matrix : matrix.cpp
	g++ -g -O0 -fopenmp matrix.cpp -o matrix

matrix-experiments.done : matrix
	rm -f callgrind.out.*
	touch matrix-experiments.done
	$(VALGRIND) ./matrix

matrix.data : matrix-experiments.done
	rm -f matrix.data 
	for f in `find . -name "callgrind.out.*.*"`; \
	   do echo `cat $$f | egrep "Client|totals" \
	            | sed -e 's/.*: *//' \
	            | tr '\n' ' '` >> matrix.data; done
	sort -n matrix.data > matrix.data.tmp
	mv matrix.data.tmp matrix.data

matrix.pdf : matrix.data matrix.gnuplot
	gnuplot "matrix.gnuplot"
