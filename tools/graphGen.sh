#! /bin/sh

DATE=$(date '+%d-%m-%Y-%H:%M:%S')

all=$(ls ../result | grep -v "*.ps")
arg=""
i=0
for file in $all
do
	if [ $i -eq 0 ]; then
		arg="plot \"../result/$file\" using 1:3"
	else
		arg=$arg", \"../result/$file\" using 1:3"
	fi
	i=1
done

gnuplot <<EOF
set term postscript landscape
set output '../result/graphic${DATE}.ps'

set xlabel 'B'
set ylabel 'NbSmooth'
set grid
set nokey
set title 'link between size of B and n'
$arg
EOF

