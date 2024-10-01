set terminal pngcairo font "Arial,12"  # Set output format and size

# Loop through L values from 2 to 50
do for [L=2:50] {
    filename = sprintf("percolation_data_L_%d.csv", L)
    output_filename = sprintf("percolation_plot_L_%d.png", L)  # Define output filename for each plot
    set output output_filename  # Set the output file for the current plot

    set xlabel 'p'                            # X-axis label
    set ylabel 'Fraction of Passes'           # Y-axis label                                 # Add grid
    set yrange [-0.1:1.12]                        # Set y-axis range from 0 to 1.1
    set style data points                      # Use scatter plot style (points)

    # Plot the data for the current L
    plot filename using 1:2 with points pointtype 7 pointsize 0.2 linecolor rgb "black" title sprintf('L = %d', L)
}

unset output
