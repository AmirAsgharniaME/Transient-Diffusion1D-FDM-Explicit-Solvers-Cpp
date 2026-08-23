#ifndef RelativeResidual_HPP
#define RelativeResidual_HPP
#include "Field1D/Field1D.hpp"

class RelativeResidual
{
public:
    RelativeResidual() = delete;
    static double ReturnResidual(const Field1D& Field1D_Old_obj,const Field1D& Field1D_New_obj);

private:
    
};

#endif
