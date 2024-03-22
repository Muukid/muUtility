/*
muUtility.h - Muukid
Public domain C utility file used by mu libraries.
No warranty implied; use at your own risk.

Licensed under MIT License or public domain, whichever you prefer.
More explicit license information at the end of file.

@MENTION MU_SECURE_WARNINGS
*/

#ifndef MUU_H
	#define MUU_H
	
	#if !defined(MU_SECURE_WARNINGS) && !defined(_CRT_SECURE_NO_WARNINGS)
		#define _CRT_SECURE_NO_WARNINGS
	#endif

	#ifdef __cplusplus
	extern "C" { // }
	#endif

	#define MUU_VERSION_MAJOR 1
	#define MUU_VERSION_MINOR 0
	#define MUU_VERSION_PATCH 0

	/* C standard library dependencies */

		#if !defined(int8_m)   || \
			!defined(uint8_m)  || \
			!defined(int16_m)  || \
			!defined(uint16_m) || \
			!defined(int32_m)  || \
			!defined(uint32_m) || \
			!defined(int64_m)  || \
			!defined(uint64_m)

			#define __STDC_LIMIT_MACROS
			#define __STDC_CONSTANT_MACROS
			#include <stdint.h>

			#ifndef int8_m
				#ifdef INT8_MAX
					#define int8_m int8_t
				#else
					#define int8_m char
				#endif
			#endif

			#ifndef uint8_m
				#ifdef UINT8_MAX
					#define uint8_m uint8_t
				#else
					#define uint8_m unsigned char
				#endif
			#endif

			#ifndef int16_m
				#ifdef INT16_MAX
					#define int16_m int16_t
				#else
					#define int16_m short
				#endif
			#endif

			#ifndef uint16_m
				#ifdef UINT16_MAX
					#define uint16_m uint16_t
				#else
					#define uint16_m unsigned short
				#endif
			#endif

			#ifndef int32_m
				#ifdef INT32_MAX
					#define int32_m int32_t
				#else
					#define int32_m long
				#endif
			#endif

			#ifndef uint32_m
				#ifdef UINT32_MAX
					#define uint32_m uint32_t
				#else
					#define uint32_m unsigned long
				#endif
			#endif

			#ifndef int64_m
				#ifdef INT64_MAX
					#define int64_m int64_t
				#else
					#define int64_m long long
				#endif
			#endif

			#ifndef uint64_m
				#ifdef UINT64_MAX
					#define uint64_m uint64_t
				#else
					#define uint64_m unsigned long long
				#endif
			#endif

		#endif

		#if !defined(size_m)

			#include <stddef.h>

			#ifndef size_m
				#define size_m size_t
			#endif

		#endif

		#if !defined(MU_SIZE_MAX)

			#include <stdint.h>

			#ifndef MU_SIZE_MAX
				#define MU_SIZE_MAX SIZE_MAX
			#endif

		#endif

		#if !defined(muBool)   || \
			!defined(MU_TRUE)  || \
			!defined(MU_FALSE)

			#include <stdbool.h>

			#ifndef muBool
				#define muBool bool
			#endif

			#ifndef MU_TRUE
				#define MU_TRUE true
			#endif

			#ifndef MU_FALSE
				#define MU_FALSE false
			#endif

		#endif

	/* Useful macros */

		#ifndef MUDEF
			#ifdef MU_STATIC
				#define MUDEF static
			#else
				#define MUDEF extern
			#endif
		#endif

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

		#ifndef MU_NULL_PTR
			#define MU_NULL_PTR 0
		#endif

		#ifndef MU_NULL
			#define MU_NULL 0
		#endif

		#ifndef MU_NONE
			#define MU_NONE MU_SIZE_MAX
		#endif

		#ifndef MU_SET_RESULT
			#define MU_SET_RESULT(res, val) if(res!=MU_NULL_PTR){*res=val;}
		#endif

		#ifndef MU_ASSERT
			#define MU_ASSERT(cond, res, val, after) if(!(cond)){MU_SET_RESULT(res, val) after}
		#endif

		#define MU_ENUM(name, ...) enum _##name{__VA_ARGS__};typedef enum _##name _##name; typedef size_m name;

		#if !defined(MU_WIN32) && !defined(MU_UNIX)
			#if defined(WIN32) || defined(_WIN32)
				#define MU_WIN32
			#elif defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
				#define MU_UNIX
			#endif
		#endif

		#define MU_HRARRAY_DEFAULT_FUNC(name) \
			muBool name##_comp(name t0, name t1) { \
				return t0.active == t1.active; \
			} \
			\
			void name##_on_creation(name* p) { \
				if (p != MU_NULL_PTR) { \
					MU_LOCK_CREATE(p->lock, p->lock_active) \
				} \
			} \
			void name##_on_destruction(name* p) { \
				if (p != MU_NULL_PTR) { \
					MU_LOCK_DESTROY(p->lock, p->lock_active) \
				} \
			} \
			void name##_on_hold(name* p) { \
				if (p != MU_NULL_PTR) { \
					MU_LOCK_LOCK(p->lock, p->lock_active) \
				} \
			} \
			void name##_on_release(name* p) { \
				if (p != MU_NULL_PTR) { \
					MU_LOCK_UNLOCK(p->lock, p->lock_active) \
				} \
			} \
			\
			mu_dynamic_hrarray_declaration( \
				name##_array, name, name##_, name##_comp, \
				name##_on_creation, name##_on_destruction, name##_on_hold, name##_on_release \
			)

		#define MU_SAFEFUNC(result, lib_prefix, context, fail_return) \
			MU_SET_RESULT(result, lib_prefix##SUCCESS) \
			MU_ASSERT(context != MU_NULL_PTR, result, lib_prefix##NOT_YET_INITIALIZED, fail_return) \

		#define MU_HOLD(result, item, da, context, lib_prefix, fail_return, da_prefix) \
			MU_ASSERT(item < da.length, result, lib_prefix##INVALID_ID, fail_return) \
			da_prefix##hold_element(0, &da, item); \
			MU_ASSERT(da.data[item].active, result, lib_prefix##INVALID_ID, da_prefix##release_element(0, &da, item); fail_return)

		#define MU_RELEASE(da, item, da_prefix) \
			da_prefix##release_element(0, &da, item);

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

