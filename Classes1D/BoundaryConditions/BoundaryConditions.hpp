#ifndef BoundaryConditions_HPP
#define BoundaryConditions_HPP

#include "Boundaries/Boundary.hpp"
#include "Field1D/Field1D.hpp"
#include "Mesh1D/Mesh1D.hpp"

class BoundaryConditions
{
public:

    static void ApplyBoundaryCondition(Field1D& Field1D_Obj,const Mesh1D& Mesh1D_Obj,const Boundary& TopBoundary_Obj);

};
#endif //BoundaryConditions_HPP