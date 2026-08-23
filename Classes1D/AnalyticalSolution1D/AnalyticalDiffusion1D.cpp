#include "AnalyticalSolution1D/AnalyticalDiffusion1D.hpp"
#include <cstddef>




    AnalyticalDiffusion1D::AnalyticalDiffusion1D(Mesh1D& Mesh_Obj, Geometry& Height_Obj ,Boundary& TopWall_Obj,Boundary& BottomWall_Obj)
    :NumOfNodes(Mesh_Obj.GetNumOfNodes()),
     YPositions(NumOfNodes,0.0),
     AnalyticalValues(NumOfNodes,0.0),
     H(Height_Obj.GetValue()),
     TopWallVlaue(TopWall_Obj.GetValue()),
     BottomWallValue(BottomWall_Obj.GetValue())


    {
        for (std::size_t i = 0; i < NumOfNodes; i++)
        {
           YPositions[i] = Mesh_Obj.GetYPositions(i);
        }
        ClaculateAnalyticalValues();
    }


void AnalyticalDiffusion1D::ClaculateAnalyticalValues()
{
    for (std::size_t i = 0; i < NumOfNodes; i++)
    {
      AnalyticalValues[i]=BottomWallValue * (1.0 -  YPositions[i]/H) + TopWallVlaue *  YPositions[i]/H;

    }
    
}
std::size_t AnalyticalDiffusion1D::Size()
{
    return AnalyticalValues.size();
}

double AnalyticalDiffusion1D::GetValue(std::size_t Index)
{
 return AnalyticalValues[Index];
}

