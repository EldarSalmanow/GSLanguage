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

        inline static constexpr const SizeType SizeValue = SizeV;

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

        inline constexpr ValueType *begin() {
            return _data;
        }

        inline constexpr ValueType *end() {
            return _data + SizeValue;
        }

        inline constexpr const ValueType *begin() const {
            return _data;
        }

        inline constexpr const ValueType *end() const {
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

        inline constexpr Bool operator==(const Array<ValueType, SizeValue> &array) const {
            for (std::uint64_t index = 0; auto &value : array) {
                if (_data[index] != value) {
                    return false;
                }

                ++index;
            }

            return true;
        }

        inline constexpr Bool operator!=(const Array<ValueType, SizeValue> &array) const {
            return !(*this == array);
        }

        inline constexpr ValueType &operator[](const std::uint64_t &index) {
            if (index >= 0 && index < SizeValue) {
                return _data[index];
            }

            throw std::runtime_error("containers::Array::operator[]: Index out of range!");
        }

        inline constexpr const ValueType &operator[](const std::uint64_t &index) const {
            if (index >= 0 && index < SizeValue) {
                return _data[index];
            }

            throw std::runtime_error("containers::Array::operator[] const: Index out of range!");
        }

    private:

        ValueType _data[SizeValue];
    };

    template<typename ValueT>
    class Vector {
    public:

        using ValueType = ValueT;

        inline static constexpr const std::uint64_t ChunkSize = 20;

    public:

        constexpr Vector()
                : _data(nullptr), _size(0), _allocatedSize(0) {}

        constexpr Vector(std::initializer_list<ValueType> initializerList) {
            _size = initializerList.size();

            _data = new ValueType[_size];

            _allocatedSize = _size;

            for (std::uint64_t index = 0; auto &value : initializerList) {
                _data[index] = value;

                ++index;
            }
        }

        constexpr Vector(const Vector<ValueType> &vector) {
            if (this == &vector) {
                return;
            }

            delete[] _data;

            _size = vector.Size();

            _data = new ValueType[_size];

            _allocatedSize = _size;

            for (std::uint64_t index = 0; auto &value : vector) {
                _data[index] = value;

                ++index;
            }
        }

        constexpr Vector(Vector<ValueType> &&vector) noexcept {
            if (this == &vector) {
                return;
            }

            delete[] _data;

            _size = vector.Size();

            _data = new ValueType[_size];

            _allocatedSize = _size;

            for (std::uint64_t index = 0; auto &value : vector) {
                _data[index] = value;

                ++index;
            }
        }

    public:

        constexpr ~Vector() {
            delete[] _data;
        }

    public:

        void append(const ValueType &value) {
            if (_size == _allocatedSize) {
                _allocatedSize += ChunkSize;

                auto newData = new ValueType[_allocatedSize];

                for (std::uint64_t index = 0; auto &vectorValue : *this) {
                    newData[index] = vectorValue;

                    ++index;
                }

                delete[] _data;

                _data = newData;
            }

            ++_size;

            _data[_size] = value;
        }

    public:

        inline constexpr ValueType *Data() {
            return _data;
        }

        inline constexpr std::uint64_t Size() const {
            return _size;
        }

    public:

        inline constexpr ValueType *begin() {
            return _data;
        }

        inline constexpr ValueType *end() {
            return _data + _size;
        }

        inline constexpr const ValueType *begin() const {
            return _data;
        }

        inline constexpr const ValueType *end() const {
            return _data + _size;
        }

    public:

        inline constexpr Vector<ValueType> &operator=(const Vector<ValueType> &vector) {
            if (this == &vector) {
                return *this;
            }

            delete[] _data;

            _size = vector.Size();

            _data = new ValueType[_size];

            _allocatedSize = _size;

            for (std::uint64_t index = 0; auto &value : vector) {
                _data[index] = value;

                ++index;
            }

            return *this;
        }

        inline constexpr Vector<ValueType> &operator=(Vector<ValueType> &&vector) noexcept {
            if (this == &vector) {
                return *this;
            }

            delete[] _data;

            _size = vector.Size();

            _data = new ValueType[_size];

            _allocatedSize = _size;

            for (std::uint64_t index = 0; auto &value : vector) {
                _data[index] = value;

                ++index;
            }

            return *this;
        }

        inline constexpr Bool operator==(const Vector<ValueType> &vector) const {
            if (_size != vector.Size()) {
                return false;
            }

            for (std::uint64_t index = 0; auto &value : vector) {
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

        inline constexpr ValueType &operator[](const std::uint64_t &index) {
            if (index >= 0 && index < _size) {
                return _data[index];
            }

            throw std::runtime_error("containers::Vector::operator[]: Index out of range!");
        }

        inline constexpr const ValueType &operator[](const std::uint64_t &index) const {
            if (index >= 0 && index < _size) {
                return _data[index];
            }

            throw std::runtime_error("containers::Vector::operator[] const: Index out of range!");
        }

    public:

        ValueType *_data;

        std::uint64_t _size;

        std::uint64_t _allocatedSize;
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

}

namespace std {

    template<typename ValueT, auto SizeV>
    constexpr size_t size(const containers::Array<ValueT, SizeV> &array) noexcept {
        return array.Size();
    }

    template<typename ValueT, auto SizeV>
    constexpr auto data(containers::Array<ValueT, SizeV> &array) {
        return array.Data();
    }

    template<typename ValueT>
    constexpr size_t size(const containers::Vector<ValueT> &vector) noexcept {
        return vector.Size();
    }

    template<typename ValueT>
    constexpr auto data(containers::Vector<ValueT> &vector) {
        return vector.Data();
    }

}

void main() {
    auto vec = containers::make_vector<UString>({"Эльдар", "Азамат"});

    vec.append("Эмиль");

    std::cout << *std::find(vec.begin(), vec.end(), "Эмиль");

    return 0;
}

