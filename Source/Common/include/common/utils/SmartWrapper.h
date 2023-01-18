#pragma once

#include <functional>
#include <optional>
#include <utility>

namespace common::utils
{
    template<typename T>
    class SmartWrapper
    {
    public:
        SmartWrapper()
        {
        }

        SmartWrapper(T handle, std::function<void(T)> deleter)
            : _handle(handle), _deleter(deleter)
        {
        }

        SmartWrapper(const SmartWrapper&) = delete;
        SmartWrapper<T>& operator=(const SmartWrapper&) = delete;

        SmartWrapper(SmartWrapper&& smartWrapper)
        {
            std::swap(_handle, smartWrapper._handle);
            std::swap(_deleter, smartWrapper._deleter);
        }

        SmartWrapper<T>& operator=(SmartWrapper&& smartWrapper)
        {
            std::swap(_handle, smartWrapper._handle);
            std::swap(_deleter, smartWrapper._deleter);
            return *this;
        }

        ~SmartWrapper()
        {
            if (*this)
                _deleter(_handle.value());
        }

        operator bool()
        {
            return _handle.has_value();
        }

        T& value()
        {
            return _handle.value();
        }

        const T& value() const
        {
            return _handle.value();
        }

    private:
        std::optional<T> _handle;
        std::function<void(T)> _deleter;
    };
}
