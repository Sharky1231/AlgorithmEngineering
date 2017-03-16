set terminal pdf
set output "matrixMisspredictions.pdf"
set xlabel "number of elements"
set ylabel "branch miss predictions"

plot "matrix.data" using 1:13 with linespoints pointtype 7 title "branch miss predictions"

set output "matrixRuntime.pdf"
set xlabel "number of elements"
set ylabel "execution time (s)"

plot "matrix.data" using 1:2 with linespoints pointtype 7 title "runtime"

set output "matrixCacheMiss.pdf"
set xlabel "number of elements"
set ylabel "D1 read cache misses"

plot "matrix.data" using 1:7 with linespoints pointtype 7 title "cache"

set output "matrixInstructions.pdf"
set xlabel "number of elements"
set ylabel "number of instructions"

plot "matrix.data" using 1:3 with linespoints pointtype 7 title "instructions"

set output "matrixDataReads.pdf"
set xlabel "number of elements"
set ylabel "number of Data Reads"

plot "matrix.data" using 1:3 with linespoints pointtype 7 title "data reads"

set output "matrixDataWrites.pdf"
set xlabel "number of elements"
set ylabel "number of Data Writes"

plot "matrix.data" using 1:3 with linespoints pointtype 7 title "data writes"
