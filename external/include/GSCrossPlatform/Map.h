#ifndef GSCROSSPLATFORM_MAP_H
#define GSCROSSPLATFORM_MAP_H

#include <GSCrossPlatform/Vector.h>

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

    inline constexpr KeyType &Key() {
        return _key;
    }

    inline constexpr ValueType &Value() {
        return _value;
    }

    inline constexpr const KeyType &Key() const {
        return _key;
    }

    inline constexpr const ValueType &Value() const {
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

    using Iterator = typename Vector<Pair<KeyType, ValueType>>::Iterator;

    using ConstIterator = typename Vector<Pair<KeyType, ValueType>>::ConstIterator;

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

    inline constexpr U64 Size() const {
        return _pairs.Size();
    }

public:

    inline constexpr Iterator begin() {
        return _pairs.begin();
    }

    inline constexpr Iterator end() {
        return _pairs.end();
    }

    inline constexpr ConstIterator begin() const {
        return _pairs.begin();
    }

    inline constexpr ConstIterator end() const {
        return _pairs.end();
    }

public:

    inline constexpr Map<KeyType, ValueType> &operator=(const Map<KeyType, ValueType> &map) {
        if (this == &map) {
            return *this;
        }

        _pairs = map._pairs;

        return *this;
    }

    inline constexpr Map<KeyType, ValueType> &operator=(Map<KeyType, ValueType> &&map) noexcept {
        if (this == &map) {
            return *this;
        }

        _pairs = std::move(map._pairs);

        return *this;
    }

    inline constexpr Bool operator==(const Map<KeyType, ValueType> &map) const {
        if (_pairs.Size() != map.Size()) {
            return false;
        }

        for (U64 index = 0; auto &pair : map) {
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

        return _pairs.Append(Pair<KeyType, ValueType>(key, ValueType()))[_pairs.Size() - 1].Value();
    }

    inline constexpr const ValueType &operator[](const KeyType &key) const {
        for (auto &pair : _pairs) {
            if (pair.Key() == key) {
                return pair.Value();
            }
        }

        return _pairs.Append(Pair<KeyType, ValueType>(key, ValueType()))[_pairs.Size() - 1].Value();
    }

private:

    Vector<Pair<KeyType, ValueType>> _pairs;
};

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

namespace std {

    template<typename KeyT, typename ValueT>
    constexpr size_t size(const Map<KeyT, ValueT> &map) noexcept {
        return map.Size();
    }

    template<typename KeyT, typename ValueT>
    constexpr auto data(Map<KeyT, ValueT> &map) {
        return map.Data();
    }

}

#endif //GSCROSSPLATFORM_MAP_H
