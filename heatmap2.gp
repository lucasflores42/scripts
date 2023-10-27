#set terminal postscript eps enhanced color
#set output 'invest_diagrama_triang.eps'

#esse programa serve pra fazer heatmap com um arquivo de 3 columas sendo (x,y,z) e cada valor de x é separado por uma linha em branco

#ex: 1 0 0.5
#    1 1 0.5
#    1 2 0.5
#
#    2 0 0.5
#    2 1 0.5
#    2 2 0.5


unset key
set xrange[4.2:5.5]
set xlabel 'r'

set yrange[0.5:5.]
set ylabel 'c'

set pm3d explicit
set pm3d map

#set pm3d interpolate 0,0

splot 'histograma2.dat' u 1:2:($3/10000) w pm3d




pause -1
