set terminal pdf
set output "btreeMisspredictions.pdf"
set xlabel "number of elements"
set ylabel "branch miss predictions"

plot "btree.data" using 1:13 with linespoints pointtype 7 title "branch miss predictions"

set output "btreeRuntime.pdf"
set xlabel "number of elements"
set ylabel "execution time (s)"

plot "btree.data" using 1:2 with linespoints pointtype 7 title "runtime"

set output "btreeCacheMiss.pdf"
set xlabel "number of elements"
set ylabel "D1 read cache misses"

plot "btree.data" using 1:7 with linespoints pointtype 7 title "cache"

set output "btreeInstructions.pdf"
set xlabel "number of elements"
set ylabel "number of instructions"

plot "btree.data" using 1:3 with linespoints pointtype 7 title "instructions"

set output "btreeDataReads.pdf"
set xlabel "number of elements"
set ylabel "number of Data Reads"

plot "btree.data" using 1:4 with linespoints pointtype 7 title "data reads"

set output "btreeDataWrites.pdf"
set xlabel "number of elements"
set ylabel "number of Data Writes"

plot "btree.data" using 1:5 with linespoints pointtype 7 title "data writes"
