#ifndef GSCROSSPLATFORM_MEMORY_H
#define GSCROSSPLATFORM_MEMORY_H

#include <GSCrossPlatform/Types.h>

template<typename ValueT>
class UniquePtr {
public:

    using ValueType = ValueT;

public:

    constexpr UniquePtr()
            : _pointer(nullptr) {}

    constexpr UniquePtr(ValueType *pointer)
            : _pointer(pointer) {}

public:

    constexpr UniquePtr(const UniquePtr<ValueType> &uniquePtr) = delete;

    constexpr UniquePtr(UniquePtr<ValueType> &&uniquePtr) noexcept {
        if (this == &uniquePtr) {
            return *this;
        }

        _pointer = uniquePtr._pointer;

        uniquePtr._pointer = nullptr;
    }

public:

    constexpr ~UniquePtr() {
        delete _pointer;
    }

public:

    inline constexpr UniquePtr<ValueType> &operator=(const UniquePtr<ValueType> &uniquePtr) = delete;

    inline constexpr UniquePtr<ValueType> &operator=(UniquePtr<ValueType> &&uniquePtr) {
        if (this == &uniquePtr) {
            return *this;
        }

       _pointer = uniquePtr._pointer;

       uniquePtr._pointer = nullptr;

       return *this;
    }

    inline constexpr ValueType &operator*() {
        return *_pointer;
    }

    inline constexpr ValueType *operator->() {
        return _pointer;
    }

private:

    ValueType *_pointer;
};

#endif //GSCROSSPLATFORM_MEMORY_H
