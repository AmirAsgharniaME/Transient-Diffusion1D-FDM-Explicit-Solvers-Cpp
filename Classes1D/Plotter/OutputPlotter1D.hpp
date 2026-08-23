#pragma once

#include <cstdio>
#include <string>

class OutputPlotter1D {
private:
    FILE* gnuplotPipe;
    std::string plotTitle;

    void configurePlot() const;

public:
    OutputPlotter1D(const std::string& title = "Solution Comparison");
    ~OutputPlotter1D();

    void plotComparison(
        const std::string& file1,
        const std::string& label1,
        const std::string& file2,
        const std::string& label2,
        const std::string& file3,
        const std::string& label3
    ) const;
};

