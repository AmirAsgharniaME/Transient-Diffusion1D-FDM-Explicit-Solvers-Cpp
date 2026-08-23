# ==============================================================================
# Compiler Configuration
# ==============================================================================
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I.
# Output binary target
TARGET = bin/main


# ==============================================================================
# Project Structure Breakdown
# ==============================================================================

# 1. Essential Headers:
#    Contains standalone, header-only declarations and utilities (.hpp only)
ESSENTIAL_HEADERS = $(wildcard EssentialHeaders/*.hpp)


# 2. 1D Simulation Classes:
#    Modular object-oriented components. Each class consists of:
#    - Declaration / Interface : (.hpp)
#    - Implementation / Source : (.cpp)

# Class Headers (.hpp)
CLASS_HEADERS = \
    Classes1D/AnalyticalSolution1D/AnalyticalDiffusion1D.hpp \
    Classes1D/Boundaries/Boundary.hpp \
    Classes1D/BoundaryConditions/BoundaryConditions.hpp \
    Classes1D/Convergence/RelativeResidual.hpp \
    Classes1D/ExplicitSolvers1D/ExplicitSolvers1D.hpp \
    Classes1D/Field1D/Field1D.hpp \
    Classes1D/FileWriter1D/FileWriter1D.hpp \
    Classes1D/Geometry/Geometry.hpp \
    Classes1D/InitialConditions/InitialConditions.hpp \
    Classes1D/Mesh1D/Mesh1D.hpp \
    Classes1D/Plotter/OutputPlotter1D.hpp \
    Classes1D/Plotter/ResidualPlotter.hpp \
    Classes1D/Printer/StatusPrinter.hpp \
    Classes1D/SolverSettings/SolutionParameters.hpp \
    Classes1D/Thermophysical_Properties/ThermophysicalProperties.hpp

# Class Implementations (.cpp)
CLASS_SRCS = \
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
    Classes1D/Plotter/OutputPlotter1D.cpp \
    Classes1D/Plotter/ResidualPlotter.cpp \
    Classes1D/Printer/StatusPrinter.cpp \
    Classes1D/SolverSettings/SolutionParameters.cpp \
    Classes1D/Thermophysical_Properties/ThermophysicalProperties.cpp


# 3. Application Entry Point:
#    The driver routine that links all classes and headers together
MAIN_SRC = main/main.cpp


# ==============================================================================
# Aggregated Dependencies
# ==============================================================================
ALL_SRCS    = $(MAIN_SRC) $(CLASS_SRCS)
ALL_HEADERS = $(ESSENTIAL_HEADERS) $(CLASS_HEADERS)


# ==============================================================================
# Build Rules
# ==============================================================================
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(ALL_SRCS) $(ALL_HEADERS)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(ALL_SRCS)

clean:
	rm -rf bin/*

