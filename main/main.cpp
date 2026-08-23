/*===========
C++ Libraries
=============*/ 
#include <iostream>
#include <vector>
#include <cmath> 
#include <iomanip>
#include <thread> // Added for optional small delays


/*=====
Headers
========*/ 

//Stops The Loop Solver Iterations by Pressing ESC
#include "EssentialHeaders/KeyboardHandler.hpp"

//Inputs
#include "EssentialHeaders/SolverInputs.hpp"

//SolverOptions
#include "EssentialHeaders/SolverOptions.hpp"


/*=====
Classes
========*/

//Geometry
#include "Classes1D/Geometry/Geometry.hpp"

//Thermophysical_Properties
#include "Classes1D/Thermophysical_Properties/ThermophysicalProperties.hpp"

//SolverSettings
#include "Classes1D/SolverSettings/SolutionParameters.hpp"

//Mesh
#include "Classes1D/Mesh1D/Mesh1D.hpp"

//Field
#include "Classes1D/Field1D/Field1D.hpp"
//InitialConditions
#include "Classes1D/InitialConditions/InitialConditions.hpp"

//Boundaries
#include "Classes1D/Boundaries/Boundary.hpp"

//BoundaryConditions
#include "Classes1D/BoundaryConditions/BoundaryConditions.hpp"

//Convergence
#include "Classes1D/Convergence/RelativeResidual.hpp"

//AnalyticalSolution
#include "Classes1D/AnalyticalSolution1D/AnalyticalDiffusion1D.hpp"

//Solvers
#include "Classes1D/ExplicitSolvers1D/ExplicitSolvers1D.hpp"

//FileWriter1D
#include "Classes1D/FileWriter1D/FileWriter1D.hpp"

//Plotter
#include "Classes1D/Plotter/ResidualPlotter.hpp"
#include "Classes1D/Plotter/OutputPlotter1D.hpp"

//Printer
#include "Classes1D/Printer/StatusPrinter.hpp"



//constexpr SolverScheme ActiveScheme = SolverScheme::FTCS;
constexpr SolverScheme ActiveScheme = SolverScheme::DUFORT_FRANKEL;

