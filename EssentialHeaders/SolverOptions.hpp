
#pragma once

#include <string_view>

enum class SolverScheme 
{
    FTCS,
    DUFORT_FRANKEL
};

// [[nodiscard]] : Warns the compiler if the returned string is ignored by the caller.
// constexpr     : Allows evaluation at compile-time when the input is known at compile-time.
// std::string_view : A lightweight, zero-copy, read-only view of a string literal (avoids heap allocation).
// noexcept      : Guarantees that this function will never throw an exception at runtime.
[[nodiscard]] constexpr std::string_view To_String(SolverScheme scheme) noexcept
{
    switch (scheme)
    {
        case SolverScheme::FTCS:
            return "FTCS";

        case SolverScheme::DUFORT_FRANKEL:
            return "DUFORT_FRANKEL";
    }

    return "UNKNOWN";
}





/*
inline std::string Convert_SolverScheme_To_String(SolverScheme scheme)
{
    switch (scheme)
    {
        case SolverScheme::FTCS:
            return "FTCS";

        case SolverScheme::DUFORT_FRANKEL:
            return "DUFORT_FRANKEL";
    }

    return "UNKNOWN";
}
*/
