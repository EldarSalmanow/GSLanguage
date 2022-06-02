#ifndef GSCROSSPLATFORM_VECTOR_H
#define GSCROSSPLATFORM_VECTOR_H

#include <stdexcept>

#include <GSCrossPlatform/Types.h>

template<typename ValueT>
class Vector {
public:

    using ValueType = ValueT;

    inline static constexpr const U64 ChunkSize = 4;

public:

    using Iterator = ValueType *;

    using ConstIterator = const ValueType *;

public:

    constexpr Vector() {
        _data = nullptr;

        _size = 0;

        _allocatedSize = 0;
    }

    constexpr Vector(std::initializer_list<ValueType> initializerList) {
        _size = initializerList.size();

        if (_size > 0) {
            _allocatedSize = AlignSize(_size);

            _data = new ValueType[_allocatedSize];

            for (U64 index = 0; auto &value : initializerList) {
                _data[index] = value;

                ++index;
            }
        } else {
            _allocatedSize = 0;

            _data = nullptr;
        }
    }

    constexpr Vector(const Vector<ValueType> &vector) {
        if (this == &vector) {
            return;
        }

        _size = vector.Size();

        if (_size > 0) {
            _allocatedSize = AlignSize(_size);

            _data = new ValueType[_allocatedSize];

            for (U64 index = 0; auto &value : vector) {
                _data[index] = value;

                ++index;
            }
        } else {
            _allocatedSize = 0;

            _data = nullptr;
        }
    }

    constexpr Vector(Vector<ValueType> &&vector) noexcept {
        if (this == &vector) {
            return;
        }

        _size = vector.Size();

        if (_size > 0) {
            _allocatedSize = AlignSize(_size);

            _data = new ValueType[_allocatedSize];

            for (U64 index = 0; auto &value : vector) {
                _data[index] = std::move(value);

                ++index;
            }
        } else {
            _allocatedSize = 0;

            _data = nullptr;
        }
    }

public:

    constexpr ~Vector() {
        delete[] _data;
    }

public:

    constexpr Vector<ValueType> &Append(const ValueType &value) {
        if (_size == _allocatedSize) {
            _allocatedSize += ChunkSize;

            auto newData = new ValueType[_allocatedSize];

            for (U64 index = 0; auto &vectorValue : *this) {
                newData[index] = vectorValue;

                ++index;
            }

            delete[] _data;

            _data = newData;
        }

        ++_size;

        _data[_size - 1] = value;

        return *this;
    }

    constexpr Vector<ValueType> &Append(std::initializer_list<ValueType> initializerList) {
        for (auto &value : initializerList) {
            Append(value);
        }

        return *this;
    }

public:

    inline constexpr ValueType *Data() {
        return _data;
    }

    inline constexpr U64 Size() const {
        return _size;
    }

    inline constexpr Bool Empty() const {
        return _size == 0;
    }

public:

    inline constexpr Iterator begin() {
        return _data;
    }

    inline constexpr Iterator end() {
        return _data + _size;
    }

    inline constexpr ConstIterator begin() const {
        return _data;
    }

    inline constexpr ConstIterator end() const {
        return _data + _size;
    }

public:

    inline constexpr Vector<ValueType> &operator=(const Vector<ValueType> &vector) {
        if (this == &vector) {
            return *this;
        }

        delete[] _data;

        _size = vector.Size();

        if (_size > 0) {
            _allocatedSize = AlignSize(_size);

            _data = new ValueType[_allocatedSize];

            for (U64 index = 0; auto &value : vector) {
                _data[index] = value;

                ++index;
            }
        } else {
            _allocatedSize = 0;

            _data = nullptr;
        }

        return *this;
    }

    inline constexpr Vector<ValueType> &operator=(Vector<ValueType> &&vector) noexcept {
        if (this == &vector) {
            return *this;
        }

        delete[] _data;

        _size = vector.Size();

        if (_size > 0) {
            _allocatedSize = AlignSize(_size);

            _data = new ValueType[_allocatedSize];

            for (U64 index = 0; auto &value : vector) {
                _data[index] = std::move(value);

                ++index;
            }
        } else {
            _allocatedSize = 0;

            _data = nullptr;
        }

        return *this;
    }

    inline constexpr Bool operator==(const Vector<ValueType> &vector) const {
        if (_size != vector.Size()) {
            return false;
        }

        for (U64 index = 0; auto &value : vector) {
            if (_data[index] != value) {
                return false;
            }

            ++index;
        }

        return true;
    }

    inline constexpr Bool operator!=(const Vector<ValueType> &vector) const {
        return !(*this == vector);
    }

    inline constexpr ValueType &operator[](const U64 &index) {
        if (index >= 0 && index < _size) {
            return _data[index];
        }

        throw std::runtime_error("Vector::operator[](const U64 &): Index out of range!");
    }

    inline constexpr const ValueType &operator[](const U64 &index) const {
        if (index >= 0 && index < _size) {
            return _data[index];
        }

        throw std::runtime_error("Vector::operator[](const std:uint64_t &) const: Index out of range!");
    }

private:

    inline constexpr U64 AlignSize(const U64 &size) const {
        return (size / ChunkSize + ((size % ChunkSize) > 0 ? 1 : 0)) * ChunkSize;
    }

private:

    ValueType *_data;

    U64 _size;

    U64 _allocatedSize;
};

template<typename ValueT>
inline constexpr Vector<ValueT> make_vector() {
    return Vector<ValueT>();
}

template<typename ValueT>
inline constexpr Vector<ValueT> make_vector(std::initializer_list<ValueT> initializerList) {
    return Vector<ValueT>(initializerList);
}

template<typename ValueT>
inline constexpr Vector<ValueT> make_vector(const Vector<ValueT> &vector) {
    return Vector<ValueT>(vector);
}

template<typename ValueT>
inline constexpr Vector<ValueT> make_vector(Vector<ValueT> &&vector) {
    return Vector<ValueT>(vector);
}

namespace std {

    template<typename ValueT>
    constexpr size_t size(const Vector<ValueT> &vector) noexcept {
        return vector.Size();
    }

    template<typename ValueT>
    constexpr auto data(Vector<ValueT> &vector) {
        return vector.Data();
    }

}

#endif //GSCROSSPLATFORM_VECTOR_H
