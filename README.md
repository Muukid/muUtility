# muUtility v1.0.0

muUtility (acrynomized to muu) is a public domain header-only single-file C utility library used by most mu libraries. To use it, download the `muUtility.h` file, add it to your include path, and include it like so:

```
#define MUU_IMPLEMENTATION
#include <muUtility.h>
```

More information about the general structure of a mu library is provided at [the mu library information GitHub repository.](https://github.com/Muukid/mu-library-information)

# Licensing

muUtility is licensed under public domain or MIT license, whichever you prefer. More information is provided in the accompanying file `license.md` and at the bottom of `muUtility.h`.

# Other library dependencies

muUtility has no dependencies on any other libraries.

# General information

## Secure warnings

mu libraries often use non-secure functions that will trigger warnings on certain compilers. These warnings are, to put it lightly, dumb, so the header section of muUtility defines `_CRT_SECURE_NO_WARNINGS`. However, it is not guaranteed that this definition will actually turn the warnings off, which at that point, they have to be manually turned off by the user.

Note that defining `MU_SECURE_WARNINGS` before the header section of muUtility is defined turns this functionality off.

## C standard library dependencies

muUtility has several C standard library dependencies, all of which are overridable by defining them before the inclusion of its header. This is a list of all of those dependencies:

### `stdint.h` dependencies

`int8_m`: equivalent to `int8_t`

`uint8_m`: equivalent to `uint8_t`

`int16_m`: equivalent to `int16_t`

`uint16_m`: equivalent to `uint16_t`

`int32_m`: equivalent to `int32_t`

`uint32_m`: equivalent to `uint32_t`

`int64_m`: equivalent to `int64_t`

`uint64_m`: equivalent to `uint64_t`

`MU_SIZE_MAX`: equivalent to `SIZE_MAX`

### `stddef.h` dependencies

`size_m`: equivalent to `size_t`

### `stdbool.h` dependencies

`muBool`: equivalent to `bool`

`MU_TRUE`: equivalent to `true`

`MU_FALSE`: equivalent to `false`

## Macros

### Version

The macros `MUU_VERSION_MAJOR`, `MUU_VERSION_MINOR`, and `MUU_VERSION_PATCH` are defined to match its respective release version, following the format of:

```
vMAJOR.MINOR.PATCH
```

### `MUDEF`

The `MUDEF` macro is a macro used by virtually all mu libraries, which is generally added before a header-defined variable or function. Its default value is `extern`, but can be changed to `static` by defining `MU_STATIC` before the header section of muUtility is defined. Its value can also be overwritten entirely to anything else by directly defining `MUDEF`.

### `MU_ZERO_STRUCT`

The `MU_ZERO_STRUCT` macro is a macro function used to zero-out a struct's contents, with its only parameter being the name of the struct type. The reason this needs to be defined is because the way C and C++ syntax handles an empty struct are different, and need to be adjusted for.

### `MU_ZERO_STRUCT_CONST`

The `MU_ZERO_STRUCT_CONST` macro is a macro function identical to `MU_ZERO_STRUCT` except for values whose contents need to be determined at compile time, like a global variable.

### `muByte`

The `muByte` macro is a macro type meant to represent a single byte. It is simply a macro for `uint8_m`.

### Byte reading/writing

There are a series of macros used to read and write to bytes numerically. These macros are:

`mu_rle_uint8(b)`: Creates an expression of type `uint8_m` that reads the value stored in the 1-byte-length little-endian byte array `b`.

`mu_rbe_uint8(b)`: Creates an expression of type `uint8_m` that reads the value stored in the 1-byte-length big-endian byte array `b`.

`mu_rle_uint16(b)`: Creates an expression of type `uint16_m` that reads the value stored in the 2-byte-length little-endian byte array `b`.

`mu_rbe_uint16(b)`: Creates an expression of type `uint16_m` that reads the value stored in the 2-byte-length big-endian byte array `b`.

`mu_rle_uint32(b)`: Creates an expression of type `uint32_m` that reads the value stored in the 4-byte-length little-endian byte array `b`.

`mu_rbe_uint32(b)`: Creates an expression of type `uint32_m` that reads the value stored in the 4-byte-length big-endian byte array `b`.

`mu_rle_uint64(b)`: Creates an expression of type `uint64_m` that reads the value stored in the 8-byte-length little-endian byte array `b`.

`mu_rbe_uint64(b)`: Creates an expression of type `uint64_m` that reads the value stored in the 8-byte-length big-endian byte array `b`.

`mu_wle_uint8(b, i)`: Reads the given contents of the 1-byte-length little-endian byte array `b` into the given `uint8_m` variable `i`.

`mu_wbe_uint8(b, i)`: Reads the given contents of the 1-byte-length big-endian byte array `b` into the given `uint8_m` variable `i`.

`mu_wle_uint16(b, i)`: Reads the given contents of the 2-byte-length little-endian byte array `b` into the given `uint16_m` variable `i`.

`mu_wbe_uint16(b, i)`: Reads the given contents of the 2-byte-length big-endian byte array `b` into the given `uint16_m` variable `i`.

`mu_wle_uint32(b, i)`: Reads the given contents of the 4-byte-length little-endian byte array `b` into the given `uint32_m` variable `i`.

`mu_wbe_uint32(b, i)`: Reads the given contents of the 4-byte-length big-endian byte array `b` into the given `uint32_m` variable `i`.

`mu_wle_uint64(b, i)`: Reads the given contents of the 8-byte-length little-endian byte array `b` into the given `uint64_m` variable `i`.

`mu_wbe_uint64(b, i)`: Reads the given contents of the 8-byte-length big-endian byte array `b` into the given `uint64_m` variable `i`.

### `MU_NULL_PTR`

The `MU_NULL_PTR` macro is a macro value used to represent a null pointer. It is simply 0.

### `MU_NULL`

The `MU_NULL` macro is a macro value used to represent a null value. It is simply 0.

### `MU_NONE`

The `MU_NONE` macro is a macro value used to represent nothing. Paradoxically, its value is `MU_SIZE_MAX`, the maximum value that the type `size_m` can hold. This is done so that index reference 0 is still a valid index.

Many mu functions will return this value if an object index reference creation function failed.

### `MU_SET_RESULT`

The `MU_SET_RESULT(res, val)` macro is a macro function that checks if the given parameter `res` is a null pointer. If it is, it does nothing, but if it isn't, it sets its value to the given parameter `val`. This macro saves a lot of code, shrinking down what would be this:

```
if (result != MU_NULL_PTR) {
    *result = ...;
}
```

into this:

```
MU_SET_RESULT(result, ...)
```

### `MU_ASSERT`

The `MU_ASSERT(cond, res, val, after)` macro is a macro function used to make a short assertion statement. It is expanded like this:

```
if (!(cond)) {
    MU_SET_RESULT(res, val)
    after
}
```

### `MU_ENUM`

The `MU_ENUM(name, ...)` macro is a macro function used to declare an enumerator. The reason why one would prefer this over the traditional way of declaring enumerators is because it actually makes it a `size_m` which can avoid errors on certain compilers (looking at you, Microsoft) in regards to treating enumerators like values. It expands like this:

```
enum _##name{
    __VA_ARGS__
};
typedef enum _##name _##name;
typedef size_m name;
```

### Windows / Unix

The macros `MU_WIN32` or `MU_UNIX` are defined (if neither were defined before) in order to allow mu libraries to easily check if they're running on a Windows or Unix system.

`MU_WIN32` will be defined if `WIN32` or `_WIN32` are defined, one of which is usually pre-defined on Windows systems.

`MU_UNIX` will be defined if `__unix__` is defined or both `__APPLE__` and `__MACH__` are defined.

### `MU_HRARRAY_DEFAULT_FUNC`

The macro `MU_HRARRAY_DEFAULT_FUNC(name)` is a macro function that expands to create a hold/release array that automatically integrates a lock/unlock mechanic per element in the array. This is built on the muMemoryAllocator and muMultithreading syntax and is primarily used to quickly create an array whose elements are thread safe.

The only parameter, `name`, is simply the name of the struct being used to represent an element, and is expected to have at least three members:

1. Member `muBool active`.
2. Member `MU_LOCK lock`.
3. Member `muBool lock_active`.

Note that this doesn't mean that muUtility has a direct dependency on muMemoryAllocator or muMultithreading since it's a macro that interfaces with the APIs, one that will only be expanded by another mu library if the libraries have assumably already been added.

### `MU_SAFEFUNC`

The macro `MU_SAFEFUNC(result, lib_prefix, context, fail_return)` is a macro function that expands to do 2 things: ensure that the result parameter is automatically set to successful and that the library's global context has already been initialized. It expands like so:

```
MU_SET_RESULT(result, lib_prefix##SUCCESS)
MU_ASSERT(context != MU_NULL_PTR, result, lib_prefix##NOT_YET_INITIALIZED, fail_return)
```

An example usage would be:

```
MU_SAFEFUNC(result, MUX_, mux_global_context, return 0;)
```

which would expand to:

```
MU_SET_RESULT(result, MUX_SUCCESS)
MU_ASSERT(mux_global_context != MU_NULL_PTR, result, MUX_NOT_YET_INITIALIZED, return 0;)
```

which (for funsies) would expand to:

```
if (result != MU_NULL_PTR) {
    *result = MUX_SUCCESS
}
if (!(mux_global_context != MU_NULL_PTR)) {
    if (result != MU_NULL_PTR) {
        *result = MUX_NOT_YET_INITIALIZED;
    }
    return 0;
}
```

### `MU_HOLD`

The macro `MU_HOLD(result, item, da, context, lib_prefix, fail_return, da_prefix)` is a macro function that expands to hold an element in a hold/release array, and makes thread safe holding very easy without changing the code depending on whether or not `MU_THREADSAFE` has been defined. It expands to:

```
MU_ASSERT(item < da.length, result, lib_prefix##INVALID_ID, fail_return)
da_prefix##hold_element(0, &da, item);
MU_ASSERT(da.data[item].active, result, lib_prefix##INVALID_ID, da_prefix##release_element(0, &da, item); fail_return)
```

An example usage would be:

```
MU_HOLD(result, object, MUX_GOBJECTS, mux_global_context, MUX_, return 0;, mux_object_)
```

which would expand to:

```
MU_ASSERT(object < MUX_GOBJECTS.length, result, MUX_INVALID_ID, return 0;)
mux_object_hold_element(0, &MUX_GOBJECTS, object);
MU_ASSERT(MUX_GOBJECTS.data[object].active, result, MUX_INVALID_ID, mux_object_release_element(0, &MUX_GOBJECTS, item); return 0;)
```

which (for funsies) would expand to:

```
if (!(object < MUX_GOBJECTS.length)) {
    if (result != MU_NULL_PTR) {
        *result = MUX_INVALID_ID;
    }
    return 0;
}
mux_object_hold_element(0, &MUX_GOBJECTS, object);
if (!(MUX_GOBJECTS.data[object].active)) {
    if (result != MU_NULL_PTR) {
        *result = MUX_INVALID_ID;
    }
    mux_object_release_element(0, &MUX_GOBJECTS, item);
    return 0;
}
```

### `MU_RELEASE`

The macro `MU_RELEASE(da, item, da_prefix)` is a macro function used to release an element in a hold/release array. It expands to:

```
da_prefix##release_element(0, &da, item);
```
