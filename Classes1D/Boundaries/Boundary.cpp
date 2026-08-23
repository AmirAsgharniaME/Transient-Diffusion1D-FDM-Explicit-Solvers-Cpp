#include "Boundaries/Boundary.hpp"

Boundary::Boundary(double Default_Initial_BoundaryValue_,double Default_Boundary_Position_)
:BoundaryValue(Default_Initial_BoundaryValue_),
 BoundaryPosition(Default_Boundary_Position_)
{}



double Boundary::GetValue() const 
{return BoundaryValue;}

void Boundary::SetValue(const double BoundaryValue_)
{BoundaryValue = BoundaryValue_;}

void Boundary::SetPosition(const double BoundaryPosition_)
{
 BoundaryPosition = BoundaryPosition_;
}
double Boundary::GetPosition() const
{
    return BoundaryPosition;
}