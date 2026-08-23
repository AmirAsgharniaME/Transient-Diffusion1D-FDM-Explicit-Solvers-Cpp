#include "Geometry/Geometry.hpp"
#include <stdexcept>


Geometry::Geometry(double DefaultValue_)
:Value(DefaultValue_)
{}

double Geometry::GetValue() const 
{return Value;}


void Geometry::SetValue(double MyValue_)
{ 

    if (MyValue_<= 0.0)
    {
    throw std::invalid_argument("Height must be greater than zero.");
    }
    else
    {
       Value = MyValue_;
    }
    
}
