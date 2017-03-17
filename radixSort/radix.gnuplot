set terminal pdf

set output "mispredictions.pdf"
set xlabel "number of elements"
set ylabel "branch miss predictions"

plot "radixAll.data" using 2:($1 ==1  ? $14 : 1/0) with linespoints pointtype 7 title "LSD", \
	 "radixAll.data" using 2:($1 ==2  ? $14 : 1/0) with linespoints pointtype 7 title "MSD"
	 
set output "runtime.pdf"
set xlabel "number of elements"
set ylabel "execution time (s)"
	 
plot "radixAll.data" using 2:($1 ==1  ? $3 : 1/0) with linespoints pointtype 7 title "LSD", \
	 "radixAll.data" using 2:($1 ==2  ? $3 : 1/0) with linespoints pointtype 7 title "MSD"

set output "cacheMisses.pdf"
set xlabel "number of elements"
set ylabel "cache misses"
	 
plot "radixAll.data" using 2:($1 ==1  ? $8 : 1/0) with linespoints pointtype 7 title "LSD", \
	 "radixAll.data" using 2:($1 ==2  ? $8 : 1/0) with linespoints pointtype 7 title "MSD"

