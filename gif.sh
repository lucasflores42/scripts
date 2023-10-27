set terminal gif animate delay 1
set output 'loner.gif'				#compilar: gnuplot oi.sh
set key bottom
stats 'loner.dat' nooutput

set autoscale keepfix
set palette model RGB
unset colorbox
unset border
unset xtics
unset ytics
set palette defined ( 0 "purple", 1 "black",  2 "white")
set cbrange[0:2]
set size square
set xrange [0:100]
set yrange [0:100]
 #do for [i=0:int(STATS_blocks)]  {
					#i=0:12 plota 13 matrizes

do for [i=0:500] {
	
    plot 'loner.dat'  index (i) matrix with image;

}	



  


