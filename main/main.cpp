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


/*=====
Classes
========*/

//Geometry
#include "Geometry/Geometry.hpp"

//Thermophysical_Properties
#include "Thermophysical_Properties/ThermophysicalProperties.hpp"

//SolverSettings
#include "SolverSettings/SolutionParameters.hpp"

//Mesh
#include "Mesh1D/Mesh1D.hpp"

//Field
#include "Field1D/Field1D.hpp"
//InitialConditions
#include "InitialConditions/InitialConditions.hpp"

//Boundaries
#include "Boundaries/Boundary.hpp"

//BoundaryConditions
#include "BoundaryConditions/BoundaryConditions.hpp"

//Convergence
#include "Convergence/RelativeResidual.hpp"

//AnalyticalSolution
#include "AnalyticalSolution1D/AnalyticalDiffusion1D.hpp"

//Solvers
#include "ExplicitSolvers1D/ExplicitSolvers1D.hpp"

//FileWriter1D
#include "FileWriter1D/FileWriter1D.hpp"

//Plotter
#include "Plotter/ResidualPlotter.hpp"
#include "Plotter/OutputPlotter.hpp"

//Printer
#include "Printer1D/Printer1D.hpp"

// =============================================================================
// Solver Selection: Choose scheme directly here in the editor
// =============================================================================
enum class SolverScheme 
{
    FTCS,
    DUFORT_FRANKEL
};

constexpr SolverScheme ActiveScheme = SolverScheme::FTCS;
//constexpr SolverScheme ActiveScheme = SolverScheme::DUFORT_FRANKEL;

