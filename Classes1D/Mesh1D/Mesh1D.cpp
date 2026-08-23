#include "Mesh1D/Mesh1D.hpp"

#include <cstddef>
#include <iostream>
#include <stdexcept>



Mesh1D::Mesh1D(
    const Geometry& Height_Obj,
    std::size_t NumOfNodes_
)
    :NumOfNodes(NumOfNodes_),
     NumOfIntervals(NumOfNodes - 1),
     ChannelHeight(Height_Obj.GetValue()),
     deltaY(ChannelHeight / static_cast<double>(NumOfIntervals)),
     YPositions(NumOfNodes)
{
    DiscretizeYDirection();
}

void Mesh1D::DiscretizeYDirection()
{
    for (std::size_t Index = 0; Index < YPositions.size(); ++Index)
    {
        YPositions[Index] = static_cast<double>(Index) * deltaY;
    }
}

void Mesh1D::PrintYPositions() const
{
    for (std::size_t Index = 0; Index < YPositions.size(); ++Index)
    {
        std::cout << YPositions[Index] << " ";
    }

    std::cout << '\n';
}

std::size_t Mesh1D::GetNumOfNodes() const
{
    return NumOfNodes;
}

void Mesh1D::SetNumOfNodes(std::size_t NumOfNodes_)
{
    if (NumOfNodes_ < 2)
    {
        throw std::invalid_argument("The number of mesh nodes must be at least 2.");
    }

    NumOfNodes = NumOfNodes_;
    NumOfIntervals = NumOfNodes - 1;
    deltaY = ChannelHeight / static_cast<double>(NumOfIntervals);
    YPositions.resize(NumOfNodes);
    DiscretizeYDirection();
}


std::size_t Mesh1D::GetNumOfIntervals() const
{
    return NumOfIntervals;
}

double Mesh1D::GetdeltaY() const
{
    return deltaY;
}

double Mesh1D::GetYPositions(std::size_t Index) const
{
    return YPositions.at(Index);
}

int Mesh1D::findIndex(double target_Position) const
{

        auto it = std::find(YPositions.begin(), YPositions.end(), target_Position);

        if (it == YPositions.end()) 
        {
            return -1;
        }

        return static_cast<int>(it - YPositions.begin());

}