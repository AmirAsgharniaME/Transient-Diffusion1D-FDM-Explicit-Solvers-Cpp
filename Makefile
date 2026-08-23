CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I. -IClasses1D -Imain

# Header prerequisites
HEADERS = $(wildcard EssentialHeaders/*.hpp)

# Source files (mapped accurately to project tree)
SRCS = main/main.cpp \
       Classes1D/AnalyticalSolution1D/AnalyticalDiffusion1D.cpp \
       Classes1D/Boundaries/Boundary.cpp \
       Classes1D/BoundaryConditions/BoundaryConditions.cpp \
       Classes1D/Convergence/RelativeResidual.cpp \
       Classes1D/ExplicitSolvers1D/ExplicitSolvers1D.cpp \
       Classes1D/Field1D/Field1D.cpp \
       Classes1D/FileWriter1D/FileWriter1D.cpp \
       Classes1D/Geometry/Geometry.cpp \
       Classes1D/InitialConditions/InitialConditions.cpp \
       Classes1D/Mesh1D/Mesh1D.cpp \
       Classes1D/Plotter/OutputPlotter.cpp \
       Classes1D/Plotter/ResidualPlotter.cpp \
       Classes1D/Printer1D/Printer1D.cpp \
       Classes1D/SolverSettings/SolutionParameters.cpp \
       Classes1D/Thermophysical_Properties/ThermophysicalProperties.cpp

all: bin/main

bin/main: $(SRCS) $(HEADERS)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -o bin/main $(SRCS)

clean:
	rm -rf bin/*
