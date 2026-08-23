#include "Classes1D/FileWriter1D/FileWriter1D.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>


void FileWriter1D::WriteField1D(
    const Field1D& Field1D_Obj, 
    const Mesh1D& Mesh1D_Obj,
    const FieldType FieldType_, 
    const std::string RelativePath)
{
    std::string FileName;
    if (FieldType_ == FieldType::Initial_Numerical)
    {
        std::cout<<"Initialization Completed, Writing The Initial Field2D To File..."<<std::endl;
        FileName = "Initial_Numerical1D";
    }
    else if (FieldType_ == FieldType::Steady_State_Numerical)
    {
        std::cout<<"Writing The Steady State Numerical Field2D To File..."<<std::endl;
        FileName = "Steady_State_Numerical1D";
    }

    std::string FileExtension = "dat";
    std::filesystem::path dirPath(RelativePath);
    if (!std::filesystem::exists(dirPath))
    {
        std::filesystem::create_directories(dirPath);
    }

    std::filesystem::path fullFilePath = dirPath / (FileName + "." + FileExtension);

    std::ofstream file(fullFilePath);

    if (file.is_open()) 
    {
        file << std::fixed << std::setprecision(6);
        for (size_t i = 0; i < Field1D_Obj.Size(); i++)
        {
            file << std::left
                 << std::setw(20) << Mesh1D_Obj.GetYPositions(i)
                 << std::setw(20) << Field1D_Obj.GetValue(i)
                 << "\n";
        }
                             
        std::cout << FileName << "." << FileExtension << " Created Successfully At: " << fullFilePath.string() << std::endl;
        file.close();
    }
    else 
    {
        std::cout << FileName << "." << FileExtension << " Failed To Create Because The Path Folder Is WRONG." << std::endl;
    }  
}

void FileWriter1D::WriteField1D(
    const AnalyticalDiffusion1D& Field1DAnalytical_obj,
    const Mesh1D& Mesh1D_Obj,
    const FieldType FieldType_,
    const std::string RelativePath)
{
    std::string FileName ="Steady_State_Analytical1D";
    std::string FileExtension = "dat";

    std::filesystem::path dirPath(RelativePath);

    if (!std::filesystem::exists(dirPath))
    {
        std::filesystem::create_directories(dirPath);
    }

    std::filesystem::path fullFilePath = dirPath / (FileName + "." + FileExtension);

    std::ofstream file(fullFilePath);

    if (file.is_open()) 
    {
        file << std::fixed << std::setprecision(6);
        for (size_t i = 0; i < Field1DAnalytical_obj.Size(); i++)
        {
            file << std::left
                 << std::setw(20) << Mesh1D_Obj.GetYPositions(i)
                 << std::setw(20) << Field1DAnalytical_obj.GetValue(i)
                 << "\n";
        }
                             
        std::cout << FileName << "." << FileExtension << " Created Successfully At: " << fullFilePath.string() << std::endl;
        file.close();
    }
    else 
    {
        std::cout << FileName << "." << FileExtension << " Failed To Create Because The Path Folder Is WRONG." << std::endl;
    }
}


