

# muUtility v2.0.0

muUtility (acrynomized to muu) is a public domain single-file single-header C utility library with no dependencies used by most mu libraries. It contains a collection of definitions and functions within a header wrapper (`MUU_H`) that is automatically defined if it is not defined already.

More information about mu libraries in general can be found at [the mu library information GitHub repository](https://github.com/Muukid/mu-library-information).

# Licensing

muUtility is licensed under public domain or MIT license, whichever you prefer. More information is provided in the accompanying file `license.md` and at the bottom of `muUtility.h`.


# Version

The macros `MUU_VERSION_MAJOR`, `MUU_VERSION_MINOR`, and `MUU_VERSION_PATCH` are defined to match its respective release version, following the formatting of `MAJOR.MINOR.PATCH`.

# `MUDEF`

The `MUDEF` macro is used by virtually all mu libraries, and is generally added before a header-defined variable or function. Its default value is `extern`, but can be changed to `static` by defining `MU_STATIC` before the header section of muUtility is defined. Its value can also be overwritten entirely to anything else by directly defining `MUDEF`.

# Secure warnings

mu libraries often use non-secure functions that will trigger warnings on certain compilers. These warnings are, to put it lightly, dumb, so muUtility defines `_CRT_SECURE_NO_WARNINGS`. However, it is not guaranteed that this definition will actually turn the warnings off, which, at that point, they have to be manually turned off by the user. This functionality can be turned off by defining `MU_SECURE_WARNINGS`.

# C++ extern

Every mu library's primary code externs "C" within the main chunks of their code; macros `MU_CPP_EXTERN_START` and `MU_CPP_EXTERN_END` are defined to make this process easier, and would read like this:

```
MU_CPP_EXTERN_START

// Library code goes here...

MU_CPP_EXTERN_END
```

# C standard library dependencies

muUtility has several C standard library dependencies, all of which are overridable by defining them before the inclusion of the file. The following is a list of those dependencies.

## `stdint.h` dependencies

* `int8_m` - equivalent to `int8_t` if `INT8_MAX` is defined; `char` if otherwise.

* `uint8_m` - equivalent to `uint8_t` if `UINT8_MAX` is defined; `unsigned char` if otherwise.

* `int16_m` - equivalent to `int16_t` if `INT16_MAX` is defined; `short` if otherwise.

* `uint16_m` - equivalent to `uint16_t` if `UINT16_MAX` is defined; `unsigned short` if otherwise.

* `int32_m` - equivalent to `int32_t` if `INT32_MAX` is defined; `long` if otherwise.

* `uint32_m` - equivalent to `uint32_t` if `UINT32_MAX` is defined; `unsigned long` if otherwise.

* `int64_m` - equivalent to `int64_t` if `INT64_MAX` is defined; `long long` if otherwise.

* `uint64_m` - equivalent to `uint64_t` if `UINT64_MAX` is defined; `unsigned long long` if otherwise.

* `MU_SIZE_MAX` - equivalent to `SIZE_MAX`.

## `stddef.h` dependencies

* `size_m` - equivalent to `size_t`.

## `stdbool.h` dependencies

* `muBool` - equivalent to `bool`.

* `MU_TRUE` - equivalent to `true`.

* `MU_FALSE` - equivalent to `false`.

# Zero struct

There are two macros, `MU_ZERO_STRUCT` and `MU_ZERO_STRUCT_CONST`, which are functions used to zero-out a struct's contents, with their only parameter being the struct type. The reason this needs to be defined is because the way C and C++ syntax handles an empty struct are different, and need to be adjusted for. These macros are overridable by defining them before `muUtility.h` is included.

# Byte manipulation

muUtility defines several inline functions that read a value from a given array of bytes. Internally, they're all defined with the prefix `muu_...`, and then a macro is defined for them as `MU_...` (with change in capitalization after the prefix as well). The macros for these functions can be overridden, and, in such case, the original function will go undefined. For example, the function `muu_rleu8` is primarily referenced via the macro `MU_RLEU8`, and if `MU_RLEU8` is overridden, `muu_rleu8` is never defined and is not referenceable.

All reading functions take in a pointer of bytes as their only parameter and have a return type of the fixed-width size of bits in question; for example, `muu_rleu8` is defined as:

```
MUDEF inline uint8_m muu_rleu8(muByte* b);
```

All writing functions take in a pointer of bytes as their first parameter, the number to be written as the second parameter, and have a return type of void; for example, `muu_wleu8` is defined as:

```
MUDEF inline void muu_wleu8(muByte* b, uint8_m n);
```

The exception to this is 24-bit, in which case, the fixed-width types are 32-bit (`uint32_m` / `int32_m`).

## Byte type

muUtility defines the type `muByte` to refer to a byte. It is defined as `uint8_m`, and is overridable.

## 8-bit

The following macros exist for byte manipulation regarding 8-bit integers:

* `MU_RLEU8` - reads an unsigned 8-bit integer from little-endian byte data; overridable macro to `muu_rleu8`.

* `MU_WLEU8` - writes an unsigned 8-bit integer to little-endian byte data; overridable macro to `muu_wleu8`.

* `MU_RLES8` - reads a signed 8-bit integer from little-endian byte data; overridable macro to `muu_rles8`.

* `MU_WLES8` - writes a signed 8-bit integer to little-endian byte data; overridable macro to `muu_wles8`.

* `MU_RBEU8` - reads an unsigned 8-bit integer from big-endian byte data; overridable macro to `muu_rbeu8`.

* `MU_WBEU8` - writes an unsigned 8-bit integer to big-endian byte data; overridable macro to `muu_wbeu8`.

* `MU_RBES8` - reads a signed 8-bit integer from big-endian byte data; overridable macro to `muu_rbes8`.

* `MU_WBES8` - writes a signed 8-bit integer to big-endian byte data; overridable macro to `muu_wbes8`.

## 16-bit

The following macros exist for byte manipulation regarding 16-bit integers:

* `MU_RLEU16` - reads an unsigned 16-bit integer from little-endian byte data; overridable macro to `muu_rleu16`.

* `MU_WLEU16` - writes an unsigned 16-bit integer to little-endian byte data; overridable macro to `muu_wleu16`.

* `MU_RLES16` - reads a signed 16-bit integer from little-endian byte data; overridable macro to `muu_rles16`.

* `MU_WLES16` - writes a signed 16-bit integer to little-endian byte data; overridable macro to `muu_wles16`.

* `MU_RBEU16` - reads an unsigned 16-bit integer from big-endian byte data; overridable macro to `muu_rbeu16`.

* `MU_WBEU16` - writes an unsigned 16-bit integer to big-endian byte data; overridable macro to `muu_wbeu16`.

* `MU_RBES16` - reads a signed 16-bit integer from big-endian byte data; overridable macro to `muu_rbes16`.

* `MU_WBES16` - writes a signed 16-bit integer to big-endian byte data; overridable macro to `muu_wbes16`.

## 24-bit

The following macros exist for byte manipulation regarding 24-bit integers:

* `MU_RLEU24` - reads an unsigned 24-bit integer from little-endian byte data; overridable macro to `muu_rleu24`.

* `MU_WLEU24` - writes an unsigned 24-bit integer to little-endian byte data; overridable macro to `muu_wleu24`.

* `MU_RLES24` - reads a signed 24-bit integer from little-endian byte data; overridable macro to `muu_rles24`.

* `MU_WLES24` - writes a signed 24-bit integer to little-endian byte data; overridable macro to `muu_wles24`.

* `MU_RBEU24` - reads an unsigned 24-bit integer from big-endian byte data; overridable macro to `muu_rbeu24`.

* `MU_WBEU24` - writes an unsigned 24-bit integer to big-endian byte data; overridable macro to `muu_wbeu24`.

* `MU_RBES24` - reads a signed 24-bit integer from big-endian byte data; overridable macro to `muu_rbes24`.

* `MU_WBES24` - writes a signed 24-bit integer to big-endian byte data; overridable macro to `muu_wbes24`.

## 32-bit

The following macros exist for byte manipulation regarding 32-bit integers:

* `MU_RLEU32` - reads an unsigned 32-bit integer from little-endian byte data; overridable macro to `muu_rleu32`.

* `MU_WLEU32` - writes an unsigned 32-bit integer to little-endian byte data; overridable macro to `muu_wleu32`.

* `MU_RLES32` - reads a signed 32-bit integer from little-endian byte data; overridable macro to `muu_rles32`.

* `MU_WLES32` - writes a signed 32-bit integer to little-endian byte data; overridable macro to `muu_wles32`.

* `MU_RBEU32` - reads an unsigned 32-bit integer from big-endian byte data; overridable macro to `muu_rbeu32`.

* `MU_WBEU32` - writes an unsigned 32-bit integer to big-endian byte data; overridable macro to `muu_wbeu32`.

* `MU_RBES32` - reads a signed 32-bit integer from big-endian byte data; overridable macro to `muu_rbes32`.

* `MU_WBES32` - writes a signed 32-bit integer to big-endian byte data; overridable macro to `muu_wbes32`.

## 64-bit

The following macros exist for byte manipulation regarding 64-bit integers:

* `MU_RLEU64` - reads an unsigned 64-bit integer from little-endian byte data; overridable macro to `muu_rleu64`.

* `MU_WLEU64` - writes an unsigned 64-bit integer to little-endian byte data; overridable macro to `muu_wleu64`.

* `MU_RLES64` - reads a signed 64-bit integer from little-endian byte data; overridable macro to `muu_rles64`.

* `MU_WLES64` - writes a signed 64-bit integer to little-endian byte data; overridable macro to `muu_wles64`.

* `MU_RBEU64` - reads an unsigned 64-bit integer from big-endian byte data; overridable macro to `muu_rbeu64`.

* `MU_WBEU64` - writes an unsigned 64-bit integer to big-endian byte data; overridable macro to `muu_wbeu64`.

* `MU_RBES64` - reads a signed 64-bit integer from big-endian byte data; overridable macro to `muu_rbes64`.

* `MU_WBES64` - writes a signed 64-bit integer to big-endian byte data; overridable macro to `muu_wbes64`.

# Set result


The `MU_SET_RESULT(res, val)` macro is an overridable function that checks if the given parameter `res` is a null pointer. If it is, it does nothing, but if it isn't, it dereferences the pointer and sets the value to `val`. This macro saves a lot of code, shrinking down what would be this:

```c
if (result != MU_NULL_PTR) {
*result = ...;
}
```

into this:

```c
MU_SET_RESULT(result, ...)
```


# Enum


The `MU_ENUM(name, ...)` macro is an overridable function used to declare an enumerator. `name` is the name of the enumerator type, and `...` are all of the values. The reason why one would prefer this over the traditional way of declaring enumerators is because it actually makes it a `size_m`, which can avoid errors on certain compilers (looking at you, Microsoft) in regards to treating enumerators like values. It expands like this:

```c
enum _##name {
__VA_ARGS__
};
typedef enum _##name _##name;
typedef size_m name;
```


# Operating system recognition


The macros `MU_WIN32` or `MU_LINUX` are defined (if neither were defined before) in order to allow mu libraries to easily check if they're running on a Windows or Linux system.

`MU_WIN32` will be defined if `WIN32` or `_WIN32` are defined, one of which is usually pre-defined on Windows systems.

`MU_LINUX` will be defined if `__linux__` is defined.

