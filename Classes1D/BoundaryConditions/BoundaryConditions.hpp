#pragma once

#include "Classes1D/Boundaries/Boundary.hpp"
#include "Classes1D/Field1D/Field1D.hpp"
#include "EssentialHeaders/BoundaryOptions.hpp"

class BoundaryConditions
{
public:

    static void ApplyBoundaryCondition(
        Field1D& Field1D_Obj,
        const Boundary& Boundary_Obj,
        BoundaryLocation Location_);

};