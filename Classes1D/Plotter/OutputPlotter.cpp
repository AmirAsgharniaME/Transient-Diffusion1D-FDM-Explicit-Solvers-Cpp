#include "Plotter/OutputPlotter.hpp"

#include <stdexcept>

#ifdef _WIN32
    #define POPEN _popen
    #define PCLOSE _pclose
#else
    #define POPEN popen
    #define PCLOSE pclose
#endif

OutputPlotter::OutputPlotter(const std::string& title)
    : gnuplotPipe(nullptr), plotTitle(title) {
    gnuplotPipe = POPEN("gnuplot -persist", "w");

    if (gnuplotPipe == nullptr) {
        throw std::runtime_error("Failed to open Gnuplot.");
    }

    configurePlot();
}

OutputPlotter::~OutputPlotter() {
    if (gnuplotPipe != nullptr) {
        fprintf(gnuplotPipe, "exit\n");
        PCLOSE(gnuplotPipe);
        gnuplotPipe = nullptr;
    }
}

void OutputPlotter::configurePlot() const {
    fprintf(gnuplotPipe, "set terminal qt size 1000,700\n");
    fprintf(gnuplotPipe, "set title '%s'\n", plotTitle.c_str());
    fprintf(gnuplotPipe, "set xlabel 'x'\n");
    fprintf(gnuplotPipe, "set ylabel 'Velocity'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set key top right\n");
    fprintf(gnuplotPipe, "set autoscale\n");
    fflush(gnuplotPipe);
}

void OutputPlotter::plotComparison(
    const std::string& file1,
    const std::string& label1,
    const std::string& file2,
    const std::string& label2,
    const std::string& file3,
    const std::string& label3
) const {
    fprintf(
        gnuplotPipe,
        "plot '%s' using 1:2 with lines lw 2 lc rgb 'blue' title '%s', "
        "'%s' using 1:2 with points pt 7 ps 1.2 lc rgb 'red' title '%s', "
        "'%s' using 1:2 with lines lw 2 lc rgb 'dark-green' title '%s'\n",
        file1.c_str(), label1.c_str(),
        file2.c_str(), label2.c_str(),
        file3.c_str(), label3.c_str()
    );

    fflush(gnuplotPipe);
}
