#include "SolverSettings/SolutionParameters.hpp"
#include <stdexcept>

template <typename T>
SolutionParameters<T>::SolutionParameters(T DefaultParameterValue_)
    : ParameterValue(DefaultParameterValue_)
{
    // All parameter values must be strictly positive.
    if (DefaultParameterValue_ <= T{0})
    {
        throw std::invalid_argument(
            "The Parameter Value must be positive."
        );
    }
}

template <typename T>
void SolutionParameters<T>::SetValue(T ParameterValue_)
{
    // Reject zero and negative values.
    if (ParameterValue_ <= T{0})
    {
        throw std::invalid_argument(
            "The Parameter Value must be positive."
        );
    }

    ParameterValue = ParameterValue_;
}

template <typename T>
T SolutionParameters<T>::GetValue() const
{
    return ParameterValue;
}

// Explicitly generate the class implementation for double.
template class SolutionParameters<double>;

// Explicitly generate the class implementation for std::size_t.
template class SolutionParameters<std::size_t>;
