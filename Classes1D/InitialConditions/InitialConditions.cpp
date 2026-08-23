#include "InitialConditions/InitialConditions.hpp"

void InitialConditions::ApplyInitialCondition(Field1D& Field1D_Obj,const double InitialValue_)
{
    if (Field1D_Obj.Size() == 0)
    {
        return;
    }

    // Initially, the fluid is stationary
     Field1D_Obj.SetAllValues(InitialValue_);
}

