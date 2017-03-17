VALGRIND = valgrind --tool=callgrind --cache-sim=yes --branch-sim=yes --instr-atstart=no

all : radix.pdf

clean : 
	rm -f callgrind.out.* *~ radix-experiments.done radix radixAll.data

radix :
	g++ -fopenmp -g -O0 radixLSD.cpp -o radixLSD
	g++ -fopenmp -g -O0 radixMSD.cpp -o radixMSD

radix-experiments.done : radix
	rm -f callgrind.out.*
	touch radix-experiments.done
	$(VALGRIND) ./radixLSD
	$(VALGRIND) ./radixMSD

radixAll.data : radix-experiments.done
	rm -f radixAll.data 
	for f in `find . -name "callgrind.out.*.*"`; \
	   do echo `cat $$f | egrep "Client|totals" \
	            | sed -e 's/.*: *//' \
	            | tr '\n' ' '` >> radixAll.data; done
	sort -n radixAll.data > radixAll.data.tmp
	mv radixAll.data.tmp radixAll.data


radix.pdf : radixAll.data radix.gnuplot
	gnuplot "radix.gnuplot"
