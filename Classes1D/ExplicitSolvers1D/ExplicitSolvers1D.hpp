#pragma once

#include <cstddef>
#include <iostream>
#include "Classes1D/Field1D/Field1D.hpp"
#include "Classes1D/Thermophysical_Properties/ThermophysicalProperties.hpp"
#include "Classes1D/SolverSettings/SolutionParameters.hpp"
#include "Classes1D/Mesh1D/Mesh1D.hpp"

struct StabilityParams 
{
    const SolutionParameters<double>* My_dt_Obj;
    const SolutionParameters<double>* My_DiffNumber_Obj;
    SolutionParameters<double>* Stable_dt_Obj;
    SolutionParameters<double>* Stable_DiffNumber_Obj;
};

class ExplicitSolvers1D
{
public:
    ExplicitSolvers1D() =delete;

    //FTCS
    static void Parameters_Stabilization
   (StabilityParams& Params,
    const Mesh1D& Mesh1D_Obj,
    const ThermophysicalProperties& nu_Obj);
    
   static void Solve_nPlus1
   (const Field1D& Field1D_n_Obj,
    Field1D& Field1D_nPlus1_Obj, 
    double Stable_Diffusion_Number_);

   //DUFORT_FRANKEL
   static void Solve_nPlus1
   (Field1D& Field1D_n_Obj,
    Field1D& Field1D_nminus1_Obj,
    Field1D& Field1D_nplus1_Obj,
    std::vector<double> CoeffsVector_);

   static std::vector<double> ReturnDuFortFrankelCoeffs(const SolutionParameters<double>& My_Diff_Number);





};
