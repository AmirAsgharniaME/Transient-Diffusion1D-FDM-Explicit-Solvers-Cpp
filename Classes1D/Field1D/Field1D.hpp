#ifndef Field1D_HPP
#define Field1D_HPP

#include <cstddef>
#include <vector>
#include "Mesh1D/Mesh1D.hpp"

class Field1D
{
public:
    explicit Field1D(
        const Mesh1D& Mesh1D_Obj,
        double InitialValue_ = 0.0);

    std::size_t Size() const;

    double GetValue(std::size_t Index_) const;
    void SetValue(std::size_t Index_, double Value_);
    void SetTopValue(double Value_);
    void SetBottomValue(double Value_);

    void SetAllValues(double Value_);

    void Swap(Field1D& Other) noexcept;

private:
        std::size_t NumOfNodes;
        std::vector<double> Field1D_Values;

};

    
    

void swap(Field1D& Left, Field1D& Right) noexcept;

#endif
