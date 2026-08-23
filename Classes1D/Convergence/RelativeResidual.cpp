#include "Convergence/RelativeResidual.hpp"
#include <stdexcept>
#include <cstddef>
#include <cmath>



/*
Relative L2 Norm of the Solution Change
Relative L2 Residual Based on Successive Iteration Difference
in cfd : Relative residual or Relative residual of velocity based on solution update
ComputeRelativeL2VelocityChange
Residual =
sqrt( Σ (Unew_i - Uold_i)^2 )
/
sqrt( Σ (Unew_i)^2 )

*/

double RelativeResidual::ReturnResidual(const Field1D& Field1D_Old_obj,const Field1D& Field1D_New_obj)
{


    double numerator = 0.0;
    double denominator = 0.0;

    for (std::size_t i = 1; i < Field1D_Old_obj.Size() - 1; ++i)
    {
        const double diff = Field1D_New_obj.GetValue(i) - Field1D_Old_obj.GetValue(i);

        numerator += diff * diff;
        denominator += Field1D_New_obj.GetValue(i) * Field1D_New_obj.GetValue(i);
    }

    return std::sqrt(numerator) / (std::sqrt(denominator) + 1.0e-30);
}


