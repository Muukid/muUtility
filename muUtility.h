/*
muUtility.h - Muukid
Public domain C utility file used by mu libraries.
No warranty implied; use at your own risk.

Licensed under MIT license or public domain; whichever you prefer.
More explicit license information at the end of file.
*/

/* @DOCBEGIN

# muUtility v2.0.1

muUtility (acrynomized to muu) is a public domain single-file single-header C utility library with no dependencies used by most mu libraries. It contains a collection of definitions and functions within a header wrapper (`MUU_H`) that is automatically defined if it is not defined already.

More information about mu libraries in general can be found at [the mu library information GitHub repository](https://github.com/Muukid/mu-library-information).

# Licensing

muUtility is licensed under public domain or MIT license, whichever you prefer. More information is provided in the accompanying file `license.md` and at the bottom of `muUtility.h`.

@DOCEND */

#ifndef MUU_H
	#define MUU_H

	// @DOCLINE # Version
		// @DOCLINE The macros `MUU_VERSION_MAJOR`, `MUU_VERSION_MINOR`, and `MUU_VERSION_PATCH` are defined to match its respective release version, following the formatting of `MAJOR.MINOR.PATCH`.
		
		#define MUU_VERSION_MAJOR 2
		#define MUU_VERSION_MINOR 0
		#define MUU_VERSION_PATCH 1

	// @DOCLINE # `MUDEF`
		// @DOCLINE The `MUDEF` macro is used by virtually all mu libraries, and is generally added before a header-defined variable or function. Its default value is `extern`, but can be changed to `static` by defining `MU_STATIC` before the header section of muUtility is defined. Its value can also be overwritten entirely to anything else by directly defining `MUDEF`.
		
		#ifndef MUDEF
			#ifdef MU_STATIC
				#define MUDEF static
			#else
				#define MUDEF extern
			#endif
		#endif
	
	// @DOCLINE # Secure warnings
		// @DOCLINE mu libraries often use non-secure functions that will trigger warnings on certain compilers. These warnings are, to put it lightly, dumb, so muUtility defines `_CRT_SECURE_NO_WARNINGS`. However, it is not guaranteed that this definition will actually turn the warnings off, which, at that point, they have to be manually turned off by the user. This functionality can be turned off by defining `MU_SECURE_WARNINGS`.
		#if !defined(MU_SECURE_WARNINGS) && !defined(_CRT_SECURE_NO_WARNINGS)
			#define _CRT_SECURE_NO_WARNINGS
		#endif
	
	// @DOCLINE # C++ extern
		// @DOCLINE Every mu library's primary code externs "C" within the main chunks of their code; macros `MU_CPP_EXTERN_START` and `MU_CPP_EXTERN_END` are defined to make this process easier, and would read like this:
		/* @DOCBEGIN
		```
		MU_CPP_EXTERN_START

		// Library code goes here...

		MU_CPP_EXTERN_END
		```
		@DOCEND */
		#ifdef __cplusplus
			#define MU_CPP_EXTERN_START extern "C" {
			#define MU_CPP_EXTERN_END   }
		#else
			#define MU_CPP_EXTERN_START
			#define MU_CPP_EXTERN_END
		#endif
	
	MU_CPP_EXTERN_START

	// @DOCLINE # C standard library dependencies

		// @DOCLINE muUtility has several C standard library dependencies, all of which are overridable by defining them before the inclusion of the file. The following is a list of those dependencies.

		// @DOCLINE ## `stdint.h` dependencies
		#if !defined(int8_m) || \
			!defined(uint8_m) || \
			!defined(int16_m) || \
			!defined(uint16_m) || \
			!defined(int32_m) || \
			!defined(uint32_m) || \
			!defined(int64_m) || \
			!defined(uint64_m) || \
			!defined(MU_SIZE_MAX)

			#define __STDC_LIMIT_MACROS
			#define __STDC_CONSTANT_MACROS
			#include <stdint.h>
			
			// @DOCLINE * `int8_m` - equivalent to `int8_t` if `INT8_MAX` is defined; `char` if otherwise.
			#ifndef int8_m
				#ifdef INT8_MAX
					#define int8_m int8_t
				#else
					#define int8_m char
				#endif
			#endif

			// @DOCLINE * `uint8_m` - equivalent to `uint8_t` if `UINT8_MAX` is defined; `unsigned char` if otherwise.
			#ifndef uint8_m
				#ifdef UINT8_MAX
					#define uint8_m uint8_t
				#else
					#define uint8_m unsigned char
				#endif
			#endif

			// @DOCLINE * `int16_m` - equivalent to `int16_t` if `INT16_MAX` is defined; `short` if otherwise.
			#ifndef int16_m
				#ifdef INT16_MAX
					#define int16_m int16_t
				#else
					#define int16_m short
				#endif
			#endif

			// @DOCLINE * `uint16_m` - equivalent to `uint16_t` if `UINT16_MAX` is defined; `unsigned short` if otherwise.
			#ifndef uint16_m
				#ifdef UINT16_MAX
					#define uint16_m uint16_t
				#else
					#define uint16_m unsigned short
				#endif
			#endif

			// @DOCLINE * `int32_m` - equivalent to `int32_t` if `INT32_MAX` is defined; `long` if otherwise.
			#ifndef int32_m
				#ifdef INT32_MAX
					#define int32_m int32_t
				#else
					#define int32_m long
				#endif
			#endif

			// @DOCLINE * `uint32_m` - equivalent to `uint32_t` if `UINT32_MAX` is defined; `unsigned long` if otherwise.
			#ifndef uint32_m
				#ifdef UINT32_MAX
					#define uint32_m uint32_t
				#else
					#define uint32_m unsigned long
				#endif
			#endif

			// @DOCLINE * `int64_m` - equivalent to `int64_t` if `INT64_MAX` is defined; `long long` if otherwise.
			#ifndef int64_m
				#ifdef INT64_MAX
					#define int64_m int64_t
				#else
					#define int64_m long long
				#endif
			#endif

			// @DOCLINE * `uint64_m` - equivalent to `uint64_t` if `UINT64_MAX` is defined; `unsigned long long` if otherwise.
			#ifndef uint64_m
				#ifdef UINT64_MAX
					#define uint64_m uint64_t
				#else
					#define uint64_m unsigned long long
				#endif
			#endif

			// @DOCLINE * `MU_SIZE_MAX` - equivalent to `SIZE_MAX`.
			#ifndef MU_SIZE_MAX
				#define MU_SIZE_MAX SIZE_MAX
			#endif

		#endif /* stdint.h */

		// @DOCLINE ## `stddef.h` dependencies
		#if !defined(size_m)

			#include <stddef.h>

			// @DOCLINE * `size_m` - equivalent to `size_t`.
			#ifndef size_m
				#define size_m size_t
			#endif

		#endif /* stddef.h */

		// @DOCLINE ## `stdbool.h` dependencies
		#if !defined(muBool) || \
			!defined(MU_TRUE) || \
			!defined(MU_FALSE)

			#include <stdbool.h>

			// @DOCLINE * `muBool` - equivalent to `bool`.
			#ifndef muBool
				#define muBool bool
			#endif

			// @DOCLINE * `MU_TRUE` - equivalent to `true`.
			#ifndef MU_TRUE
				#define MU_TRUE true
			#endif

			// @DOCLINE * `MU_FALSE` - equivalent to `false`.
			#ifndef MU_FALSE
				#define MU_FALSE false
			#endif

		#endif /* stdbool.h */

	// @DOCLINE # Zero struct

		// @DOCLINE There are two macros, `MU_ZERO_STRUCT` and `MU_ZERO_STRUCT_CONST`, which are functions used to zero-out a struct's contents, with their only parameter being the struct type. The reason this needs to be defined is because the way C and C++ syntax handles an empty struct are different, and need to be adjusted for. These macros are overridable by defining them before `muUtility.h` is included.

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

	// @DOCLINE # Byte manipulation

		// @DOCLINE muUtility defines several inline functions that read a value from a given array of bytes. Internally, they're all defined with the prefix `muu_...`, and then a macro is defined for them as `MU_...` (with change in capitalization after the prefix as well). The macros for these functions can be overridden, and, in such case, the original function will go undefined. For example, the function `muu_rleu8` is primarily referenced via the macro `MU_RLEU8`, and if `MU_RLEU8` is overridden, `muu_rleu8` is never defined and is not referenceable.

		// @DOCLINE All reading functions take in a pointer of bytes as their only parameter and have a return type of the fixed-width size of bits in question; for example, `muu_rleu8` is defined as:

		/* @DOCBEGIN
		```
		MUDEF inline uint8_m muu_rleu8(muByte* b);
		```
		@DOCEND */

		// @DOCLINE All writing functions take in a pointer of bytes as their first parameter, the number to be written as the second parameter, and have a return type of void; for example, `muu_wleu8` is defined as:

		/* @DOCBEGIN
		```
		MUDEF inline void muu_wleu8(muByte* b, uint8_m n);
		```
		@DOCEND */

		// @DOCLINE The exception to this is 24-bit, in which case, the fixed-width types are 32-bit (`uint32_m` / `int32_m`).

		// @DOCLINE ## Byte type

			// @DOCLINE muUtility defines the type `muByte` to refer to a byte. It is defined as `uint8_m`, and is overridable.
			#ifndef muByte
				#define muByte uint8_m
			#endif

		// @DOCLINE ## 8-bit

			// @DOCLINE The following macros exist for byte manipulation regarding 8-bit integers:

			// @DOCLINE * `MU_RLEU8` - reads an unsigned 8-bit integer from little-endian byte data; overridable macro to `muu_rleu8`.
			#ifndef MU_RLEU8
				MUDEF inline uint8_m muu_rleu8(muByte* b) {
					return b[0];
				}
				#define MU_RLEU8 muu_rleu8
			#endif

			// @DOCLINE * `MU_WLEU8` - writes an unsigned 8-bit integer to little-endian byte data; overridable macro to `muu_wleu8`.
			#ifndef MU_WLEU8
				MUDEF inline void muu_wleu8(muByte* b, uint8_m n) {
					b[0] = n;
				}
				#define MU_WLEU8 muu_wleu8
			#endif

			// @DOCLINE * `MU_RLES8` - reads a signed 8-bit integer from little-endian byte data; overridable macro to `muu_rles8`.
			#ifndef MU_RLES8
				MUDEF inline int8_m muu_rles8(muByte* b) {
					// I'm PRETTY sure this is okay...
					return *(int8_m*)b;
				}
				#define MU_RLES8 muu_rles8
			#endif

			// @DOCLINE * `MU_WLES8` - writes a signed 8-bit integer to little-endian byte data; overridable macro to `muu_wles8`.
			#ifndef MU_WLES8
				MUDEF inline void muu_wles8(muByte* b, int8_m n) {
					((int8_m*)(b))[0] = n;
				}
				#define MU_WLES8 muu_wles8
			#endif

			// @DOCLINE * `MU_RBEU8` - reads an unsigned 8-bit integer from big-endian byte data; overridable macro to `muu_rbeu8`.
			#ifndef MU_RBEU8
				MUDEF inline uint8_m muu_rbeu8(muByte* b) {
					return b[0];
				}
				#define MU_RBEU8 muu_rbeu8
			#endif

			// @DOCLINE * `MU_WBEU8` - writes an unsigned 8-bit integer to big-endian byte data; overridable macro to `muu_wbeu8`.
			#ifndef MU_WBEU8
				MUDEF inline void muu_wbeu8(muByte* b, uint8_m n) {
					b[0] = n;
				}
				#define MU_WBEU8 muu_wbeu8
			#endif

			// @DOCLINE * `MU_RBES8` - reads a signed 8-bit integer from big-endian byte data; overridable macro to `muu_rbes8`.
			#ifndef MU_RBES8
				MUDEF inline int8_m muu_rbes8(muByte* b) {
					return *(int8_m*)b;
				}
				#define MU_RBES8 muu_rbes8
			#endif

			// @DOCLINE * `MU_WBES8` - writes a signed 8-bit integer to big-endian byte data; overridable macro to `muu_wbes8`.
			#ifndef MU_WBES8
				MUDEF inline void muu_wbes8(muByte* b, int8_m n) {
					((int8_m*)(b))[0] = n;
				}
				#define MU_WBES8 muu_wbes8
			#endif

		// @DOCLINE ## 16-bit

			// @DOCLINE The following macros exist for byte manipulation regarding 16-bit integers:

			// @DOCLINE * `MU_RLEU16` - reads an unsigned 16-bit integer from little-endian byte data; overridable macro to `muu_rleu16`.
			#ifndef MU_RLEU16
				MUDEF inline uint16_m muu_rleu16(muByte* b) {
					return (
						((uint16_m)(b[0]) << 0) |
						((uint16_m)(b[1]) << 8)
					);
				}
				#define MU_RLEU16 muu_rleu16
			#endif

			// @DOCLINE * `MU_WLEU16` - writes an unsigned 16-bit integer to little-endian byte data; overridable macro to `muu_wleu16`.
			#ifndef MU_WLEU16
				MUDEF inline void muu_wleu16(muByte* b, uint16_m n) {
					b[0] = (uint8_m)(n >> 0);
					b[1] = (uint8_m)(n >> 8);
				}
				#define MU_WLEU16 muu_wleu16
			#endif

			// @DOCLINE * `MU_RLES16` - reads a signed 16-bit integer from little-endian byte data; overridable macro to `muu_rles16`.
			#ifndef MU_RLES16
				MUDEF inline int16_m muu_rles16(muByte* b) {
					uint16_m u16 = muu_rleu16(b);
					return *(int16_m*)&u16;
				}
				#define MU_RLES16 muu_rles16
			#endif

			// @DOCLINE * `MU_WLES16` - writes a signed 16-bit integer to little-endian byte data; overridable macro to `muu_wles16`.
			#ifndef MU_WLES16
				MUDEF inline void muu_wles16(muByte* b, int16_m n) {
					uint16_m un = *(uint16_m*)&n;
					b[0] = (uint8_m)(un >> 0);
					b[1] = (uint8_m)(un >> 8);
				}
				#define MU_WLES16 muu_wles16
			#endif

			// @DOCLINE * `MU_RBEU16` - reads an unsigned 16-bit integer from big-endian byte data; overridable macro to `muu_rbeu16`.
			#ifndef MU_RBEU16
				MUDEF inline uint16_m muu_rbeu16(muByte* b) {
					return (
						((uint16_m)(b[1]) << 0) |
						((uint16_m)(b[0]) << 8)
					);
				}
				#define MU_RBEU16 muu_rbeu16
			#endif

			// @DOCLINE * `MU_WBEU16` - writes an unsigned 16-bit integer to big-endian byte data; overridable macro to `muu_wbeu16`.
			#ifndef MU_WBEU16
				MUDEF inline void muu_wbeu16(muByte* b, uint16_m n) {
					b[1] = (uint8_m)(n >> 0);
					b[0] = (uint8_m)(n >> 8);
				}
				#define MU_WBEU16 muu_wbeu16
			#endif

			// @DOCLINE * `MU_RBES16` - reads a signed 16-bit integer from big-endian byte data; overridable macro to `muu_rbes16`.
			#ifndef MU_RBES16
				MUDEF inline int16_m muu_rbes16(muByte* b) {
					uint16_m u16 = muu_rbeu16(b);
					return *(int16_m*)&u16;
				}
				#define MU_RBES16 muu_rbes16
			#endif

			// @DOCLINE * `MU_WBES16` - writes a signed 16-bit integer to big-endian byte data; overridable macro to `muu_wbes16`.
			#ifndef MU_WBES16
				MUDEF inline void muu_wbes16(muByte* b, int16_m n) {
					uint16_m un = *(uint16_m*)&n;
					b[1] = (uint8_m)(un >> 0);
					b[0] = (uint8_m)(un >> 8);
				}
				#define MU_WBES16 muu_wbes16
			#endif

		// @DOCLINE ## 24-bit

			// @DOCLINE The following macros exist for byte manipulation regarding 24-bit integers:

			// @DOCLINE * `MU_RLEU24` - reads an unsigned 24-bit integer from little-endian byte data; overridable macro to `muu_rleu24`.
			#ifndef MU_RLEU24
				MUDEF inline uint32_m muu_rleu24(muByte* b) {
					return (
						((uint32_m)(b[0]) << 0) |
						((uint32_m)(b[1]) << 8) |
						((uint32_m)(b[2]) << 16)
					);
				}
				#define MU_RLEU24 muu_rleu24
			#endif

			// @DOCLINE * `MU_WLEU24` - writes an unsigned 24-bit integer to little-endian byte data; overridable macro to `muu_wleu24`.
			#ifndef MU_WLEU24
				MUDEF inline void muu_wleu24(muByte* b, uint32_m n) {
					b[0] = (uint8_m)(n >> 0);
					b[1] = (uint8_m)(n >> 8);
					b[2] = (uint8_m)(n >> 16);
				}
				#define MU_WLEU24 muu_wleu24
			#endif

			// @DOCLINE * `MU_RLES24` - reads a signed 24-bit integer from little-endian byte data; overridable macro to `muu_rles24`.
			#ifndef MU_RLES24
				MUDEF inline int32_m muu_rles24(muByte* b) {
					uint32_m u24 = muu_rleu24(b);
					return *(int32_m*)&u24;
				}
				#define MU_RLES24 muu_rles24
			#endif

			// @DOCLINE * `MU_WLES24` - writes a signed 24-bit integer to little-endian byte data; overridable macro to `muu_wles24`.
			#ifndef MU_WLES24
				MUDEF inline void muu_wles24(muByte* b, int32_m n) {
					// Probably definitely doesn't work with signed integers; fix later
					uint32_m un = *(uint32_m*)&n;
					b[0] = (uint8_m)(un >> 0);
					b[1] = (uint8_m)(un >> 8);
					b[2] = (uint8_m)(un >> 16);
				}
				#define MU_WLES24 muu_wles24
			#endif

			// @DOCLINE * `MU_RBEU24` - reads an unsigned 24-bit integer from big-endian byte data; overridable macro to `muu_rbeu24`.
			#ifndef MU_RBEU24
				MUDEF inline uint32_m muu_rbeu24(muByte* b) {
					return (
						((uint32_m)(b[2]) << 0) |
						((uint32_m)(b[1]) << 8) |
						((uint32_m)(b[0]) << 16)
					);
				}
				#define MU_RBEU24 muu_rbeu24
			#endif

			// @DOCLINE * `MU_WBEU24` - writes an unsigned 24-bit integer to big-endian byte data; overridable macro to `muu_wbeu24`.
			#ifndef MU_WBEU24
				MUDEF inline void muu_wbeu24(muByte* b, uint32_m n) {
					b[2] = (uint8_m)(n >> 0);
					b[1] = (uint8_m)(n >> 8);
					b[0] = (uint8_m)(n >> 16);
				}
				#define MU_WBEU24 muu_wbeu24
			#endif

			// @DOCLINE * `MU_RBES24` - reads a signed 24-bit integer from big-endian byte data; overridable macro to `muu_rbes24`.
			#ifndef MU_RBES24
				MUDEF inline int32_m muu_rbes24(muByte* b) {
					uint32_m u24 = muu_rbeu24(b);
					return *(int32_m*)&u24;
				}
				#define MU_RBES24 muu_rbes24
			#endif

			// @DOCLINE * `MU_WBES24` - writes a signed 24-bit integer to big-endian byte data; overridable macro to `muu_wbes24`.
			#ifndef MU_WBES24
				MUDEF inline void muu_wbes24(muByte* b, int32_m n) {
					uint32_m un = *(uint32_m*)&n;
					b[2] = (uint8_m)(un >> 0);
					b[1] = (uint8_m)(un >> 8);
					b[0] = (uint8_m)(un >> 16);
				}
				#define MU_WBES24 muu_wbes24
			#endif

		// @DOCLINE ## 32-bit

			// @DOCLINE The following macros exist for byte manipulation regarding 32-bit integers:

			// @DOCLINE * `MU_RLEU32` - reads an unsigned 32-bit integer from little-endian byte data; overridable macro to `muu_rleu32`.
			#ifndef MU_RLEU32
				MUDEF inline uint32_m muu_rleu32(muByte* b) {
					return (
						((uint32_m)(b[0]) << 0)  |
						((uint32_m)(b[1]) << 8)  |
						((uint32_m)(b[2]) << 16) |
						((uint32_m)(b[3]) << 24)
					);
				}
				#define MU_RLEU32 muu_rleu32
			#endif

			// @DOCLINE * `MU_WLEU32` - writes an unsigned 32-bit integer to little-endian byte data; overridable macro to `muu_wleu32`.
			#ifndef MU_WLEU32
				MUDEF inline void muu_wleu32(muByte* b, uint32_m n) {
					b[0] = (uint8_m)(n >> 0);
					b[1] = (uint8_m)(n >> 8);
					b[2] = (uint8_m)(n >> 16);
					b[3] = (uint8_m)(n >> 24);
				}
				#define MU_WLEU32 muu_wleu32
			#endif

			// @DOCLINE * `MU_RLES32` - reads a signed 32-bit integer from little-endian byte data; overridable macro to `muu_rles32`.
			#ifndef MU_RLES32
				MUDEF inline int32_m muu_rles32(muByte* b) {
					uint32_m u32 = muu_rleu32(b);
					return *(int32_m*)&u32;
				}
				#define MU_RLES32 muu_rles32
			#endif

			// @DOCLINE * `MU_WLES32` - writes a signed 32-bit integer to little-endian byte data; overridable macro to `muu_wles32`.
			#ifndef MU_WLES32
				MUDEF inline void muu_wles32(muByte* b, int32_m n) {
					uint32_m un = *(uint32_m*)&n;
					b[0] = (uint8_m)(un >> 0);
					b[1] = (uint8_m)(un >> 8);
					b[2] = (uint8_m)(un >> 16);
					b[3] = (uint8_m)(un >> 24);
				}
				#define MU_WLES32 muu_wles32
			#endif

			// @DOCLINE * `MU_RBEU32` - reads an unsigned 32-bit integer from big-endian byte data; overridable macro to `muu_rbeu32`.
			#ifndef MU_RBEU32
				MUDEF inline uint32_m muu_rbeu32(muByte* b) {
					return (
						((uint32_m)(b[3]) << 0)  |
						((uint32_m)(b[2]) << 8)  |
						((uint32_m)(b[1]) << 16) |
						((uint32_m)(b[0]) << 24)
					);
				}
				#define MU_RBEU32 muu_rbeu32
			#endif

			// @DOCLINE * `MU_WBEU32` - writes an unsigned 32-bit integer to big-endian byte data; overridable macro to `muu_wbeu32`.
			#ifndef MU_WBEU32
				MUDEF inline void muu_wbeu32(muByte* b, uint32_m n) {
					b[3] = (uint8_m)(n >> 0);
					b[2] = (uint8_m)(n >> 8);
					b[1] = (uint8_m)(n >> 16);
					b[0] = (uint8_m)(n >> 24);
				}
				#define MU_WBEU32 muu_wbeu32
			#endif

			// @DOCLINE * `MU_RBES32` - reads a signed 32-bit integer from big-endian byte data; overridable macro to `muu_rbes32`.
			#ifndef MU_RBES32
				MUDEF inline int32_m muu_rbes32(muByte* b) {
					uint32_m u32 = muu_rbeu32(b);
					return *(int32_m*)&u32;
				}
				#define MU_RBES32 muu_rbes32
			#endif

			// @DOCLINE * `MU_WBES32` - writes a signed 32-bit integer to big-endian byte data; overridable macro to `muu_wbes32`.
			#ifndef MU_WBES32
				MUDEF inline void muu_wbes32(muByte* b, int32_m n) {
					uint32_m un = *(uint32_m*)&n;
					b[3] = (uint8_m)(un >> 0);
					b[2] = (uint8_m)(un >> 8);
					b[1] = (uint8_m)(un >> 16);
					b[0] = (uint8_m)(un >> 24);
				}
				#define MU_WBES32 muu_wbes32
			#endif

		// @DOCLINE ## 64-bit

			// @DOCLINE The following macros exist for byte manipulation regarding 64-bit integers:

			// @DOCLINE * `MU_RLEU64` - reads an unsigned 64-bit integer from little-endian byte data; overridable macro to `muu_rleu64`.
			#ifndef MU_RLEU64
				MUDEF inline uint64_m muu_rleu64(muByte* b) {
					return (
						((uint64_m)(b[0]) << 0)  |
						((uint64_m)(b[1]) << 8)  |
						((uint64_m)(b[2]) << 16) |
						((uint64_m)(b[3]) << 24) |
						((uint64_m)(b[4]) << 32) |
						((uint64_m)(b[5]) << 40) |
						((uint64_m)(b[6]) << 48) |
						((uint64_m)(b[7]) << 56)
					);
				}
				#define MU_RLEU64 muu_rleu64
			#endif

			// @DOCLINE * `MU_WLEU64` - writes an unsigned 64-bit integer to little-endian byte data; overridable macro to `muu_wleu64`.
			#ifndef MU_WLEU64
				MUDEF inline void muu_wleu64(muByte* b, uint64_m n) {
					b[0] = (uint8_m)(n >> 0);
					b[1] = (uint8_m)(n >> 8);
					b[2] = (uint8_m)(n >> 16);
					b[3] = (uint8_m)(n >> 24);
					b[4] = (uint8_m)(n >> 32);
					b[5] = (uint8_m)(n >> 40);
					b[6] = (uint8_m)(n >> 48);
					b[7] = (uint8_m)(n >> 56);
				}
				#define MU_WLEU64 muu_wleu64
			#endif

			// @DOCLINE * `MU_RLES64` - reads a signed 64-bit integer from little-endian byte data; overridable macro to `muu_rles64`.
			#ifndef MU_RLES64
				MUDEF inline int64_m muu_rles64(muByte* b) {
					uint64_m u64 = muu_rleu64(b);
					return *(int64_m*)&u64;
				}
				#define MU_RLES64 muu_rles64
			#endif

			// @DOCLINE * `MU_WLES64` - writes a signed 64-bit integer to little-endian byte data; overridable macro to `muu_wles64`.
			#ifndef MU_WLES64
				MUDEF inline void muu_wles64(muByte* b, int64_m n) {
					uint64_m un = *(uint64_m*)&n;
					b[0] = (uint8_m)(un >> 0);
					b[1] = (uint8_m)(un >> 8);
					b[2] = (uint8_m)(un >> 16);
					b[3] = (uint8_m)(un >> 24);
					b[4] = (uint8_m)(un >> 32);
					b[5] = (uint8_m)(un >> 40);
					b[6] = (uint8_m)(un >> 48);
					b[7] = (uint8_m)(un >> 56);
				}
				#define MU_WLES64 muu_wles64
			#endif

			// @DOCLINE * `MU_RBEU64` - reads an unsigned 64-bit integer from big-endian byte data; overridable macro to `muu_rbeu64`.
			#ifndef MU_RBEU64
				MUDEF inline uint64_m muu_rbeu64(muByte* b) {
					return (
						((uint64_m)(b[7]) << 0)  |
						((uint64_m)(b[6]) << 8)  |
						((uint64_m)(b[5]) << 16) |
						((uint64_m)(b[4]) << 24) |
						((uint64_m)(b[3]) << 32) |
						((uint64_m)(b[2]) << 40) |
						((uint64_m)(b[1]) << 48) |
						((uint64_m)(b[0]) << 56)
					);
				}
				#define MU_RBEU64 muu_rbeu64
			#endif

			// @DOCLINE * `MU_WBEU64` - writes an unsigned 64-bit integer to big-endian byte data; overridable macro to `muu_wbeu64`.
			#ifndef MU_WBEU64
				MUDEF inline void muu_wbeu64(muByte* b, uint64_m n) {
					b[7] = (uint8_m)(n >> 0);
					b[6] = (uint8_m)(n >> 8);
					b[5] = (uint8_m)(n >> 16);
					b[4] = (uint8_m)(n >> 24);
					b[3] = (uint8_m)(n >> 32);
					b[2] = (uint8_m)(n >> 40);
					b[1] = (uint8_m)(n >> 48);
					b[0] = (uint8_m)(n >> 56);
				}
				#define MU_WBEU64 muu_wbeu64
			#endif

			// @DOCLINE * `MU_RBES64` - reads a signed 64-bit integer from big-endian byte data; overridable macro to `muu_rbes64`.
			#ifndef MU_RBES64
				MUDEF inline int64_m muu_rbes64(muByte* b) {
					uint64_m u64 = muu_rbeu64(b);
					return *(int64_m*)&u64;
				}
				#define MU_RBES64 muu_rbes64
			#endif

			// @DOCLINE * `MU_WBES64` - writes a signed 64-bit integer to big-endian byte data; overridable macro to `muu_wbes64`.
			#ifndef MU_WBES64
				MUDEF inline void muu_wbes64(muByte* b, int64_m n) {
					uint64_m un = *(uint64_m*)&n;
					b[7] = (uint8_m)(un >> 0);
					b[6] = (uint8_m)(un >> 8);
					b[5] = (uint8_m)(un >> 16);
					b[4] = (uint8_m)(un >> 24);
					b[3] = (uint8_m)(un >> 32);
					b[2] = (uint8_m)(un >> 40);
					b[1] = (uint8_m)(un >> 48);
					b[0] = (uint8_m)(un >> 56);
				}
				#define MU_WBES64 muu_wbes64
			#endif

	// @DOCLINE # Set result

		/* @DOCBEGIN

		The `MU_SET_RESULT(res, val)` macro is an overridable function that checks if the given parameter `res` is a null pointer. If it is, it does nothing, but if it isn't, it dereferences the pointer and sets the value to `val`. This macro saves a lot of code, shrinking down what would be this:

		```c
		if (result) {
			*result = ...;
		}
		```

		into this:

		```c
		MU_SET_RESULT(result, ...)
		```

		@DOCEND */

		#ifndef MU_SET_RESULT
			#define MU_SET_RESULT(res, val) if(res){*res=val;}
		#endif

	// @DOCLINE # Enum

		/* @DOCBEGIN

		The `MU_ENUM(name, ...)` macro is an overridable function used to declare an enumerator. `name` is the name of the enumerator type, and `...` are all of the values. The reason why one would prefer this over the traditional way of declaring enumerators is because it actually makes it a `size_m`, which can avoid errors on certain compilers (looking at you, Microsoft) in regards to treating enumerators like values. It expands like this:

		```c
		enum _##name {
			__VA_ARGS__
		};
		typedef enum _##name _##name;
		typedef size_m name;
		```

		@DOCEND */

		#define MU_ENUM(name, ...) enum _##name{__VA_ARGS__};typedef enum _##name _##name;typedef size_m name;

	// @DOCLINE # Operating system recognition

		/* @DOCBEGIN

		The macros `MU_WIN32` or `MU_LINUX` are defined (if neither were defined before) in order to allow mu libraries to easily check if they're running on a Windows or Linux system.

		`MU_WIN32` will be defined if `WIN32` or `_WIN32` are defined, one of which is usually pre-defined on Windows systems.

		`MU_LINUX` will be defined if `__linux__` is defined.

		@DOCEND */

		#if !defined(MU_WIN32) && !defined(MU_LINUX)
			#if defined(WIN32) || defined(_WIN32)
				#define MU_WIN32
			#endif
			#if defined(__linux__)
				#define MU_LINUX
			#endif
		#endif

	MU_CPP_EXTERN_END

#endif /* MUU_H */

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

