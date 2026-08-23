#pragma once

#include <vector>


class Boundary
{
public:
    explicit Boundary(double Default_Initial_BoundaryValue_ = 0.0);


    double GetValue() const;
    void SetValue(const double BoundaryValue_);




private:
    double BoundaryValue;
    
};

