reset
set terminal pdf font "Times New Roman, 12"

set style line 1 lc rgb 'black'  lt 1 lw 1 pt 6 pi -1 ps 1
set style line 2 lc rgb 'black'   lt 1 lw 1 pt 7 pi -1 ps 1

set key top right Left reverse box
set title "pr76"
set xlabel "x"
set ylabel "y"
#set xrange [0:80]
#set yrange [0:13000]
set grid
#set style data line
set terminal pdf
set output "tsp.pdf"
plot "1.dat" with point title '  dat' ls 1, \

#"eil51.tsp" with point title '  eil51' ls 1
