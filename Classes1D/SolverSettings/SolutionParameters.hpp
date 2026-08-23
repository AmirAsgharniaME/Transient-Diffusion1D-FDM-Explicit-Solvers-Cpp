#ifndef SolutionParameters_HPP
#define SolutionParameters_HPP

#include <cstddef>
#include <type_traits>

// T is the data type stored by this parameter object.
template <typename T>
class SolutionParameters
{
    // Restrict supported types to double and std::size_t.
    static_assert(
        std::is_same_v<T, double> || std::is_same_v<T, std::size_t>,
        "SolutionParameters only supports double and std::size_t."
    );

private:
    T ParameterValue;

public:
    // T{1} creates the default value 1 with the correct type.
    explicit SolutionParameters(T DefaultParameterValue_ = T{1});

    void SetValue(T ParameterValue_);

    // The return type is exactly the template type T.
    T GetValue() const;
};

#endif // SolutionParameters_HPP
