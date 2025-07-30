#pragma once

#include <type_traits>

template <typename Enum>
struct EnableBitMaskOperators : std::false_type
{
};

#define ENABLE_BITMASK_OPERATORS(EnumType)                                     \
    template <>                                                                \
    struct EnableBitMaskOperators<EnumType> : std::true_type                   \
    {                                                                          \
    }

template <typename Enum>
using EnableIfBitMask =
    std::enable_if_t<EnableBitMaskOperators<Enum>::value, Enum>;

template <typename Enum>
constexpr EnableIfBitMask<Enum> operator|(Enum lhs, Enum rhs)
{
    using Underlying = std::underlying_type_t<Enum>;
    return static_cast<Enum>(static_cast<Underlying>(lhs) |
                             static_cast<Underlying>(rhs));
}

template <typename Enum>
constexpr EnableIfBitMask<Enum> operator&(Enum lhs, Enum rhs)
{
    using Underlying = std::underlying_type_t<Enum>;
    return static_cast<Enum>(static_cast<Underlying>(lhs) &
                             static_cast<Underlying>(rhs));
}

template <typename Enum>
constexpr EnableIfBitMask<Enum> operator~(Enum value)
{
    using Underlying = std::underlying_type_t<Enum>;
    return static_cast<Enum>(~static_cast<Underlying>(value));
}

template <typename Enum>
constexpr std::enable_if_t<EnableBitMaskOperators<Enum>::value, Enum &>
operator|=(Enum &lhs, Enum rhs)
{
    return lhs = lhs | rhs;
}

template <typename Enum>
constexpr std::enable_if_t<EnableBitMaskOperators<Enum>::value, Enum &>
operator&=(Enum &lhs, Enum rhs)
{
    return lhs = lhs & rhs;
}
