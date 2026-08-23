#ifndef FILEWRITER_HPP
#define FILEWRITER_HPP
#include "Field1D/Field1D.hpp"
#include "AnalyticalSolution1D/AnalyticalDiffusion1D.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <iomanip>

#include <vector>
#include <string>





class FileWriter1D
{
public:
    FileWriter1D() =delete;
    
   static void WriteField1D(Field1D& Field1D_Obj,  Mesh1D& Mesh1D_Obj ,std::string FileName, std::string Path);
   static void WriteField1D(AnalyticalDiffusion1D& Field1DAnalytical_obj,Mesh1D& Mesh1D_Obj,std::string FileName ,std::string Path);

};

#endif // FILEWRITER_HPP
