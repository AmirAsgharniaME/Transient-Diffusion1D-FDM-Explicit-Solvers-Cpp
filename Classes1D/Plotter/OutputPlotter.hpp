#ifndef OUTPUTPLOTTER_HPP
#define OUTPUTPLOTTER_HPP

#include <cstdio>
#include <string>

class OutputPlotter {
private:
    FILE* gnuplotPipe;
    std::string plotTitle;

    void configurePlot() const;

public:
    OutputPlotter(const std::string& title = "Solution Comparison");
    ~OutputPlotter();

    void plotComparison(
        const std::string& file1,
        const std::string& label1,
        const std::string& file2,
        const std::string& label2,
        const std::string& file3,
        const std::string& label3
    ) const;
};

#endif
