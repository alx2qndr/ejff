#pragma once

#include <memory>
#include <stdexcept>
#include <utility>

#include <fmt/format.h>

namespace ejff
{

template <typename T, typename Deleter>
class UniqueHandle
{
public:
    UniqueHandle() = default;

    explicit UniqueHandle(T *ptr, Deleter deleter = {}) : ptr_(ptr, std::move(deleter))
    {
        if (!ptr_)
        {
            throw std::invalid_argument(
                "ejff::UniqueHandle cannot be initialized with a null pointer.");
        }
    }

    UniqueHandle(const UniqueHandle &) = delete;
    UniqueHandle &operator=(const UniqueHandle &) = delete;

    UniqueHandle(UniqueHandle &&) noexcept = default;
    UniqueHandle &operator=(UniqueHandle &&) noexcept = default;

    ~UniqueHandle() = default;

    void reset(T *new_ptr = nullptr) noexcept { ptr_.reset(new_ptr); }

    T *release() noexcept { return ptr_.release(); }

    T *get() noexcept { return ptr_.get(); }
    T *get() const noexcept { return ptr_.get(); }

    explicit operator bool() const noexcept { return ptr_ != nullptr; }

protected:
    std::unique_ptr<T, Deleter> ptr_;
};

} // namespace ejff
