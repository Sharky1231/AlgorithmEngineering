set terminal pdf
set output "binaryMisspredictions.pdf"
set xlabel "number of elements"
set ylabel "branch miss predictions"

plot "binary.data" using 2:($1 ==1  ? $14 : 1/0) with linespoints pointtype 7 title "recursive", \
	 "binary.data" using 2:($1 ==2  ? $14 : 1/0) with linespoints pointtype 7 title "iterative", \
	 "binary.data" using 2:($1 ==3  ? $14 : 1/0) with linespoints pointtype 7 title "btree", \
	 "binary.data" using 2:($1 ==4  ? $14 : 1/0) with linespoints pointtype 7 title "btree balanced"

set output "binaryRuntime.pdf"
set xlabel "number of elements"
set ylabel "execution time (s)"

plot "binary.data" using 2:($1 ==1  ? $3 : 1/0) with linespoints pointtype 7 title "recursive", \
     "binary.data" using 2:($1 ==2  ? $3 : 1/0) with linespoints pointtype 7 title "iterative", \
	 "binary.data" using 2:($1 ==3  ? $3 : 1/0) with linespoints pointtype 7 title "btree", \
	 "binary.data" using 2:($1 ==4  ? $3 : 1/0) with linespoints pointtype 7 title "btree balanced"

set output "binaryCacheMiss.pdf"
set xlabel "number of elements"
set ylabel "D1 read cache misses"

plot "binary.data" using 2:($1 ==1  ? $8 : 1/0) with linespoints pointtype 7 title "recursive", \
     "binary.data" using 2:($1 ==2  ? $8 : 1/0) with linespoints pointtype 7 title "iterative", \
	 "binary.data" using 2:($1 ==3  ? $8 : 1/0) with linespoints pointtype 7 title "btree", \
	 "binary.data" using 2:($1 ==4  ? $8 : 1/0) with linespoints pointtype 7 title "btree balanced"

set output "binaryInstructions.pdf"
set xlabel "number of elements"
set ylabel "number of instructions"

plot "binary.data" using 2:($1 ==1  ? $4 : 1/0) with linespoints pointtype 7 title "recursive", \
     "binary.data" using 2:($1 ==2  ? $4 : 1/0) with linespoints pointtype 7 title "recursive", \
	 "binary.data" using 2:($1 ==3  ? $4 : 1/0) with linespoints pointtype 7 title "btree", \
	 "binary.data" using 2:($1 ==4  ? $4 : 1/0) with linespoints pointtype 7 title "btree balanced"

set output "binaryDataReads.pdf"
set xlabel "number of elements"
set ylabel "number of Data Reads"

plot "binary.data" using 2:($1 ==1  ? $5 : 1/0) with linespoints pointtype 7 title "recursive", \
     "binary.data" using 2:($1 ==2  ? $5 : 1/0) with linespoints pointtype 7 title "iterative", \
	 "binary.data" using 2:($1 ==3  ? $5 : 1/0) with linespoints pointtype 7 title "btree", \
	 "binary.data" using 2:($1 ==4  ? $5 : 1/0) with linespoints pointtype 7 title "btree balanced"

set output "binaryDataWrites.pdf"
set xlabel "number of elements"
set ylabel "number of Data Writes"

plot "binary.data" using 2:($1 ==1  ? $6 : 1/0) with linespoints pointtype 7 title "recursive", \
	 "binary.data" using 2:($1 ==2  ? $6 : 1/0) with linespoints pointtype 7 title "iterative", \
	 "binary.data" using 2:($1 ==3  ? $6 : 1/0) with linespoints pointtype 7 title "btree", \
	 "binary.data" using 2:($1 ==4  ? $6 : 1/0) with linespoints pointtype 7 title "btree balanced"
