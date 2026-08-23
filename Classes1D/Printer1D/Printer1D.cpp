#include "Printer1D/Printer1D.hpp"
#include <iomanip>



void Printer1D::PrintMesh1D(const Mesh1D& Mesh1D_Obj) 

{
    std::size_t NumOfNodes = Mesh1D_Obj.GetNumOfNodes();

    std::cout << std::scientific << std::setprecision(3);

    std::cout << "\n"
              << std::left << std::setw(10) << "Index"
              << std::right << std::setw(20) << "YPosition"
              << '\n';

    std::cout << std::string(30, '-') << '\n';

    for (std::size_t i = 0; i < NumOfNodes; ++i) 
    {
        std::cout << std::left << std::setw(10) << i
                  << std::right << std::setw(20) << Mesh1D_Obj.GetYPositions(i)
                  << '\n';
    }
}
    

void Printer1D::PrintField1D(const Field1D& Field1D_Obj)
{

    std::size_t NumOfNodes = Field1D_Obj.Size();

    std::cout << std::scientific << std::setprecision(3);

    std::cout << "\n"
              << std::left << std::setw(10) << "Index"
              << std::right << std::setw(20) << "Field Value"
              << '\n';

    std::cout << std::string(30, '-') << '\n';

    for (std::size_t i = 0; i < NumOfNodes; ++i) 
    {
        std::cout << std::left << std::setw(10) << i
                  << std::right << std::setw(20) << Field1D_Obj.GetValue(i)
                  << '\n';
    }

}


void Printer1D::Print_Mesh1D_Field1D(const Mesh1D& Mesh1D_Obj,const Field1D& Field1D_Obj) 
{
    std::size_t NumOfNodes = Mesh1D_Obj.GetNumOfNodes();
    
    if (NumOfNodes != Field1D_Obj.Size()) 
    {
        throw std::invalid_argument(
            "The sizes of YPosition and FieldValue must be equal."
        );
    }

    std::cout << std::scientific << std::setprecision(3);

    std::cout << std::left
              << std::setw(10) << "Index"
              << std::setw(20) << "YPosition"
              << std::setw(20) << "Field Value"
              << '\n';

    std::cout << std::string(50, '-') << '\n';

    for (std::size_t i = 0; i < NumOfNodes; ++i) {
        std::cout << std::left
                  << std::setw(10) << i
                  << std::setw(20) << Mesh1D_Obj.GetYPositions(i)
                  << std::setw(20) << Field1D_Obj.GetValue(i)
                  << '\n';
    }
}

void Printer1D::PrintStepStatus(std::size_t Step ,double Residual ,SolutionParameters<double>& dt_Obj)
{

const double Time =static_cast<double>(Step) * dt_Obj.GetValue();
std::cout << "Step: " << std::setw(6) << Step
          << " | Time: " << std::fixed << std::setprecision(2)
          << std::setw(10) << Time << " s"
          << " | Relative residual: " << std::scientific
          << std::setprecision(2) << Residual
          << std::defaultfloat << '\n';
}


void Printer1D::PrintConvergenceStatus(std::size_t Step,double Residual,SolutionParameters<double>& dt_Obj)
{
const double Time =static_cast<double>(Step) * dt_Obj.GetValue();
std::cout << "\n"
          << "========================================\n"
          << "Convergence achieved\n"
          << "Step   : " << std::setw(6) << Step << '\n'
          << "Time   : " << std::fixed << std::setprecision(2)
          << std::setw(10) << Time << " s\n"
          << "Residual: " << std::scientific << std::setprecision(2) << Residual << '\n'
          << "========================================\n"
          << std::defaultfloat;


}

