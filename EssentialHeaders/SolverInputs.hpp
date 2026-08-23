#ifndef SolverInputs_HPP
#define SolverInputs_HPP
#include <vector>
#include <cstddef>

namespace SolverInputs
{   /*******************Geometry Inputs*****************************/
    inline constexpr double Height_Value = 0.04; //[m]

    /*****************Thermophysical_Properties Inputs************************/
    inline constexpr double nu_Value = 0.000217;

    /****************Solver Settings Inputs**************************/
    inline constexpr std::size_t NumTimeStep_Value = 10000;
    inline constexpr double dt_Value = 0.001;
    inline constexpr double Tolerance_Value = 1e-6;
    /**********************Mesh*****************************/
    inline constexpr std::size_t NumOfNodes_Value =40;

   /***********Initial Condition Values****************/
   inline const double Uniform_Initial_Velocity = 0.0;

   /***************Boundary Codition Values*****************/

   inline const double TopWall_Velocity_Values = 0.0;
   inline const double BottomWall_Velocity_Values = 40.0;

}

#endif // SolverInputs_HPP
