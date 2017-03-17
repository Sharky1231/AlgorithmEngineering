VALGRIND = valgrind --tool=callgrind --cache-sim=yes --branch-sim=yes --instr-atstart=no

all : binary.pdf

clean : 
	rm -f callgrind.out.* *~ binary-experiments.done binary binary.data *.pdf

binary : binarySearch.cpp
	g++ -g -O0 -fopenmp binarySearch.cpp -o binarySearch

binary-experiments.done : binary
	rm -f callgrind.out.*
	touch binary-experiments.done
	$(VALGRIND) ./binarySearch

binary.data : binary-experiments.done
	rm -f binary.data 
	for f in `find . -name "callgrind.out.*.*"`; \
	   do echo `cat $$f | egrep "Client|totals" \
	            | sed -e 's/.*: *//' \
	            | tr '\n' ' '` >> binary.data; done
	sort -n binary.data > binary.data.tmp
	mv binary.data.tmp binary.data

binary.pdf : binary.data binary.gnuplot
	gnuplot "binary.gnuplot"
