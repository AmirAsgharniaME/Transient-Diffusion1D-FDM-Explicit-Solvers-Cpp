#ifndef Printer1D_HPP
#define Printer1D_HPP

#include <iostream>
#include <cstddef>
#include "Mesh1D/Mesh1D.hpp"
#include "Field1D/Field1D.hpp"
#include "SolverSettings/SolutionParameters.hpp"

class Printer1D
{
public:
    Printer1D() =delete;


   
   static void PrintMesh1D(const Mesh1D& Mesh1D_Obj);
   static void PrintField1D(const Field1D& Field1D_Obj);
   static void Print_Mesh1D_Field1D(const Mesh1D& Mesh1D_Obj,const Field1D& Field1D_Obj);
   static void PrintStepStatus(std::size_t Step,double Residual,SolutionParameters<double>& dt_Obj);
   static void PrintConvergenceStatus(std::size_t Step,double Residual,SolutionParameters<double>& dt_Obj);
   
   

};

#endif // Printer1D_HPP