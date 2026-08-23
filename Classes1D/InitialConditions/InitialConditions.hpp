#ifndef InitialConditions_HPP
#define InitialConditions_HPP
#include "Boundaries/Boundary.hpp"

#include "Field1D/Field1D.hpp"

class InitialConditions
{
public:
    static void ApplyInitialCondition(
    Field1D& Field1D_Obj,
    const double InitialValue_);

};

#endif