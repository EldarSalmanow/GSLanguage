#ifndef GSCROSSPLATFORM_ARRAY_H
#define GSCROSSPLATFORM_ARRAY_H

#include <stdexcept>

template<typename ValueT, auto SizeV>
class Array {
public:

    using ValueType = ValueT;

    using SizeType = decltype(SizeV);

    inline static constexpr const SizeType SizeValue = SizeV;

public:

    using Iterator = ValueType *;

    using ConstIterator = const ValueType *;

public:

    constexpr Array() = default;

    constexpr Array(std::initializer_list<ValueType> initializerList) {
        if (initializerList.size() > SizeValue) {
            throw std::runtime_error("Array::Array(std::initializer_list<ValueType>): Initializer list bigger than array size!");
        }

        for (std::uint64_t index = 0; auto &value : initializerList) {
            _data[index] = value;

            ++index;
        }
    }

    constexpr Array(const Array<ValueType, SizeValue> &array) {
        if (this == &array) {
            return;
        }

        for (std::uint64_t index = 0; auto &value : array) {
            _data[index] = value;

            ++index;
        }
    }

    constexpr Array(Array<ValueType, SizeValue> &&array) noexcept {
        if (this == &array) {
            return;
        }

        for (std::uint64_t index = 0; auto &value : array) {
            _data[index] = value;

            ++index;
        }
    }

public:

    inline constexpr ValueType *Data() {
        return _data;
    }

    inline constexpr SizeType Size() const {
        return SizeValue;
    }

public:

    inline constexpr Iterator begin() {
        return _data;
    }

    inline constexpr Iterator end() {
        return _data + SizeValue;
    }

    inline constexpr ConstIterator begin() const {
        return _data;
    }

    inline constexpr ConstIterator end() const {
        return _data + SizeValue;
    }

public:

    inline constexpr Array<ValueType, SizeValue> &operator=(const Array<ValueType, SizeValue> &array) {
        if (this == &array) {
            return *this;
        }

        for (std::uint64_t index = 0; auto &value : array) {
            _data[index] = value;

            ++index;
        }

        return *this;
    }

    inline constexpr Array<ValueType, SizeValue> &operator=(Array<ValueType, SizeValue> &&array) noexcept {
        if (this == &array) {
            return *this;
        }

        for (std::uint64_t index = 0; auto &value : array) {
            _data[index] = value;

            ++index;
        }

        return *this;
    }

    inline constexpr bool operator==(const Array<ValueType, SizeValue> &array) const {
        for (std::uint64_t index = 0; auto &value : array) {
            if (_data[index] != value) {
                return false;
            }

            ++index;
        }

        return true;
    }

    inline constexpr bool operator!=(const Array<ValueType, SizeValue> &array) const {
        return !(*this == array);
    }

    inline constexpr ValueType &operator[](const std::uint64_t &index) {
        if (index >= 0 && index < SizeValue) {
            return _data[index];
        }

        throw std::runtime_error("Array::operator[](const std::uint64_t &): Index out of range!");
    }

    inline constexpr const ValueType &operator[](const std::uint64_t &index) const {
        if (index >= 0 && index < SizeValue) {
            return _data[index];
        }

        throw std::runtime_error("Array::operator[](const std::uint64_t &) const: Index out of range!");
    }

private:

    ValueType _data[SizeValue];
};

template<typename ValueT, auto SizeV>
inline constexpr Array<ValueT, SizeV> make_array() {
    return Array<ValueT, SizeV>();
}

template<typename ValueT, auto SizeV>
inline constexpr Array<ValueT, SizeV> make_array(std::initializer_list<ValueT> initializerList) {
    return Array<ValueT, SizeV>(initializerList);
}

template<typename ValueT, auto SizeV>
inline constexpr Array<ValueT, SizeV> make_array(const Array<ValueT, SizeV> &array) {
    return Array<ValueT, SizeV>(array);
}

template<typename ValueT, auto SizeV>
inline constexpr Array<ValueT, SizeV> make_array(Array<ValueT, SizeV> &&array) {
    return Array<ValueT, SizeV>(array);
}

namespace std {

    template<typename ValueT, auto SizeV>
    constexpr size_t size(const Array<ValueT, SizeV> &array) noexcept {
        return array.Size();
    }

    template<typename ValueT, auto SizeV>
    constexpr auto data(Array<ValueT, SizeV> &array) {
        return array.Data();
    }

}

#endif //GSCROSSPLATFORM_ARRAY_H
