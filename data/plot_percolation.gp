set datafile separator ','
set terminal pdfcairo font "Ariel,12"
set output "percolation_L_50.pdf"
set yrange [-0.1:1.2]
set xlabel 'p'                      # X-axis label
set ylabel 'Fraction of Passes'      # Y-axis label
set style data points                # Use scatter plot style (points)

plot 'percolation_data_L_50.txt' using 1:2 with points pointtype 7 pointsize 0.2 linecolor rgb "black" title 'Percolation Fraction'
