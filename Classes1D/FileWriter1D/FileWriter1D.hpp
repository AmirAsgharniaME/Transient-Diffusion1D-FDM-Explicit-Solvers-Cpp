#pragma once
#include "Classes1D/Field1D/Field1D.hpp"
#include "Classes1D/AnalyticalSolution1D/AnalyticalDiffusion1D.hpp"
#include "EssentialHeaders/FileWriterOptions.hpp"



class FileWriter1D
{
public:
    FileWriter1D() =delete;
    
   static void WriteField1D(
    const Field1D& Field1D_Obj, 
    const Mesh1D& Mesh1D_Obj,
    const FieldType FieldType_, 
    const std::string RelativePath);


   static void WriteField1D(
    const AnalyticalDiffusion1D& Field1DAnalytical_obj,
    const Mesh1D& Mesh1D_Obj,
    const FieldType FieldType_,
    const std::string RelativePath);

};

