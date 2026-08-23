#pragma once
#include <vector>
#include "Classes1D/Mesh1D/Mesh1D.hpp"
#include "Classes1D/Boundaries/Boundary.hpp"
#include "Classes1D/Field1D/Field1D.hpp"

class AnalyticalDiffusion1D
{
public:
   explicit AnalyticalDiffusion1D(
        Mesh1D& Mesh_Obj, 
        Geometry& Height_Obj,
        Boundary& TopWall_Obj,
        Boundary& BottomWall_Obj
        );

    void ClaculateAnalyticalValues();
    std::size_t Size() const;
    double GetValue(std::size_t Index) const;
   


    private:
    std::size_t NumOfNodes;
    std::vector<double> YPositions;
    std::vector<double> AnalyticalValues;
    double H;
    double TopWallVlaue;
    double BottomWallValue;
};

