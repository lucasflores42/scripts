#set terminal postscript eps enhanced color
#set output 'invest_diagrama_triang.eps'

#set label 1 "(b)" font ",35" at 0.55, 0.9 front

#Verde p/ P's
#set palette defined (0 "#ffffff", 0.5 "#99d8c9", 1 "#2ca25f")
#Azul p/ Coop.
#set palette defined (0 "#ffffff", 0.5 "#9ecae1", 1 "#3182bd")

#set palette defined (0 0 0 0.5, 1 0 0 1, 2 0 0.5 1, 3 0 1 1, 4 0.5 1 0.5, 5 1 1 0, 6 1 0.5 0, 7 1 0 0, 8 0.5 0 0)

#set palette rgbformulae -31,13,22

unset key
#set cbrange [-10:]

#set palette defined (-10 "black", -5 "white", 50 "blue")

#set cblabel "{/Symbol r}_c + {/Symbol r}_p"
#set cblabel "{/Symbol r}_p" font ",25"
set cblabel "Density" font ",20" offset 1,0,0
#unset cbtics
#unset colorbox
set view map
#set dgrid3d

set pm3d map
#set pm3d interpolate 0,0
set lmargin at screen 0.15
set rmargin at screen 0.8
set xtics  font ",20" # 0,3,15
set ytics font ",20"  #3,1.,7.5 
set xrange[-0.5:5.5]
#set yrange[4.2:5.2]
set xlabel '{c}' font ",25"
set ylabel 'r' font ",25" offset -4,0,0 rotate by 0
#set key font ",30" tamanho da label dentro da figura

numero_pontos_x = 1  # eixo está em inteiros, se variaçao entre pontos é 0.1 tem que dividir por 10 (valor real em 1 estaria em 10) 10 = 1/0.1 (botar numero de pontos entre 2 inteiros)

valor_inicial_x = 0

numero_pontos_y = 10  # eixo está em inteiros, se variaçao entre pontos é 0.1 tem que dividir por 10 (valor real em 1 estaria em 10) 10 = 1/0.1

valor_inicial_y = 2.0

splot "commitment_random_focal_matriz.dat" u (($1/numero_pontos_x) + valor_inicial_x):(($2/numero_pontos_y)+valor_inicial_y):3 matrix with image

#splot "commitment_random_focal_matriz.dat" u 1:2:3 matrix with image

pause -1
