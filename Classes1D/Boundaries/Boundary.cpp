#include "Classes1D/Boundaries/Boundary.hpp"

Boundary::Boundary(double Default_Initial_BoundaryValue_)
:BoundaryValue(Default_Initial_BoundaryValue_)
{}



double Boundary::GetValue() const 
{return BoundaryValue;}

void Boundary::SetValue(const double BoundaryValue_)
{BoundaryValue = BoundaryValue_;}
