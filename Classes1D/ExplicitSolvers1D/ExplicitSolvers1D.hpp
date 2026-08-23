#ifndef ExplicitSolvers1D_HPP
#define ExplicitSolvers1D_HPP

#include <cstddef>
#include <iostream>
#include "Field1D/Field1D.hpp"
#include "Thermophysical_Properties/ThermophysicalProperties.hpp"
#include "SolverSettings/SolutionParameters.hpp"
#include "Mesh1D/Mesh1D.hpp"
class ExplicitSolvers1D
{
public:
    ExplicitSolvers1D() =delete;
    
   static void Solve_Diffusion1D(const Field1D& Field1D_n_Obj,Field1D& Field1D_nPlus1_Obj , double Stable_Diffusion_Number_);
   static void Reset_Stability_Params(
    SolutionParameters<double>& Stable_dt_Obj,
    SolutionParameters<double>& Stable_DiffNumber_Obj,
    const Mesh1D& Mesh1D_obj,
    const ThermophysicalProperties& nu_Obj);
   
   static void Solve_Diffusion1D(Field1D& Field1D_n_Obj,Field1D& Field1D_nminus1_Obj,Field1D& Field1D_nplus1_Obj,std::vector<double> CoeffsVector_);

   static std::vector<double> ReturnCoeffs(const SolutionParameters<double>& My_Diff_Number);





};

#endif //ExplicitSolvers1D_HPP