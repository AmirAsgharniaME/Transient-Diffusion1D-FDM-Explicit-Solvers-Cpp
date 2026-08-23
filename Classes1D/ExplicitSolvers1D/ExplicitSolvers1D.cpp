#include "ExplicitSolvers1D/ExplicitSolvers1D.hpp"

 void ExplicitSolvers1D::Solve_Diffusion1D(const Field1D& Field1D_n_Obj,Field1D& Field1D_nPlus1_Obj , double Stable_Diffusion_Number_)
 {


      for (size_t i = 1; i < Field1D_n_Obj.Size() - 1 ; i++)
      {
        double RHS = Field1D_n_Obj.GetValue(i) + Stable_Diffusion_Number_ * (Field1D_n_Obj.GetValue(i + 1) - 2.0 * Field1D_n_Obj.GetValue(i) + Field1D_n_Obj.GetValue(i -1));
        Field1D_nPlus1_Obj.SetValue(i , RHS );
      }

}


   void ExplicitSolvers1D::Reset_Stability_Params(
    SolutionParameters<double>& Stable_dt_Obj,
    SolutionParameters<double>& Stable_DiffNumber_Obj,
    const Mesh1D& Mesh1D_obj,
    const ThermophysicalProperties& nu_Obj)
{


// Stable_dt_Obj and Stable_DiffNumber are initialized with my inputs
    double mydt = Stable_dt_Obj.GetValue();
    double MyDiffusinNumber = Stable_DiffNumber_Obj.GetValue();
    double deltaY = Mesh1D_obj.GetdeltaY();
    double KV = nu_Obj.GetValue();

        std::cout << "Diffusion Number limit is 0.5 and your Diffusion Number = "<< MyDiffusinNumber << '\n';
        std::cout << "FTCS is Unstable with your dt = " <<mydt<< '\n';

        double Reduction_Factor = 0.95;

        while (MyDiffusinNumber >= 0.5)
        {
        mydt= Reduction_Factor * mydt;
        MyDiffusinNumber = KV * mydt /(deltaY * deltaY);
        }

        std::cout << "dt is has been reduced for the stability of FTCS method." << '\n';
        double Lower_dt = mydt;
        Stable_dt_Obj.SetValue(Lower_dt);

        double Lower_DiffNumber = MyDiffusinNumber;
        Stable_DiffNumber_Obj.SetValue(Lower_DiffNumber);

        std::cout <<" New dt = "<<Lower_dt<<'\n';
        std::cout <<" New Diffusin Number = "<<Lower_DiffNumber<<'\n';

  }

void ExplicitSolvers1D::Solve_Diffusion1D(Field1D& Field1D_n_Obj,Field1D& Field1D_nminus1_Obj,Field1D& Field1D_nplus1_Obj,std::vector<double> CoeffsVector_)
  {

      for (size_t i = 1; i < Field1D_n_Obj.Size() - 1 ; i++)
      {
        double RHS = CoeffsVector_[0] * Field1D_nminus1_Obj.GetValue(i) + CoeffsVector_[1] * (Field1D_n_Obj.GetValue(i + 1) + Field1D_n_Obj.GetValue(i -1));
        Field1D_nplus1_Obj.SetValue(i , RHS );
      }

  }

  std::vector<double> ExplicitSolvers1D::ReturnCoeffs(const SolutionParameters<double>& My_Diff_Number_Obj)
   {
       

        double r = My_Diff_Number_Obj.GetValue();
        double C_Old = (1.0 - 2.0 * r)/(1.0 + 2.0 * r);
        double C = (2.0 * r)/(1.0 + 2.0 * r);
        


     std::vector<double> CoeffsVector = {C_Old, C};


     return CoeffsVector;

   }