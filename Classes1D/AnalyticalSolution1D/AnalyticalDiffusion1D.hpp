#ifndef AnalyticalDiffusion1D_HPP
#define AnalyticalDiffusion1D_HPP
#include <vector>
#include "Mesh1D/Mesh1D.hpp"
#include "Boundaries/Boundary.hpp"
#include "Field1D/Field1D.hpp"

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
    std::size_t Size();
    double GetValue(std::size_t Index);
   


    private:
    std::size_t NumOfNodes;
    std::vector<double> YPositions;
    std::vector<double> AnalyticalValues;
    double H;
    double TopWallVlaue;
    double BottomWallValue;
};

#endif //AnalyticalDiffusion1D_HPP