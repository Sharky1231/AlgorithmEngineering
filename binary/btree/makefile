VALGRIND = valgrind --tool=callgrind --cache-sim=yes --branch-sim=yes --instr-atstart=no

all : btree.pdf

clean : 
	rm -f callgrind.out.* *~ btree-experiments.done btree btree.data *.pdf

btree : btree.cpp
	g++ -g -O0 -fopenmp btree.cpp -o btree

btree-experiments.done : btree
	rm -f callgrind.out.*
	touch btree-experiments.done
	$(VALGRIND) ./btree

btree.data : btree-experiments.done
	rm -f btree.data 
	for f in `find . -name "callgrind.out.*.*"`; \
	   do echo `cat $$f | egrep "Client|totals" \
	            | sed -e 's/.*: *//' \
	            | tr '\n' ' '` >> btree.data; done
	sort -n btree.data > btree.data.tmp
	mv btree.data.tmp btree.data

btree.pdf : btree.data btree.gnuplot
	gnuplot "btree.gnuplot"