int main() 
{
const std::string schemeName = (ActiveScheme == SolverScheme::FTCS) 
                                  ? "FTCSMethod" 
                                  : "DuFortFrankelMethod";

std::cout << "Selected Scheme: " << schemeName << std::endl;

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
SolutionParameters<double> my_dt;
SolutionParameters<double> Stable_dt;

SolutionParameters<double> My_DiffNumber;
SolutionParameters<double> Stable_DiffNumber;

SolutionParameters<double> Tolerance;


NumTimeLevels.SetValue(SolverInputs::NumTimeStep_Value);
my_dt.SetValue(SolverInputs::dt_Value);
Stable_dt.SetValue(my_dt.GetValue());


Tolerance.SetValue(SolverInputs::Tolerance_Value);

//====
//Mesh1D
//======
Mesh1D mesh1D(Height);
mesh1D.SetNumOfNodes(SolverInputs::NumOfNodes_Value);

//=================
//Diffusion Nymber
//=================
My_DiffNumber.SetValue((nu.GetValue() * my_dt.GetValue())/(mesh1D.GetdeltaY()*mesh1D.GetdeltaY()));
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
TopWall.SetPosition(Height.GetValue());
BottomWall.SetValue(SolverInputs::BottomWall_Velocity_Values);
BottomWall.SetPosition(0.0);


//=======================================
//Apply Boundary Conditions To Field1D U_0
//=========================================
BoundaryConditions::ApplyBoundaryCondition(U_0, mesh1D, TopWall);
BoundaryConditions::ApplyBoundaryCondition(U_0, mesh1D, BottomWall);

AnalyticalDiffusion1D U_Analytical_1D(mesh1D, Height, TopWall, BottomWall);

std::string FilePath = "OutPutData/" + schemeName;
FileWriter1D::WriteField1D(U_0, mesh1D, "U0_1D", FilePath);
FileWriter1D::WriteField1D(U_Analytical_1D, mesh1D, "U_Analytical_1D", FilePath);


ResidualPlotter plotter("CFD Convergence: Diffusion 1D (" + schemeName + ")");
std::vector<double> stepHistory;
std::vector<double> residualHistory;

// ============
// Stability
// ============

if (ActiveScheme == SolverScheme::FTCS)
{
    if (My_DiffNumber.GetValue() < 0.5)
        {
          Stable_DiffNumber.SetValue(My_DiffNumber.GetValue());
          std::cout<<"FTCS Scheme is stable"<<'\n';
        }
    else if (My_DiffNumber.GetValue() >= 0.5)
        {
          ExplicitSolvers1D::Reset_Stability_Params(Stable_dt,Stable_DiffNumber,mesh1D,nu);
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
        ExplicitSolvers1D::Solve_Diffusion1D(U_0,U_1,Stable_DiffNumber.GetValue());
        
        //Apply Boundary Conditions To New Field
        BoundaryConditions::ApplyBoundaryCondition(U_1,mesh1D,TopWall);
        BoundaryConditions::ApplyBoundaryCondition(U_1,mesh1D,BottomWall);
      //Swap : U_n-1 <------- U_0 And U_n <-------  U_1
        U_nMinus1.Swap(U_0);
        U_n.Swap(U_1);

      }// End of if(My_diffNumber.GetValue() < 0.5)

      if (My_DiffNumber.GetValue() >= 0.5)
      {
        SolutionParameters<double> Temp_Stable_dt;
        SolutionParameters<double> Temp_Stable_DiffNumber;
        Temp_Stable_dt.SetValue(my_dt.GetValue());
        Temp_Stable_DiffNumber.SetValue(My_DiffNumber.GetValue());

        ExplicitSolvers1D::Reset_Stability_Params(Temp_Stable_dt,Temp_Stable_DiffNumber,mesh1D,nu);
        std::size_t n = static_cast<std::size_t>(std::llround(my_dt.GetValue()/ Temp_Stable_dt.GetValue()));

        U_nMinus1 = U_0; //Saving U_n-1 = U_0

        // U_0 ----> U_1 with Lower_dt and Lower_DiffNumber
        for (size_t i = 1; i <= n; i++)
        {


        ExplicitSolvers1D::Solve_Diffusion1D(U_0 , U_1 , Temp_Stable_DiffNumber.GetValue());

        BoundaryConditions::ApplyBoundaryCondition(U_1 ,mesh1D,TopWall);
        BoundaryConditions::ApplyBoundaryCondition(U_1 ,mesh1D,BottomWall);

        if (i==n)
        {
        //U_nPlus1 = U_1
        U_n.Swap(U_1);
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
  Coeffs = ExplicitSolvers1D::ReturnCoeffs(My_DiffNumber);
}



// ==========================
// Solver Loop 
// ===========================
std::size_t TimeLevel;

// Initial TimeLevel
if (ActiveScheme == SolverScheme::FTCS)
{
  TimeLevel =1;
}
else if (ActiveScheme == SolverScheme::DUFORT_FRANKEL)
{
  TimeLevel = 2;
}

for (; TimeLevel < NumTimeLevels.GetValue(); TimeLevel++)

{

//***This Condition Stops The Loop Solver Iterations by Pressing ESC***//
if (isEscPressed())
{
    std::cout << "\nESC pressed. Exiting program now..." << std::endl;
    return 0;
}


if (ActiveScheme == SolverScheme::FTCS)
{
ExplicitSolvers1D::Solve_Diffusion1D(U_n, U_nPlus1 , Stable_DiffNumber.GetValue());
}
else if (ActiveScheme == SolverScheme::DUFORT_FRANKEL)
{
  ExplicitSolvers1D::Solve_Diffusion1D(U_n,U_nMinus1,U_nPlus1,Coeffs);
}


//ExplicitSolver For FTCS

//Apply Boundary Conditions To New Field
BoundaryConditions::ApplyBoundaryCondition(U_nPlus1,mesh1D,TopWall);
BoundaryConditions::ApplyBoundaryCondition(U_nPlus1,mesh1D,BottomWall);

//Claculate The Relative Residual
double Residual = RelativeResidual::ReturnResidual(U_n,U_nPlus1);

if (ActiveScheme == SolverScheme::FTCS)
{
  Printer1D::PrintStepStatus(TimeLevel,Residual,Stable_dt);
}
else if (ActiveScheme == SolverScheme::DUFORT_FRANKEL)
{
  Printer1D::PrintStepStatus(TimeLevel,Residual,my_dt);
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
stepHistory.push_back(static_cast<double>(TimeLevel));
residualHistory.push_back(Residual);

// Update plot every 20 steps
if (TimeLevel % 20 == 0) 
{
    plotter.updatePlot(stepHistory, residualHistory);
}


//Codition For Convergence To stady state Solution
if(Residual < Tolerance.GetValue())
{

if (ActiveScheme == SolverScheme::FTCS)
{
Printer1D::PrintConvergenceStatus(TimeLevel,Residual,Stable_dt);
}
else if (ActiveScheme == SolverScheme::DUFORT_FRANKEL)
{
Printer1D::PrintConvergenceStatus(TimeLevel,Residual,my_dt);
}

FileWriter1D::WriteField1D(U_n,mesh1D,"Steady_State_U_1D",FilePath);          
break;
}

}/***************End Of Loop Solver*************/


// =========================================================================
// 3. Common Post-Processing
// =========================================================================
OutputPlotter outputPlotter("Solution Comparison (" + schemeName + ")");
outputPlotter.plotComparison(
    FilePath + "/U0_1D.dat", "Initial Condition",
    FilePath + "/Steady_State_U_1D.dat", "Steady State Numerical Solution",
    FilePath + "/U_Analytical_1D.dat", "Steady State Analytical Solution"
);

    std::cout << "Calculations Completed Successfully for " << schemeName << std::endl;
    return 0;
}
