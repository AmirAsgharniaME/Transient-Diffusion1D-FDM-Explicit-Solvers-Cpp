#include "Classes1D/Field1D/Field1D.hpp"

#include <algorithm>
#include <iomanip>
Field1D::Field1D(
    const Mesh1D& Mesh1D_Obj,
    double InitialValue_)
    :NumOfNodes(Mesh1D_Obj.GetNumOfNodes()),
    Field1D_Values(NumOfNodes,InitialValue_)
{
}

std::size_t Field1D::Size() const
{
    return Field1D_Values.size();
}

double Field1D::GetValue(std::size_t Index_) const
{
    return Field1D_Values.at(Index_);
}

void Field1D::SetValue(
    std::size_t Index_,
    double Value_)
{
    Field1D_Values.at(Index_) = Value_;
}
 void Field1D::SetSideValues(const BoundaryLocation Location ,const double Value_)
 {
     if (Location == BoundaryLocation::Top)
     {
         Field1D_Values[NumOfNodes-1] = Value_;
     }
     else if (Location == BoundaryLocation::Bottom)
     {
        Field1D_Values[0] = Value_;
     }
 }

void Field1D::SetAllValues(double Value_)
{
    std::fill(Field1D_Values.begin(), Field1D_Values.end(), Value_);
}

void Field1D::Swap(Field1D& Other) noexcept
{
    Field1D_Values.swap(Other.Field1D_Values);
}

void swap(Field1D& Left, Field1D& Right) noexcept
{
    Left.Swap(Right);
}

 void Field1D::Print() const
 {
       

    std::cout << std::scientific << std::setprecision(3);

    std::cout << "\n"
              << std::left << std::setw(10) << "Index"
              << std::right << std::setw(20) << "Field Value"
              << '\n';

    std::cout << std::string(30, '-') << '\n';

    for (std::size_t i = 0; i < NumOfNodes; ++i) 
    {
        std::cout << std::left << std::setw(10) << i
                  << std::right << std::setw(20) << Field1D_Values[i]
                  << '\n';
    }
 }