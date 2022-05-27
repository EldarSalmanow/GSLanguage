#include <Driver/Driver.h>

using namespace GSLanguageCompiler;

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C8>> argv) {
    return Driver::GS_Compiler::Start(argc, argv);
}

#include <concepts>

namespace containers {

    template<typename ValueT, auto SizeV>
    class Array {
    public:

        using ValueType = ValueT;

        using SizeType = decltype(SizeV);

        inline constexpr static SizeType SizeValue = SizeV;

    public:

        constexpr Array() = default;

        constexpr Array(std::initializer_list<ValueType> initializerList) {
            if (initializerList.size() > SizeValue) {
                throw std::runtime_error("containers::Array::Array(std::initializer_list<ValueType>): Initializer list bigger than array size!");
            }

            for (std::uint64_t index = 0; auto &value : initializerList) {
                _data[index] = value;

                ++index;
            }
        }

        constexpr Array(const Array<ValueType, SizeValue> &array) {
            for (std::uint64_t index = 0; auto &value : array) {
                _data[index] = value;

                ++index;
            }
        }

        constexpr Array(Array<ValueType, SizeValue> &&array) noexcept {
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

        inline constexpr ValueType *begin() {
            return _data;
        }

        inline constexpr ValueType *end() {
            return _data + SizeValue;
        }

        inline const constexpr ValueType *begin() const {
            return _data;
        }

        inline const constexpr ValueType *end() const {
            return _data + SizeValue;
        }

    public:

        inline constexpr Array<ValueType, SizeValue> &operator=(const Array<ValueType, SizeValue> &array) {
            for (std::uint64_t index = 0; auto &value : array) {
                _data[index] = value;

                ++index;
            }
        }

        inline constexpr Array<ValueType, SizeValue> &operator=(Array<ValueType, SizeValue> &&array) noexcept {
            for (std::uint64_t index = 0; auto &value : array) {
                _data[index] = value;

                ++index;
            }
        }

        inline constexpr ValueType &operator[](const std::uint64_t &index) {
            if (index >= 0 && index < SizeValue) {
                return _data[index];
            }

            throw std::runtime_error("containers::Array::operator[]: Index out of range!");
        }

        inline const constexpr ValueType &operator[](const std::uint64_t &index) const {
            if (index >= 0 && index < SizeValue) {
                return _data[index];
            }

            throw std::runtime_error("containers::Array::operator[] const: Index out of range!");
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

    template<typename T>
    concept HasAsString = requires(T Type) {
        Type.AsString();
    };

    template<typename T>
    inline UString to_string(const T &value) {
        return UString(value);
    }

    template<std::integral T>
    inline UString to_string(const T &integral) {
        return UString(std::to_string(integral));
    }

    template<HasAsString T>
    inline UString to_string(const T &value) {
        return value.AsString();
    }

    template<typename ValueT, auto SizeV>
    inline UString to_string(const Array<ValueT, SizeV> &array) {
        UString string;

        string += "[ ";

        for (auto &value : array) {
            string += to_string(value) + " ";
        }

        string += "]";

        return string;
    }

}

namespace std {

    template <typename ValueT, auto SizeV>
    constexpr size_t size(const containers::Array<ValueT, SizeV> &array) noexcept {
        return array.Size();
    }

    template <typename ValueT, auto SizeV>
    constexpr auto data(containers::Array<ValueT, SizeV> &array) {
        return array.Data();
    }

}

struct X {
public:

    X(int a)
            : _a(a) {}

public:

    UString AsString() const {
        return UString(std::to_string(_a));
    }

private:

    int _a;
};

void f() {
    auto array = containers::make_array<int, 5>({1, 2, 3, 4, 5});

    auto str = containers::to_string(array);

    auto s = containers::to_string(X(1 + 1));
}

