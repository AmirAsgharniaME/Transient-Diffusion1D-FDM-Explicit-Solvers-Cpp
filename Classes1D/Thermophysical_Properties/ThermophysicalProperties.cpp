#include "Thermophysical_Properties/ThermophysicalProperties.hpp"
#include <stdexcept>

ThermophysicalProperties::ThermophysicalProperties(double DefaultValue_)
:PropertyValue(DefaultValue_)
{}

double ThermophysicalProperties::GetValue() const 
{return PropertyValue;}

void ThermophysicalProperties::SetValue(double MyValue_)
{ 
    if (MyValue_ <= 0)
    {
    throw std::invalid_argument("The Value Of Property must be greater than zero.");
    }
    else
    {
        PropertyValue = MyValue_;
    }

}