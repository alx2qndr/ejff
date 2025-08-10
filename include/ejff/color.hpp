#pragma once

#include <algorithm>
#include <initializer_list>

namespace ejff
{

template <typename T = float, size_t Channels = 4>
class Color
{
public:
    constexpr Color() noexcept : components{} {}

    constexpr Color(std::initializer_list<T> list) noexcept
    {
        size_t count = std::min(list.size(), Channels);
        size_t i = 0;
        for (auto val : list)
        {
            if (i >= count)
                break;
            components[i++] = val;
        }
        for (; i < Channels; ++i)
            components[i] = T{0};
    }

    constexpr T &operator[](size_t index) noexcept { return components[index]; }
    constexpr const T &operator[](size_t index) const noexcept
    {
        return components[index];
    }

    constexpr T &red() noexcept
    {
        static_assert(Channels >= 1);
        return components[0];
    }

    constexpr const T &red() const noexcept
    {
        static_assert(Channels >= 1);
        return components[0];
    }

    constexpr T &green() noexcept
    {
        static_assert(Channels >= 2);
        return components[1];
    }

    constexpr const T &green() const noexcept
    {
        static_assert(Channels >= 2);
        return components[1];
    }

    constexpr T &blue() noexcept
    {
        static_assert(Channels >= 3);
        return components[2];
    }

    constexpr const T &blue() const noexcept
    {
        static_assert(Channels >= 3);
        return components[2];
    }

    constexpr T &alpha() noexcept
    {
        static_assert(Channels >= 4);
        return components[3];
    }

    constexpr const T &alpha() const noexcept
    {
        static_assert(Channels >= 4);
        return components[3];
    }

private:
    T components[Channels]{};
};

} // namespace ejff
