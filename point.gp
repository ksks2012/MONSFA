reset
set terminal pdf font "Times New Roman, 12"

set style line 1 lc rgb 'black'  lt 1 lw 1 pt 6 pi -1 ps 0.5
#set style line 2 lc rgb 'black'   lt 1 lw 1 pt 7 pi -1 ps 1

set key top right Left reverse box
set title "MONSFA"
set xlabel "Func 1"
set ylabel "Func 2"
#set xrange [0:4]
#set yrange [0:4]
set grid
#set style data line
set terminal pdf
set output "MONSFA.pdf"
plot "output.dat" with point title ' MONSFA' ls 1, \

#"eil51.tsp" with point title '  eil51' ls 1
