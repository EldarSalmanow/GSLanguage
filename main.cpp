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

            throw std::runtime_error("containers::Array::operator[](const std::uint64_t &): Index out of range!");
        }

        inline constexpr const ValueType &operator[](const std::uint64_t &index) const {
            if (index >= 0 && index < SizeValue) {
                return _data[index];
            }

            throw std::runtime_error("containers::Array::operator[](const std::uint64_t &) const: Index out of range!");
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

        constexpr Vector<ValueType> &Append(const ValueType &value) {
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

            throw std::runtime_error("containers::Vector::operator[](const std::uint64_t &): Index out of range!");
        }

        inline constexpr const ValueType &operator[](const std::uint64_t &index) const {
            if (index >= 0 && index < _size) {
                return _data[index];
            }

            throw std::runtime_error("containers::Vector::operator[](const std:uint64_t &) const: Index out of range!");
        }

    private:

        ValueType *_data;

        std::uint64_t _size;

        std::uint64_t _allocatedSize;
    };

    template<typename KeyT, typename ValueT>
    class Pair {
    public:

        using KeyType = KeyT;

        using ValueType = ValueT;

    public:

        constexpr Pair() = default;

        constexpr Pair(KeyType key, ValueType value)
                : _key(key), _value(value) {}

        constexpr Pair(const Pair<KeyType, ValueType> &pair) {
            if (this == &pair) {
                return;
            }

            _key = pair.Key();

            _value = pair.Value();
        }

        constexpr Pair(Pair<KeyType, ValueType> &&pair) noexcept {
            if (this == &pair) {
                return;
            }

            _key = std::move(pair.Key());

            _value = std::move(pair.Value());
        }

    public:

        inline constexpr KeyType Key() {
            return _key;
        }

        inline constexpr ValueType Value() {
            return _value;
        }

        inline constexpr KeyType Key() const {
            return _key;
        }

        inline constexpr ValueType Value() const {
            return _value;
        }

    public:

        inline constexpr Pair<KeyType, ValueType> &operator=(const Pair<KeyType, ValueType> &pair) {
            if (this == &pair) {
                return *this;
            }

            _key = pair.Key();

            _value = pair.Value();

            return *this;
        }

        inline constexpr Pair<KeyType, ValueType> &operator=(Pair<KeyType, ValueType> &&pair) noexcept {
            if (this == &pair) {
                return *this;
            }

            _key = std::move(pair.Key());

            _value = std::move(pair.Value());

            return *this;
        }

        inline constexpr Bool operator==(const Pair<KeyType, ValueType> &pair) const {
            if (_key != pair.Key() || _value != pair.Value()) {
                return false;
            }

            return true;
        }

        inline constexpr Bool operator!=(const Pair<KeyType, ValueType> &pair) const {
            return !(*this == pair);
        }

    private:

        KeyType _key;

        ValueType _value;
    };

    template<typename KeyT, typename ValueT>
    class Map {
    public:

        using KeyType = KeyT;

        using ValueType = ValueT;

    public:

        constexpr Map() = default;

        constexpr Map(std::initializer_list<Pair<KeyType, ValueType>> initializerList) {
            for (auto &pair : initializerList) {
                _pairs.append(pair);
            }
        }

        constexpr Map(const Map<KeyType, ValueType> &map) {
            if (this == &map) {
                return;
            }

            _pairs = map.Pairs();
        }

        constexpr Map(Map<KeyType, ValueType> &&map) noexcept {
            if (this == &map) {
                return;
            }

            _pairs = std::move(map.Pairs());
        }

    public:

        inline constexpr Map<KeyType, ValueType> &Append(const Pair<KeyType, ValueType> &pair) {
            _pairs.Append(pair);

            return *this;
        }

        inline constexpr Map<KeyType, ValueType> &Append(std::initializer_list<Pair<KeyType, ValueType>> pairs) {
            for (auto &pair : pairs) {
                Append(pair);
            }

            return *this;
        }

    public:

        inline constexpr Pair<KeyType, ValueType> *Data() {
            return _pairs.Data();
        }

        inline constexpr std::uint64_t Size() const {
            return _pairs.Size();
        }

    public:

        inline constexpr Pair<KeyType, ValueType> *begin() {
            return _pairs.begin();
        }

        inline constexpr Pair<KeyType, ValueType> *end() {
            return _pairs.end();
        }

        inline constexpr const Pair<KeyType, ValueType> *begin() const {
            return _pairs.begin();
        }

        inline constexpr const Pair<KeyType, ValueType> *end() const {
            return _pairs.end();
        }

    public:

        inline constexpr Vector<Pair<KeyType, ValueType>> Pairs() const {
            return _pairs;
        }

    public:

        inline constexpr Map<KeyType, ValueType> &operator=(const Map<KeyType, ValueType> &map) {
            if (this == &map) {
                return *this;
            }

            _pairs = map.Pairs();

            return *this;
        }

        inline constexpr Map<KeyType, ValueType> &operator=(Map<KeyType, ValueType> &&map) noexcept {
            if (this == &map) {
                return *this;
            }

            _pairs = std::move(map.Pairs());

            return *this;
        }

        inline constexpr Bool operator==(const Map<KeyType, ValueType> &map) const {
            if (_pairs.Size() != map.Size()) {
                return false;
            }

            for (std::uint64_t index = 0; auto &pair : map) {
                if (_pairs[index] != pair) {
                    return false;
                }
            }

            return true;
        }

        inline constexpr Bool operator!=(const Map<KeyType, ValueType> &map) const {
            return !(*this == map);
        }

        inline constexpr ValueType &operator[](const KeyType &key) {
            for (auto &pair : _pairs) {
                if (pair.Key() == key) {
                    return pair.Value();
                }
            }

            throw std::runtime_error("containers::Map::operator[](const KeyType &): Can`t found key in map!");
        }

        inline constexpr const ValueType &operator[](const KeyType &key) const {
            for (auto &pair : _pairs) {
                if (pair.Key() == key) {
                    return pair.Value();
                }
            }

            throw std::runtime_error("containers::Map::operator[](const KeyType &) const: Can`t found key in map!");
        }

    private:

        Vector<Pair<KeyType, ValueType>> _pairs;
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

    template<typename KeyT, typename ValueT>
    inline constexpr Pair<KeyT, ValueT> make_pair() {
        return Pair<KeyT, ValueT>();
    }

    template<typename KeyT, typename ValueT>
    inline constexpr Pair<KeyT, ValueT> make_pair(KeyT key, ValueT value) {
        return Pair<KeyT, ValueT>(key, value);
    }

    template<typename KeyT, typename ValueT>
    inline constexpr Pair<KeyT, ValueT> make_pair(const Pair<KeyT, ValueT> &pair) {
        return Pair<KeyT, ValueT>(pair);
    }

    template<typename KeyT, typename ValueT>
    inline constexpr Pair<KeyT, ValueT> make_pair(Pair<KeyT, ValueT> &&pair) {
        return Pair<KeyT, ValueT>(pair);
    }

    template<typename KeyT, typename ValueT>
    inline constexpr Map<KeyT, ValueT> make_map() {
        return Map<KeyT, ValueT>();
    }

    template<typename KeyT, typename ValueT>
    inline constexpr Map<KeyT, ValueT> make_map(std::initializer_list<Pair<KeyT, ValueT>> initializerList) {
        return Map<KeyT, ValueT>(initializerList);
    }

    template<typename KeyT, typename ValueT>
    inline constexpr Map<KeyT, ValueT> make_map(const Map<KeyT, ValueT> &map) {
        return Map<KeyT, ValueT>(map);
    }

    template<typename KeyT, typename ValueT>
    inline constexpr Map<KeyT, ValueT> make_map(Map<KeyT, ValueT> &&map) {
        return Map<KeyT, ValueT>(map);
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

    template<typename KeyT, typename ValueT>
    constexpr size_t size(const containers::Map<KeyT, ValueT> &map) noexcept {
        return map.Size();
    }

    template<typename KeyT, typename ValueT>
    constexpr auto data(containers::Map<KeyT, ValueT> &map) {
        return map.Data();
    }

}

#include <Lexer/Lexer.h>

void test() {
    containers::Vector<int> vector;

    vector.Append({1, 2, 3, 4});

    containers::Map<int, UString> map;

    map.Append({1, "Эльдар"});

    auto reservedWords = containers::make_map<UString, Lexer::TokenType>();

    reservedWords["var"] = Lexer::TokenType::KeywordVar;
}

