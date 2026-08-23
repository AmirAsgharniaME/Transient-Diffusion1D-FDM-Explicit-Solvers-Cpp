#include "FileWriter1D/FileWriter1D.hpp"


/*
#include <filesystem>
#include <iostream>
#include <fstream>
#include <iomanip>

void FileWriter1D::WriteField1D(Field1D& Field1D_Obj, Mesh1D& Mesh1D_Obj, std::string FileName_, std::string Path)
{
    std::cout << "Initialization Completed, Writing The Initial Velocity File" << std::endl;

    std::string FileName = FileName_;
    std::string FileExtension = "dat";
    std::string FullPath = Path + "\\" + FileName + "." + FileExtension;

    // Create folder automatically if it does not exist
    std::filesystem::path folderPath(Path);
    if (!std::filesystem::exists(folderPath))
    {
        if (!std::filesystem::create_directories(folderPath))
        {
            std::cout << FileName << "." << FileExtension
                      << " Failed To Create Because The Path Folder Could Not Be Created." << std::endl;
            return;
        }
    }

    std::ofstream file(FullPath);

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

        std::cout << FileName << "." << FileExtension << " Created Successfully At: " << Path << std::endl;
        file.close();
    }
    else
    {
        std::cout << FileName << "." << FileExtension << " Failed To Create Because The File Could Not Be Opened." << std::endl;
    }
}
*/
#include "FileWriter1D/FileWriter1D.hpp"

void FileWriter1D::WriteField1D(Field1D& Field1D_Obj, Mesh1D& Mesh1D_Obj, std::string FileName_, std::string Path)
{
    std::cout << "Initialization Completed, Writing The Initial Velocity File" << std::endl;
    std::string FileName = FileName_;
    std::string FileExtension = "dat";

    std::filesystem::path dirPath(Path);
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

void FileWriter1D::WriteField1D(AnalyticalDiffusion1D& Field1DAnalytical_Obj, Mesh1D& Mesh1D_Obj, std::string FileName_, std::string Path)
{
    std::cout << "Analytical velocity values have been calculated, Writing The Analytical velocity File" << std::endl;
    std::string FileName = FileName_;
    std::string FileExtension = "dat";

    std::filesystem::path dirPath(Path);
    if (!std::filesystem::exists(dirPath))
    {
        std::filesystem::create_directories(dirPath);
    }

    std::filesystem::path fullFilePath = dirPath / (FileName + "." + FileExtension);

    std::ofstream file(fullFilePath);

    if (file.is_open()) 
    {
        file << std::fixed << std::setprecision(6);
        for (size_t i = 0; i < Field1DAnalytical_Obj.Size(); i++)
        {
            file << std::left
                 << std::setw(20) << Mesh1D_Obj.GetYPositions(i)
                 << std::setw(20) << Field1DAnalytical_Obj.GetValue(i)
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


