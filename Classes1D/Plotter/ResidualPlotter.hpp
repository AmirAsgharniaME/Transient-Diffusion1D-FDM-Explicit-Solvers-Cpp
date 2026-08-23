#pragma once

#include <cstdio>
#include <string>
#include <vector>

class ResidualPlotter {
private:
    FILE* gnuplotPipe;
    std::string title;

public:
    explicit ResidualPlotter(const std::string& plotTitle);
    ~ResidualPlotter();

    void updatePlot(const std::vector<double>& iterations,
                    const std::vector<double>& residuals);
};

