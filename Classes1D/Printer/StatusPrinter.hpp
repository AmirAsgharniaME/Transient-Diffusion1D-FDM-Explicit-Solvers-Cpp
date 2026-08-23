#pragma once

#include <iostream>
#include <cstddef>
#include "Classes1D/Mesh1D/Mesh1D.hpp"
#include "Classes1D/Field1D/Field1D.hpp"
#include "Classes1D/SolverSettings/SolutionParameters.hpp"

class StatusPrinter
{
public:
    StatusPrinter() =delete;


   static void Print_Mesh1D_Field1D(const Mesh1D& Mesh1D_Obj,const Field1D& Field1D_Obj);
   static void PrintStepStatus(std::size_t Step,double Residual,SolutionParameters<double>& dt_Obj);
   static void PrintConvergenceStatus(std::size_t Step,double Residual,SolutionParameters<double>& dt_Obj);
   
   

};
