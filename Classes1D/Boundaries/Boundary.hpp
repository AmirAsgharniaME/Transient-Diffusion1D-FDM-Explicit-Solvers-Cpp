#ifndef Boundary_HPP
#define Boundary_HPP
#include <vector>
#include "Mesh1D/Mesh1D.hpp"

class Boundary
{
public:
    explicit Boundary(double Default_Initial_BoundaryValue_ = 0.0,double Default_Boundary_Position_ = 0.0);


    double GetValue() const;
    void SetValue(const double BoundaryValue_);
    void SetPosition(const double BoundaryPosition_);
    double GetPosition() const;




private:
    double BoundaryValue;
    double BoundaryPosition;
    
};

#endif