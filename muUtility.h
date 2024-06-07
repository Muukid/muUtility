/*
muUtility.h - Muukid
Public domain C utility file used by mu libraries.
No warranty implied; use at your own risk.

Licensed under MIT License or public domain, whichever you prefer.
More explicit license information at the end of file.
*/

/* @DOCBEGIN
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

@DOCEND */

#ifndef MUU_H
	#define MUU_H
	
	// @DOCLINE # Secure warnings
	// @DOCLINE mu libraries often use non-secure functions that will trigger warnings on certain compilers. These warnings are, to put it lightly, dumb, so the header section of muUtility defines `_CRT_SECURE_NO_WARNINGS`. However, it is not guaranteed that this definition will actually turn the warnings off, which at that point, they have to be manually turned off by the user.
	#if !defined(MU_SECURE_WARNINGS) && !defined(_CRT_SECURE_NO_WARNINGS)
		#define _CRT_SECURE_NO_WARNINGS
	#endif

	#ifdef __cplusplus
	extern "C" { // }
	#endif

	// @DOCLINE # C standard library dependencies

		// @DOCLINE muUtility has several C standard library dependencies, all of which are overridable by defining them before the inclusion of its header. The following is a list of those dependencies:

		// @DOCLINE ## `stdint.h` dependencies
		#if !defined(int8_m)      || \
			!defined(uint8_m)     || \
			!defined(int16_m)     || \
			!defined(uint16_m)    || \
			!defined(int32_m)     || \
			!defined(uint32_m)    || \
			!defined(int64_m)     || \
			!defined(uint64_m)    || \
			!defined(MU_SIZE_MAX)

			#define __STDC_LIMIT_MACROS
			#define __STDC_CONSTANT_MACROS
			#include <stdint.h>

			// @DOCLINE `int8_m`: equivalent to `int8_t` if `INT8_MAX` is defined, `char` if otherwise
			#ifndef int8_m
				#ifdef INT8_MAX
					#define int8_m int8_t
				#else
					#define int8_m char
				#endif
			#endif

			// @DOCLINE `uint8_m`: equivalent to `uint8_t` if `UINT8_MAX` is defined, `unsigned char` if otherwise
			#ifndef uint8_m
				#ifdef UINT8_MAX
					#define uint8_m uint8_t
				#else
					#define uint8_m unsigned char
				#endif
			#endif

			// @DOCLINE `int16_m`: equivalent to `int16_t` if `INT16_MAX` is defined, `short` if otherwise
			#ifndef int16_m
				#ifdef INT16_MAX
					#define int16_m int16_t
				#else
					#define int16_m short
				#endif
			#endif

			// @DOCLINE `uint16_m`: equivalent to `uint16_t` if `UINT16_MAX` is defined, `unsigned short` if otherwise
			#ifndef uint16_m
				#ifdef UINT16_MAX
					#define uint16_m uint16_t
				#else
					#define uint16_m unsigned short
				#endif
			#endif

			// @DOCLINE `int32_m`: equivalent to `int32_t` if `INT32_MAX` is defined, `long` if otherwise
			#ifndef int32_m
				#ifdef INT32_MAX
					#define int32_m int32_t
				#else
					#define int32_m long
				#endif
			#endif

			// @DOCLINE `uint32_m`: equivalent to `uint32_t` if `UINT32_MAX` is defined, `unsigned long` if otherwise
			#ifndef uint32_m
				#ifdef UINT32_MAX
					#define uint32_m uint32_t
				#else
					#define uint32_m unsigned long
				#endif
			#endif

			// @DOCLINE `int64_m`: equivalent to `int64_t` if `INT64_MAX` is defined, `long long` if otherwise
			#ifndef int64_m
				#ifdef INT64_MAX
					#define int64_m int64_t
				#else
					#define int64_m long long
				#endif
			#endif

			// @DOCLINE `uint64_m`: equivalent to `uint64_t` if `UINT64_MAX` is defined, `unsigned long long` if otherwise
			#ifndef uint64_m
				#ifdef UINT64_MAX
					#define uint64_m uint64_t
				#else
					#define uint64_m unsigned long long
				#endif
			#endif

			// @DOCLINE `MU_SIZE_MAX`: equivalent to `SIZE_MAX`
			#ifndef MU_SIZE_MAX
				#define MU_SIZE_MAX SIZE_MAX
			#endif

		#endif

		// @DOCLINE ## `stddef.h` dependencies
		#if !defined(size_m)

			#include <stddef.h>

			// @DOCLINE `size_m`: equivalent to `size_t`
			#ifndef size_m
				#define size_m size_t
			#endif

		#endif

		// @DOCLINE ## `stdbool.h` dependencies
		#if !defined(muBool)   || \
			!defined(MU_TRUE)  || \
			!defined(MU_FALSE)

			#include <stdbool.h>

			// @DOCLINE `muBool`: equivalent to `bool`
			#ifndef muBool
				#define muBool bool
			#endif

			// @DOCLINE `MU_TRUE`: equivalent to `true`
			#ifndef MU_TRUE
				#define MU_TRUE true
			#endif

			// @DOCLINE `MU_FALSE`: equivalent to `false`
			#ifndef MU_FALSE
				#define MU_FALSE false
			#endif

		#endif

	// @DOCLINE # Macros

		// @DOCLINE ## Version

			// @DOCLINE The macros `MUU_VERSION_MAJOR`, `MUU_VERSION_MINOR`, and `MUU_VERSION_PATCH` are defined to match its respective release version, following the formatting of `MAJOR.MINOR.PATCH`.

			#define MUU_VERSION_MAJOR 1
			#define MUU_VERSION_MINOR 1
			#define MUU_VERSION_PATCH 1

		// @DOCLINE ## `MUDEF`

			// @DOCLINE The `MUDEF` macro is a macro used by virtually all mu libraries, which is generally added before a header-defined variable or function. Its default value is `extern`, but can be changed to `static` by defining `MU_STATIC` before the header section of muUtility is defined. Its value can also be overwritten entirely to anything else by directly defining `MUDEF`.

			#ifndef MUDEF
				#ifdef MU_STATIC
					#define MUDEF static
				#else
					#define MUDEF extern
				#endif
			#endif

		// @DOCLINE ## Zero struct

			// @DOCLINE There are two macros, `MU_ZERO_STRUCT` and `MU_ZERO_STRUCT_CONST`, which are macro functions used to zero-out a struct's contents, with their only parameter being the struct type. The reason this needs to be defined is because the way C and C++ syntax handles an empty struct are different, and need to be adjusted for.

			#ifndef MU_ZERO_STRUCT
				#ifdef __cplusplus
					#define MU_ZERO_STRUCT(s) {}
				#else
					#define MU_ZERO_STRUCT(s) (s){0}
				#endif
			#endif

			#ifndef MU_ZERO_STRUCT_CONST
				#ifdef __cplusplus
					#define MU_ZERO_STRUCT_CONST(s) {}
				#else
					#define MU_ZERO_STRUCT_CONST(s) {0}
				#endif
			#endif

		// @DOCLINE ## Byte

			// @DOCLINE Several macros are defined to interact with the idea of a byte.

			// @DOCLINE The macro `muByte` exists as a macro for `uint8_m`, and represents a byte as a type.

			#ifndef muByte
				#define muByte uint8_m
			#endif

			// @DOCLINE There are also several macro functions used to read and write to bytes. These macros are:

			// @DOCLINE `mu_rle_uint8(b)`: Creates an expression of type `uint8_m` that reads the value stored in the 1-byte-length little-endian byte array `b`.
			#ifndef mu_rle_uint8
				#define mu_rle_uint8(b) ((uint8_m)b[0] << 0)
			#endif
			// @DOCLINE `mu_rbe_uint8(b)`: Creates an expression of type `uint8_m` that reads the value stored in the 1-byte-length big-endian byte array `b`.
			#ifndef mu_rbe_uint8
				#define mu_rbe_uint8(b) ((uint8_m)b[0] << 0)
			#endif

			// @DOCLINE `mu_rle_uint16(b)`: Creates an expression of type `uint16_m` that reads the value stored in the 2-byte-length little-endian byte array `b`.
			#ifndef mu_rle_uint16
				#define mu_rle_uint16(b) ((uint16_m)b[0] << 0 | (uint16_m)b[1] << 8)
			#endif
			// @DOCLINE `mu_rbe_uint16(b)`: Creates an expression of type `uint16_m` that reads the value stored in the 2-byte-length big-endian byte array `b`.
			#ifndef mu_rbe_uint16
				#define mu_rbe_uint16(b) ((uint16_m)b[1] << 0 | (uint16_m)b[0] << 8)
			#endif

			// @DOCLINE `mu_rle_uint32(b)`: Creates an expression of type `uint32_m` that reads the value stored in the 4-byte-length little-endian byte array `b`.
			#ifndef mu_rle_uint32
				#define mu_rle_uint32(b) ((uint32_m)b[0] << 0 | (uint32_m)b[1] << 8 | (uint32_m)b[2] << 16 | (uint32_m)b[3] << 24)
			#endif
			// @DOCLINE `mu_rbe_uint32(b)`: Creates an expression of type `uint32_m` that reads the value stored in the 4-byte-length big-endian byte array `b`.
			#ifndef mu_rbe_uint32
				#define mu_rbe_uint32(b) ((uint32_m)b[3] << 0 | (uint32_m)b[2] << 8 | (uint32_m)b[1] << 16 | (uint32_m)b[0] << 24)
			#endif

			// @DOCLINE `mu_rle_uint64(b)`: Creates an expression of type `uint64_m` that reads the value stored in the 8-byte-length little-endian byte array `b`.
			#ifndef mu_rle_uint64
				#define mu_rle_uint64(b) ((uint64_m)b[0] << 0 | (uint64_m)b[1] << 8 | (uint64_m)b[2] << 16 | (uint64_m)b[3] << 24 | (uint64_m)b[4] << 32 | (uint64_m)b[5] << 40 | (uint64_m)b[6] << 48 | (uint64_m)b[7] << 56)
			#endif
			// @DOCLINE `mu_rbe_uint64(b)`: Creates an expression of type `uint64_m` that reads the value stored in the 8-byte-length big-endian byte array `b`.
			#ifndef mu_rbe_uint64
				#define mu_rbe_uint64(b) ((uint64_m)b[7] << 0 | (uint64_m)b[6] << 8 | (uint64_m)b[5] << 16 | (uint64_m)b[4] << 24 | (uint64_m)b[3] << 32 | (uint64_m)b[2] << 40 | (uint64_m)b[1] << 48 | (uint64_m)b[0] << 56)
			#endif

			// @DOCLINE `mu_wle_uint8(b, i)`: Writes the contents of the given `uint8_m` variable `i` into the 1-byte-length little-endian byte array `b`.
			#ifndef mu_wle_uint8
				#define mu_wle_uint8(b, i) b[0] = (uint8_m)(i >> 0);
			#endif
			// @DOCLINE `mu_wbe_uint8(b, i)`: Writes the contents of the given `uint8_m` variable `i` into the 1-byte-length big-endian byte array `b`.
			#ifndef mu_wbe_uint8
				#define mu_wbe_uint8(b, i) b[0] = (uint8_m)(i >> 0);
			#endif

			// @DOCLINE `mu_wle_uint16(b, i)`: Writes the contents of the given `uint16_m` variable `i` into the 2-byte-length little-endian byte array `b`.
			#ifndef mu_wle_uint16
				#define mu_wle_uint16(b, i) b[0] = (uint8_m)(i >> 0); b[1] = (uint8_m)(i >> 8);
			#endif
			// @DOCLINE `mu_wbe_uint16(b, i)`: Writes the contents of the given `uint16_m` variable `i` into the 2-byte-length big-endian byte array `b`.
			#ifndef mu_wbe_uint16
				#define mu_wbe_uint16(b, i) b[1] = (uint8_m)(i >> 0); b[0] = (uint8_m)(i >> 8);
			#endif

			// @DOCLINE `mu_wle_uint32(b, i)`: Writes the contents of the given `uint32_m` variable `i` into the 4-byte-length little-endian byte array `b`.
			#ifndef mu_wle_uint32
				#define mu_wle_uint32(b, i) b[0] = (uint8_m)(i >> 0); b[1] = (uint8_m)(i >> 8); b[2] = (uint8_m)(i >> 16); b[3] = (uint8_m)(i >> 24);
			#endif
			// @DOCLINE `mu_wbe_uint32(b, i)`: Writes the contents of the given `uint32_m` variable `i` into the 4-byte-length big-endian byte array `b`.
			#ifndef mu_wbe_uint32
				#define mu_wbe_uint32(b, i) b[3] = (uint8_m)(i >> 0); b[2] = (uint8_m)(i >> 8); b[1] = (uint8_m)(i >> 16); b[0] = (uint8_m)(i >> 24);
			#endif

			// @DOCLINE `mu_wle_uint64(b, i)`: Writes the contents of the given `uint64_m` variable `i` into the 8-byte-length little-endian byte array `b`.
			#ifndef mu_wle_uint64
				#define mu_wle_uint64(b, i) b[0] = (uint8_m)(i >> 0); b[1] = (uint8_m)(i >> 8); b[2] = (uint8_m)(i >> 16); b[3] = (uint8_m)(i >> 24); b[4] = (uint8_m)(i >> 32); b[5] = (uint8_m)(i >> 40); b[6] = (uint8_m)(i >> 48); b[7] = (uint8_m)(i >> 56);
			#endif
			// @DOCLINE `mu_wbe_uint64(b, i)`: Writes the contents of the given `uint64_m` variable `i` into the 8-byte-length big-endian byte array `b`.
			#ifndef mu_wbe_uint64
				#define mu_wbe_uint64(b, i) b[7] = (uint8_m)(i >> 0); b[6] = (uint8_m)(i >> 8); b[5] = (uint8_m)(i >> 16); b[4] = (uint8_m)(i >> 24); b[3] = (uint8_m)(i >> 32); b[2] = (uint8_m)(i >> 40); b[1] = (uint8_m)(i >> 48); b[0] = (uint8_m)(i >> 56);
			#endif

		// @DOCLINE ## Null values

			// @DOCLINE The `MU_NULL_PTR` macro is a macro value used to represent a null pointer. It is simply 0.
			#ifndef MU_NULL_PTR
				#define MU_NULL_PTR 0
			#endif

			// @DOCLINE The `MU_NULL` macro is a macro value used to represent a null value. It is simply 0.
			#ifndef MU_NULL
				#define MU_NULL 0
			#endif

		// @DOCLINE ## Set result

			/* @DOCBEGIN The `MU_SET_RESULT(res, val)` macro is a macro function that checks if the given parameter `res` is a null pointer. If it is, it does nothing, but if it isn't, it sets its value to the given parameter `val`. This macro saves a lot of code, shrinking down what would be this:

			```c
			if (result != MU_NULL_PTR) {
			    *result = ...;
			}
			```

			into this:
			
			```c
			MU_SET_RESULT(result, ...)
			```

			@DOCEND */

			#ifndef MU_SET_RESULT
				#define MU_SET_RESULT(res, val) if(res!=MU_NULL_PTR){*res=val;}
			#endif

		// @DOCLINE ## Enum

			/* @DOCBEGIN

			The `MU_ENUM(name, ...)` macro is a macro function used to declare an enumerator. The reason why one would prefer this over the traditional way of declaring enumerators is because it actually makes it a `size_m` which can avoid errors on certain compilers (looking at you, Microsoft) in regards to treating enumerators like values. It expands like this:

			```c
			enum _##name{
			    __VA_ARGS__
			};
			typedef enum _##name _##name;
			typedef size_m name;
			```

			@DOCEND */

			#define MU_ENUM(name, ...) enum _##name{__VA_ARGS__};typedef enum _##name _##name; typedef size_m name;

		// @DOCLINE ## Operating system recognition

			/* @DOCBEGIN The macros `MU_WIN32` or `MU_UNIX` are defined (if neither were defined before) in order to allow mu libraries to easily check if they're running on a Windows or Unix system.

			`MU_WIN32` will be defined if `WIN32` or `_WIN32` are defined, one of which is usually pre-defined on Windows systems.

			`MU_UNIX` will be defined if `__unix__` is defined or both `__APPLE__` and `__MACH__` are defined.

			@DOCEND */

			#if !defined(MU_WIN32) && !defined(MU_UNIX)
				#if defined(WIN32) || defined(_WIN32)
					#define MU_WIN32
				#elif defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
					#define MU_UNIX
				#endif
			#endif

	#ifdef __cplusplus
	}
	#endif

#endif /* MUU_H */


#ifdef MUU_IMPLEMENTATION
	
	// ...

#endif /* MUU_IMPLEMENTATION */

/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2024 Hum
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/

