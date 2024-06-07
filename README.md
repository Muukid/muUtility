
# muUtility v1.1.1

muUtility (acrynomized to muu) is a public domain header-only single-file C utility library used by most mu libraries. To use it, download the `muUtility.h` file, add it to your include path, and include it like so:

```c
#define MUU_IMPLEMENTATION
#include "muUtility.h"
```

More information about the general structure of a mu library is provided at [the mu library information GitHub repository.](https://github.com/Muukid/mu-library-information)

# Licensing

muUtility is licensed under public domain or MIT license, whichever you prefer. More information is provided in the accompanying file `license.md` and at the bottom of `muUtility.h`.

# Other library dependencies

muUtility has no dependencies on any other libraries.


# Secure warnings

mu libraries often use non-secure functions that will trigger warnings on certain compilers. These warnings are, to put it lightly, dumb, so the header section of muUtility defines `_CRT_SECURE_NO_WARNINGS`. However, it is not guaranteed that this definition will actually turn the warnings off, which at that point, they have to be manually turned off by the user.

# C standard library dependencies

muUtility has several C standard library dependencies, all of which are overridable by defining them before the inclusion of its header. The following is a list of those dependencies:

## `stdint.h` dependencies

`int8_m`: equivalent to `int8_t` if `INT8_MAX` is defined, `char` if otherwise

`uint8_m`: equivalent to `uint8_t` if `UINT8_MAX` is defined, `unsigned char` if otherwise

`int16_m`: equivalent to `int16_t` if `INT16_MAX` is defined, `short` if otherwise

`uint16_m`: equivalent to `uint16_t` if `UINT16_MAX` is defined, `unsigned short` if otherwise

`int32_m`: equivalent to `int32_t` if `INT32_MAX` is defined, `long` if otherwise

`uint32_m`: equivalent to `uint32_t` if `UINT32_MAX` is defined, `unsigned long` if otherwise

`int64_m`: equivalent to `int64_t` if `INT64_MAX` is defined, `long long` if otherwise

`uint64_m`: equivalent to `uint64_t` if `UINT64_MAX` is defined, `unsigned long long` if otherwise

`MU_SIZE_MAX`: equivalent to `SIZE_MAX`

## `stddef.h` dependencies

`size_m`: equivalent to `size_t`

## `stdbool.h` dependencies

`muBool`: equivalent to `bool`

`MU_TRUE`: equivalent to `true`

`MU_FALSE`: equivalent to `false`

# Macros

## Version

The macros `MUU_VERSION_MAJOR`, `MUU_VERSION_MINOR`, and `MUU_VERSION_PATCH` are defined to match its respective release version, following the formatting of `MAJOR.MINOR.PATCH`.

## `MUDEF`

The `MUDEF` macro is a macro used by virtually all mu libraries, which is generally added before a header-defined variable or function. Its default value is `extern`, but can be changed to `static` by defining `MU_STATIC` before the header section of muUtility is defined. Its value can also be overwritten entirely to anything else by directly defining `MUDEF`.

## Zero struct

There are two macros, `MU_ZERO_STRUCT` and `MU_ZERO_STRUCT_CONST`, which are macro functions used to zero-out a struct's contents, with their only parameter being the struct type. The reason this needs to be defined is because the way C and C++ syntax handles an empty struct are different, and need to be adjusted for.

## Byte

Several macros are defined to interact with the idea of a byte.

The macro `muByte` exists as a macro for `uint8_m`, and represents a byte as a type.

There are also several macro functions used to read and write to bytes. These macros are:

`mu_rle_uint8(b)`: Creates an expression of type `uint8_m` that reads the value stored in the 1-byte-length little-endian byte array `b`.

`mu_rbe_uint8(b)`: Creates an expression of type `uint8_m` that reads the value stored in the 1-byte-length big-endian byte array `b`.

`mu_rle_uint16(b)`: Creates an expression of type `uint16_m` that reads the value stored in the 2-byte-length little-endian byte array `b`.

`mu_rbe_uint16(b)`: Creates an expression of type `uint16_m` that reads the value stored in the 2-byte-length big-endian byte array `b`.

`mu_rle_uint32(b)`: Creates an expression of type `uint32_m` that reads the value stored in the 4-byte-length little-endian byte array `b`.

`mu_rbe_uint32(b)`: Creates an expression of type `uint32_m` that reads the value stored in the 4-byte-length big-endian byte array `b`.

`mu_rle_uint64(b)`: Creates an expression of type `uint64_m` that reads the value stored in the 8-byte-length little-endian byte array `b`.

`mu_rbe_uint64(b)`: Creates an expression of type `uint64_m` that reads the value stored in the 8-byte-length big-endian byte array `b`.

`mu_wle_uint8(b, i)`: Writes the contents of the given `uint8_m` variable `i` into the 1-byte-length little-endian byte array `b`.

`mu_wbe_uint8(b, i)`: Writes the contents of the given `uint8_m` variable `i` into the 1-byte-length big-endian byte array `b`.

`mu_wle_uint16(b, i)`: Writes the contents of the given `uint16_m` variable `i` into the 2-byte-length little-endian byte array `b`.

`mu_wbe_uint16(b, i)`: Writes the contents of the given `uint16_m` variable `i` into the 2-byte-length big-endian byte array `b`.

`mu_wle_uint32(b, i)`: Writes the contents of the given `uint32_m` variable `i` into the 4-byte-length little-endian byte array `b`.

`mu_wbe_uint32(b, i)`: Writes the contents of the given `uint32_m` variable `i` into the 4-byte-length big-endian byte array `b`.

`mu_wle_uint64(b, i)`: Writes the contents of the given `uint64_m` variable `i` into the 8-byte-length little-endian byte array `b`.

`mu_wbe_uint64(b, i)`: Writes the contents of the given `uint64_m` variable `i` into the 8-byte-length big-endian byte array `b`.

## Null values

The `MU_NULL_PTR` macro is a macro value used to represent a null pointer. It is simply 0.

The `MU_NULL` macro is a macro value used to represent a null value. It is simply 0.

## Set result
The `MU_SET_RESULT(res, val)` macro is a macro function that checks if the given parameter `res` is a null pointer. If it is, it does nothing, but if it isn't, it sets its value to the given parameter `val`. This macro saves a lot of code, shrinking down what would be this:

```c
if (result != MU_NULL_PTR) {
    *result = ...;
}
```

into this:

```c
MU_SET_RESULT(result, ...)
```


## Enum


The `MU_ENUM(name, ...)` macro is a macro function used to declare an enumerator. The reason why one would prefer this over the traditional way of declaring enumerators is because it actually makes it a `size_m` which can avoid errors on certain compilers (looking at you, Microsoft) in regards to treating enumerators like values. It expands like this:

```c
enum _##name{
    __VA_ARGS__
};
typedef enum _##name _##name;
typedef size_m name;
```


## Operating system recognition
The macros `MU_WIN32` or `MU_UNIX` are defined (if neither were defined before) in order to allow mu libraries to easily check if they're running on a Windows or Unix system.

`MU_WIN32` will be defined if `WIN32` or `_WIN32` are defined, one of which is usually pre-defined on Windows systems.

`MU_UNIX` will be defined if `__unix__` is defined or both `__APPLE__` and `__MACH__` are defined.

