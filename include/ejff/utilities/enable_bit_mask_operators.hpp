#pragma once

#include <type_traits>

template <typename Enum>
struct EnableBitMaskOperators : std::false_type
{
};

#define ENABLE_BITMASK_OPERATORS(x)                                                      \
    template <>                                                                          \
    struct EnableBitMaskOperators<x> : std::true_type                                    \
    {                                                                                    \
    }

template <typename Enum>
using EnableIfBitmask = std::enable_if_t<EnableBitMaskOperators<Enum>::value, Enum>;

template <typename Enum>
using EnableIfBitmaskRef = std::enable_if_t<EnableBitMaskOperators<Enum>::value, Enum &>;

template <typename Enum>
EnableIfBitmask<Enum> operator|(Enum lhs, Enum rhs)
{
    using T = std::underlying_type_t<Enum>;
    return static_cast<Enum>(static_cast<T>(lhs) | static_cast<T>(rhs));
}

template <typename Enum>
EnableIfBitmask<Enum> operator&(Enum lhs, Enum rhs)
{
    using T = std::underlying_type_t<Enum>;
    return static_cast<Enum>(static_cast<T>(lhs) & static_cast<T>(rhs));
}

template <typename Enum>
EnableIfBitmask<Enum> operator^(Enum lhs, Enum rhs)
{
    using T = std::underlying_type_t<Enum>;
    return static_cast<Enum>(static_cast<T>(lhs) ^ static_cast<T>(rhs));
}

template <typename Enum>
EnableIfBitmask<Enum> operator~(Enum value)
{
    using T = std::underlying_type_t<Enum>;
    return static_cast<Enum>(~static_cast<T>(value));
}

template <typename Enum>
EnableIfBitmaskRef<Enum> operator|=(Enum &lhs, Enum rhs)
{
    lhs = lhs | rhs;
    return lhs;
}

template <typename Enum>
EnableIfBitmaskRef<Enum> operator&=(Enum &lhs, Enum rhs)
{
    lhs = lhs & rhs;
    return lhs;
}

template <typename Enum>
EnableIfBitmaskRef<Enum> operator^=(Enum &lhs, Enum rhs)
{
    lhs = lhs ^ rhs;
    return lhs;
}
