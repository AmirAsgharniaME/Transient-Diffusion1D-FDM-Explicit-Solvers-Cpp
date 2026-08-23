#include "Classes1D/BoundaryConditions/BoundaryConditions.hpp" // class BoundaryConditions;  forward declaration

void BoundaryConditions::ApplyBoundaryCondition(
    Field1D& Field1D_Obj,
    const Boundary& Boundary_Obj,
    BoundaryLocation Location_)
{

if (Location_ == BoundaryLocation::Top)
{
    Field1D_Obj.SetSideValues(BoundaryLocation::Top,Boundary_Obj.GetValue());
}
else if (Location_ == BoundaryLocation::Bottom)
{
    Field1D_Obj.SetSideValues(BoundaryLocation::Bottom,Boundary_Obj.GetValue());
}
    
}
