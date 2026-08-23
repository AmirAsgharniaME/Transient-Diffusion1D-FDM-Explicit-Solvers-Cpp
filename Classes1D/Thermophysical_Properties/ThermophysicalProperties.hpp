#pragma once


class ThermophysicalProperties
{
private:

    double PropertyValue; 

public:
      explicit ThermophysicalProperties(double DefaultValue_ = 1.0);
      
      double GetValue() const;
      void SetValue(double MyValue_);



};
