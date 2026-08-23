#pragma once

#include <cstddef>
#include <vector>
#include "Classes1D/Mesh1D/Mesh1D.hpp"
#include "EssentialHeaders/BoundaryOptions.hpp"

class Field1D
{
public:
    explicit Field1D(
        const Mesh1D& Mesh1D_Obj,
        double InitialValue_ = 0.0);

    std::size_t Size() const;

    double GetValue(std::size_t Index_) const;
    void SetValue(std::size_t Index_, double Value_);

    void SetSideValues(const BoundaryLocation Location ,const double Value_);

    void SetAllValues(double Value_);

    void Swap(Field1D& Other) noexcept;
    void Print() const;

private:
        std::size_t NumOfNodes;
        std::vector<double> Field1D_Values;

};

    
    

void swap(Field1D& Left, Field1D& Right) noexcept;

