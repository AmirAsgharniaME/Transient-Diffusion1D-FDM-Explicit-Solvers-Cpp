#include "Plotter/ResidualPlotter.hpp"
#include <iostream>

#ifdef _WIN32
    #define POPEN _popen
    #define PCLOSE _pclose
#else
    #define POPEN popen
    #define PCLOSE pclose
#endif

ResidualPlotter::ResidualPlotter(const std::string& plotTitle)
    : gnuplotPipe(nullptr), title(plotTitle) {

    // Open a pipe to the gnuplot executable using cross-platform popen
    gnuplotPipe = POPEN("gnuplot -persist", "w");

    if (gnuplotPipe) {
        // Initial Gnuplot configuration
        fprintf(gnuplotPipe, "set title '%s'\n", title.c_str());
        fprintf(gnuplotPipe, "set xlabel 'Iteration'\n");
        fprintf(gnuplotPipe, "set ylabel 'Residual'\n");
        fprintf(gnuplotPipe, "set logscale y\n");
        fprintf(gnuplotPipe, "set autoscale y\n");
        fprintf(gnuplotPipe, "set grid\n");
        fprintf(gnuplotPipe, "set key left top\n");
        fprintf(gnuplotPipe, "set style data lines\n");
        fflush(gnuplotPipe);
    } else {
        std::cerr << "Error: Could not open pipe to gnuplot. Ensure gnuplot is in your PATH." << std::endl;
    }
}

ResidualPlotter::~ResidualPlotter() {
    if (gnuplotPipe) {
        PCLOSE(gnuplotPipe);
        gnuplotPipe = nullptr;
    }
}

void ResidualPlotter::updatePlot(const std::vector<double>& iterations,
                                 const std::vector<double>& residuals) {
    if (!gnuplotPipe || iterations.size() != residuals.size() || iterations.empty()) {
        return;
    }

    // Command to start plotting from inline data
    fprintf(gnuplotPipe, "plot '-' with lines lw 2 title 'U-Residual'\n");

    // Send data points one by one
    for (size_t i = 0; i < iterations.size(); ++i) {
        fprintf(gnuplotPipe, "%f %e\n", iterations[i], residuals[i]);
    }

    // 'e' signals the end of the data stream for the current plot command
    fprintf(gnuplotPipe, "e\n");
    fflush(gnuplotPipe);
}
