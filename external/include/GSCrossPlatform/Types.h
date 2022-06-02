#ifndef GSCROSSPLATFORM_TYPES_H
#define GSCROSSPLATFORM_TYPES_H

#include <cstdint>

#include <GSCrossPlatform/Defines.h>

using Bool = bool;

using C8 = char;

using C16 = char16_t;

using C32 = char32_t;

using I8 = std::int8_t;

using U8 = std::uint8_t;

using I16 = std::int16_t;

using U16 = std::uint16_t;

using I32 = std::int32_t;

using U32 = std::uint32_t;

using I64 = std::int64_t;

using U64 = std::uint64_t;

template<typename T>
using Ptr = T *;

template<typename T>
using LRef = T &;

template<typename T>
using RRef = T &&;

template<typename T>
using Const = const T;

template<typename T>
using ConstPtr = Const<Ptr<T>>;

template<typename T>
using ConstLRef = Const<LRef<T>>;

template<typename T>
using ConstRRef = Const<RRef<T>>;

#endif //GSCROSSPLATFORM_TYPES_H
