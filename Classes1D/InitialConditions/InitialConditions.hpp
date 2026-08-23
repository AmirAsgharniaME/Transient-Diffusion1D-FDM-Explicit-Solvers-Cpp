#pragma once
#include "Classes1D/Boundaries/Boundary.hpp"

#include "Classes1D/Field1D/Field1D.hpp"

class InitialConditions
{
public:
    static void ApplyInitialCondition(
    Field1D& Field1D_Obj,
    const double InitialValue_);

};