int main() 
{

// =========================================================================
// Setup (Geometry, Properties, Mesh, Conditions)
// =========================================================================

//=======
//Geometry
//========= 
Geometry Height;
Height.SetValue(SolverInputs::Height_Value);


//======================
//ThermophysicalProperties
//========================
ThermophysicalProperties nu;
nu.SetValue(SolverInputs::nu_Value);


//============
//Solver Settings
//===============
SolutionParameters<std::size_t> NumTimeLevels;
SolutionParameters<double> My_dt;
SolutionParameters<double> Stable_dt;

SolutionParameters<double> My_DiffNumber;
SolutionParameters<double> Stable_DiffNumber;

SolutionParameters<double> Tolerance;


NumTimeLevels.SetValue(SolverInputs::NumTimeStep_Value);
My_dt.SetValue(SolverInputs::dt_Value);
Stable_dt.SetValue(My_dt.GetValue());


Tolerance.SetValue(SolverInputs::Tolerance_Value);

//====
//Mesh1D
//======
Mesh1D mesh1D(Height);
mesh1D.SetNumOfNodes(SolverInputs::NumOfNodes_Value);


//=================
//Diffusion Nymber
//=================
My_DiffNumber.SetValue((nu.GetValue() * My_dt.GetValue())/(mesh1D.GetdeltaY()*mesh1D.GetdeltaY()));
Stable_DiffNumber.SetValue(My_DiffNumber.GetValue());
//========
//Field1D
//========
Field1D U_0(mesh1D);
Field1D U_1(mesh1D);
Field1D U_n(mesh1D);
Field1D U_nPlus1(mesh1D);
Field1D U_nMinus1(mesh1D); //using For DUFORT_FRANKEL


//=====================================
//Apply Initial Conditions To Field1D U_0
//======================================
InitialConditions::ApplyInitialCondition(U_0, SolverInputs::Uniform_Initial_Velocity);


//====================
//Boundaries For Field1D
//======================
Boundary TopWall;
Boundary BottomWall;

//Boundary Setters
TopWall.SetValue(SolverInputs::TopWall_Velocity_Values);
BottomWall.SetValue(SolverInputs::BottomWall_Velocity_Values);



//=======================================
//Apply Boundary Conditions To Field1D U_0
//=========================================
BoundaryConditions::ApplyBoundaryCondition(U_0, TopWall, BoundaryLocation::Top);
BoundaryConditions::ApplyBoundaryCondition(U_0, BottomWall, BoundaryLocation::Bottom);


AnalyticalDiffusion1D U_Analytical_1D(mesh1D, Height, TopWall, BottomWall);

std::string_view SchemeName = To_String(SolverScheme::FTCS);
std::string FilePath = "OutPutData/" + std::string(SchemeName);

FileWriter1D::WriteField1D(U_0, mesh1D, FieldType::Initial_Numerical, FilePath);
FileWriter1D::WriteField1D(U_Analytical_1D, mesh1D, FieldType::Steady_State_Analytical, FilePath);

//static_cast<std::size_t>

ResidualPlotter plotter("CFD Convergence: Diffusion 1D (" + std::string(SchemeName) + ")");
std::vector<double> stepHistory;
std::vector<double> residualHistory;

// ============
// Stability
// ============
StabilityParams stabilityParams = {
    &My_dt,
    &My_DiffNumber,
    &Stable_dt,
    &Stable_DiffNumber
};

if (ActiveScheme == SolverScheme::FTCS)
{
    if (My_DiffNumber.GetValue() < 0.5)
        {
          Stable_DiffNumber.SetValue(My_DiffNumber.GetValue());
          std::cout<<"FTCS Scheme is stable"<<'\n';
        }
    else if (My_DiffNumber.GetValue() >= 0.5)
        {
          ExplicitSolvers1D::Parameters_Stabilization(stabilityParams,mesh1D,nu);
        }
}
else if (ActiveScheme == SolverScheme::DUFORT_FRANKEL)
{
  std::cout<<" DUFORT_FRANKEL Scheme is unconditionally stable"<<'\n';
}

//=======
//StartUp
//=======
if (ActiveScheme == SolverScheme::FTCS)
{
U_n.Swap(U_0);
}
else if (ActiveScheme == SolverScheme::DUFORT_FRANKEL)
{
//=========================================
//FTCS is a StartUp for DuFortFrankel Method
//U_0----->Explicit FTCS------> U_1
//===========================================

  if (My_DiffNumber.GetValue() < 0.5)
      {
        Stable_DiffNumber.SetValue(My_DiffNumber.GetValue());
        //U_n = U_0  And  U_nPlus1 = U_1
        ExplicitSolvers1D::Solve_nPlus1(U_0,U_1,Stable_DiffNumber.GetValue());
        
        //Apply Boundary Conditions To New Field
        BoundaryConditions::ApplyBoundaryCondition(U_1,TopWall,BoundaryLocation::Top);
        BoundaryConditions::ApplyBoundaryCondition(U_1,BottomWall,BoundaryLocation::Bottom);
      //Swap : U_n-1 <------- U_0 And U_n <-------  U_1
        U_nMinus1.Swap(U_0);
        U_n.Swap(U_1);

      }// End of if(My_diffNumber.GetValue() < 0.5)

      if (My_DiffNumber.GetValue() >= 0.5)
      {
         ExplicitSolvers1D::Parameters_Stabilization(stabilityParams,mesh1D,nu);
        std::size_t n = static_cast<std::size_t>(std::llround(My_dt.GetValue()/ Stable_dt.GetValue()));

        U_nMinus1 = U_0; //Saving U_n-1 = U_0

        // U_0 ----> U_1 with Lower_dt and Lower_DiffNumber
        for (size_t i = 1; i <= n; i++)
        {


        ExplicitSolvers1D::Solve_nPlus1(U_0 , U_1 , Stable_DiffNumber.GetValue());

        BoundaryConditions::ApplyBoundaryCondition(U_1 ,TopWall,BoundaryLocation::Top);
        BoundaryConditions::ApplyBoundaryCondition(U_1 ,BottomWall,BoundaryLocation::Bottom);


        if (i==n)
        {
        //U_nPlus1 = U_1
        U_n.Swap(U_1);
        Stable_dt.SetValue(My_dt.GetValue());
        Stable_DiffNumber.SetValue(My_DiffNumber.GetValue());
        break;
        }

        U_0.Swap(U_1);
        }// end Of Loop
      }//End Of if (DiffusionNumber >= 0.5)
}


// ======================================
// Coffes of Discrete Algebraic Equation
// ======================================
std::vector<double> Coeffs;
if (ActiveScheme == SolverScheme::FTCS)
{}
else if (ActiveScheme == SolverScheme::DUFORT_FRANKEL)
{
  Coeffs = ExplicitSolvers1D::ReturnDuFortFrankelCoeffs(My_DiffNumber);
}


// ==========================
// Solver Loop 
// ===========================
std::size_t TimeLevel_start;
std::size_t TimeLevel_n;
std::size_t TimeLevel_Total = NumTimeLevels.GetValue();
// Initial TimeLevel
if (ActiveScheme == SolverScheme::FTCS)
{
  TimeLevel_start =1;
}
else if (ActiveScheme == SolverScheme::DUFORT_FRANKEL)
{
  TimeLevel_start = 2;
}
TimeLevel_n = TimeLevel_start;

for (; TimeLevel_n < TimeLevel_Total; TimeLevel_n++)

{

//This Condition Stops The Loop Solver Iterations by Pressing ESC
if (isEscPressed())
{
    std::cout << "\nESC pressed. Exiting program now..." << std::endl;
    return 0;
}


if (ActiveScheme == SolverScheme::FTCS)
{
ExplicitSolvers1D::Solve_nPlus1(U_n, U_nPlus1 , Stable_DiffNumber.GetValue());
}
else if (ActiveScheme == SolverScheme::DUFORT_FRANKEL)
{
  ExplicitSolvers1D::Solve_nPlus1(U_n,U_nMinus1,U_nPlus1,Coeffs);
}


//ExplicitSolver For FTCS

//Apply Boundary Conditions To New Field
BoundaryConditions::ApplyBoundaryCondition(U_nPlus1,TopWall,BoundaryLocation::Top);
BoundaryConditions::ApplyBoundaryCondition(U_nPlus1,BottomWall,BoundaryLocation::Bottom);


//Claculate The Relative Residual
double Residual = RelativeResidual::ReturnResidual(U_n,U_nPlus1);

if (ActiveScheme == SolverScheme::FTCS)
{
  StatusPrinter::PrintStepStatus(TimeLevel_n,Residual,Stable_dt);
}
else if (ActiveScheme == SolverScheme::DUFORT_FRANKEL)
{
  StatusPrinter::PrintStepStatus(TimeLevel_n,Residual,My_dt);
}


//Updade
//U <--- Unew : U=Unew Copy The Values But Swap does not Copy
if (ActiveScheme == SolverScheme::FTCS)
{
  U_n.Swap(U_nPlus1);
}
else if (ActiveScheme == SolverScheme::DUFORT_FRANKEL)
{
U_nMinus1.Swap(U_n);
U_n.Swap(U_nPlus1);
}



// Record data for plotting
stepHistory.push_back(static_cast<double>(TimeLevel_n));
residualHistory.push_back(Residual);

// Update plot every 20 steps
if (TimeLevel_n % 20 == 0) 
{
    plotter.updatePlot(stepHistory, residualHistory);
}


//Codition For Convergence To stady state Solution
if(Residual < Tolerance.GetValue())
{

if (ActiveScheme == SolverScheme::FTCS)
{
StatusPrinter::PrintConvergenceStatus(TimeLevel_n,Residual,Stable_dt);
}
else if (ActiveScheme == SolverScheme::DUFORT_FRANKEL)
{
StatusPrinter::PrintConvergenceStatus(TimeLevel_n,Residual,My_dt);
}
FileWriter1D::WriteField1D(U_n,mesh1D,FieldType::Steady_State_Numerical,FilePath);
      
break;
}

}//End Of Loop Solver


// =========================================================================
// 3. Common Post-Processing
// =========================================================================
OutputPlotter1D outputPlotter("Solution Comparison (" + std::string(SchemeName) + ")");
outputPlotter.plotComparison(
    FilePath + "/Initial_Numerical1D.dat", "Initial Condition",
    FilePath + "/Steady_State_Numerical1D.dat", "Steady State Numerical Solution",
    FilePath + "/Steady_State_Analytical1D.dat", "Steady State Analytical Solution"
);

    std::cout << "Calculations Completed Successfully for " << std::string(SchemeName) << std::endl;
    std::cin.get();
    return 0;
}
