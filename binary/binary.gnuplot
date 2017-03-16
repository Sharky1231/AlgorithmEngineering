set terminal pdf
set output "binaryMisspredictions.pdf"
set xlabel "number of elements"
set ylabel "branch miss predictions"

plot "binary.data" using 1:13 with linespoints pointtype 7 title "branch miss predictions"

set output "binaryRuntime.pdf"
set xlabel "number of elements"
set ylabel "execution time (s)"

plot "binary.data" using 1:2 with linespoints pointtype 7 title "runtime"

set output "binaryCacheMiss.pdf"
set xlabel "number of elements"
set ylabel "D1 read cache misses"

plot "binary.data" using 1:7 with linespoints pointtype 7 title "cache"

set output "binaryInstructions.pdf"
set xlabel "number of elements"
set ylabel "number of instructions"

plot "binary.data" using 1:3 with linespoints pointtype 7 title "instructions"

set output "binaryDataReads.pdf"
set xlabel "number of elements"
set ylabel "number of Data Reads"

plot "binary.data" using 1:3 with linespoints pointtype 7 title "data reads"

set output "binaryDataWrites.pdf"
set xlabel "number of elements"
set ylabel "number of Data Writes"

plot "binary.data" using 1:3 with linespoints pointtype 7 title "data writes"
