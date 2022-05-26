#include <Driver/Driver.h>

using namespace GSLanguageCompiler;

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C8>> argv) {
    return Driver::GS_Compiler::Start(argc, argv);
}

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

    public:

        inline constexpr ValueType *Data() {
            return _data;
        }

        inline constexpr SizeType Size() const {
            return SizeValue;
        }

    public:

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
    inline constexpr containers::Array<ValueT, SizeV> make_array() {
        return containers::Array<ValueT, SizeV>();
    }

    template<typename ValueT, auto SizeV>
    inline constexpr containers::Array<ValueT, SizeV> make_array(std::initializer_list<ValueT> initializerList) {
        return containers::Array<ValueT, SizeV>(initializerList);
    }

}

void func() {
    auto array = containers::make_array<int, 12>({1, 2, 3});
}
