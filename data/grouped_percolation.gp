set datafile separator ','
set terminal pdfcairo font "Arial,12"
set output "grouped_Ls_50_100.pdf"
set yrange [-0.1:1.2]
set xlabel 'p'                      # X-axis label
set ylabel 'Fraction of Passes'      # Y-axis label
set style data points   

# Plot both datasets
plot 'percolation_data_L_50.txt' using 1:2 with points pointtype 7 pointsize 0.2 title 'Dataset 1', \
     'percolation_data_L_55.txt' using 1:2 with points pointtype 7 pointsize 0.2 title 'Dataset 2', \
     'percolation_data_L_60.txt' using 1:2 with points pointtype 7 pointsize 0.2 title 'Dataset 3', \
     'percolation_data_L_65.txt' using 1:2 with points pointtype 7 pointsize 0.2 title 'Dataset 4', \
     'percolation_data_L_70.txt' using 1:2 with points pointtype 7 pointsize 0.2 title 'Dataset 5', \
     'percolation_data_L_75.txt' using 1:2 with points pointtype 7 pointsize 0.2 title 'Dataset 6', \
     'percolation_data_L_80.txt' using 1:2 with points pointtype 7 pointsize 0.2 title 'Dataset 7', \
     'percolation_data_L_85.txt' using 1:2 with points pointtype 7 pointsize 0.2 title 'Dataset 8', \
     'percolation_data_L_90.txt' using 1:2 with points pointtype 7 pointsize 0.2 title 'Dataset 9', \
     'percolation_data_L_95.txt' using 1:2 with points pointtype 7 pointsize 0.2 title 'Dataset 10', \
     'percolation_data_L_100.txt' using 1:2 with points pointtype 7 pointsize 0.2 title 'Dataset 11'





