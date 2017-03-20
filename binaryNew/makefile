VALGRIND = valgrind --tool=callgrind --cache-sim=yes --branch-sim=yes --instr-atstart=no

all : binary.pdf

clean : 
	rm -f callgrind.out.* *~ binary-experiments.done binary binary.data *.pdf

binary :
	g++ -g -O0 -fopenmp iterative.cpp -o iterative
	g++ -g -O0 -fopenmp recursive.cpp -o recursive
	g++ -g -O0 -fopenmp btree.cpp -o btree
	g++ -g -O0 -fopenmp btreeBalanced.cpp -o btreeBalanced

binary-experiments.done : binary
	rm -f callgrind.out.*
	touch binary-experiments.done
	$(VALGRIND) ./iterative
	$(VALGRIND) ./recursive
	$(VALGRIND) ./btree
	$(VALGRIND) ./btreeBalanced

binary.data : binary-experiments.done
	rm -f binary.data 
	for f in `find . -name "callgrind.out.*.*"`; \
	   do echo `cat $$f | egrep "Client|totals" \
	            | sed -e 's/.*: *//' \
	            | tr '\n' ' '` >> binary.data; done
	sort -k1,1 -k2n binary.data > binary.data.tmp
	mv binary.data.tmp binary.data

binary.pdf : binary.data binary.gnuplot
	gnuplot "binary.gnuplot"
