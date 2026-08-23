#pragma once


class Geometry
{
private:

    double Value;

public:
      explicit Geometry (double DefaultValue_ = 1.0); // explicit : Geometry G = 0.05; Not allowed

      //const :  Read-only: guarantees not to modify class members or call non-const functions.
      double GetValue() const;

      void SetValue(double MyValue_);



};


