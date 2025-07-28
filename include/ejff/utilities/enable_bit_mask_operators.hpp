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
    };

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::value, Enum>::type operator|(
    Enum lhs, Enum rhs)
{
    using T = typename std::underlying_type<Enum>::type;
    return static_cast<Enum>(static_cast<T>(lhs) | static_cast<T>(rhs));
}

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::value, Enum>::type operator&(
    Enum lhs, Enum rhs)
{
    using T = typename std::underlying_type<Enum>::type;
    return static_cast<Enum>(static_cast<T>(lhs) & static_cast<T>(rhs));
}

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::value, Enum>::type operator~(
    Enum rhs)
{
    using T = typename std::underlying_type<Enum>::type;
    return static_cast<Enum>(~static_cast<T>(rhs));
}

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::value, Enum &>::type operator|=(
    Enum &lhs, Enum rhs)
{
    lhs = lhs | rhs;
    return lhs;
}

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::value, Enum &>::type operator&=(
    Enum &lhs, Enum rhs)
{
    lhs = lhs & rhs;
    return lhs;
}
