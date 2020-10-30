/**
 * Created by rayfalling on 2020/8/30.
 * 
 * Typedef file for project.
 * Use for cross platform data type.
 * Windows platform definition to override generic definition.
 * */

#pragma once

#ifndef VISREAL_WINDOWS_PLATFORM_H
#define VISREAL_WINDOWS_PLATFORM_H

#include "Platform/GenericPlatformTypes.h"
#include "Marco/MSVCPlatform.h"

namespace Engine::Core::Types {
	/**
	* Windows specific types
	**/
	struct FWindowsPlatformTypes : public GenericPlatformTypes {
		#ifdef Platform_x64
		typedef unsigned __int64 SIZE_T;
		typedef __int64          SSIZE_T;
		#else
        typedef unsigned long SIZE_T;
        typedef long		  SSIZE_T;
		#endif
	};

	typedef FWindowsPlatformTypes FPlatformTypes;

	// Base defines, must define these for the platform, there are no defaults
	#define PLATFORM_DESKTOP                    1
	#if defined( _WIN64 )
	#define PLATFORM_64BITS                    1
	#else
#define PLATFORM_64BITS					0
	#endif
	#if defined( _MANAGED ) || defined( _M_CEE )
#define PLATFORM_COMPILER_COMMON_LANGUAGE_RUNTIME_COMPILATION	1
	#endif
	#define PLATFORM_CAN_SUPPORT_EDITORONLY_DATA                1

	// Base defines, defaults are commented out

	#define PLATFORM_LITTLE_ENDIAN                                1
	#define PLATFORM_SUPPORTS_UNALIGNED_LOADS                    1
	#if defined(__clang__)
    // @todo clang: Clang compiler on Windows doesn't support SEH exception handling yet (__try/__except)
#define PLATFORM_SEH_EXCEPTIONS_DISABLED				1

    // @todo clang: Clang compiler on Windows doesn't support C++ exception handling yet (try/throw/catch)
#define PLATFORM_EXCEPTIONS_DISABLED					1
	#endif

	#define PLATFORM_SUPPORTS_PRAGMA_PACK                           1
	#define PLATFORM_ENABLE_VECTORINTRINSICS                        1
	#define PLATFORM_USE_LS_SPEC_FOR_WIDECHAR                       0
	//#define PLATFORM_USE_SYSTEM_VSWPRINTF						    1
	//#define PLATFORM_TCHAR_IS_4_BYTES							    0
	#define PLATFORM_HAS_BSD_TIME                                   0
	#define PLATFORM_USE_PTHREADS                                   0
	#define PLATFORM_MAX_FILEPATH_LENGTH_DEPRECATED                 WINDOWS_MAX_PATH
	#define PLATFORM_HAS_BSD_SOCKET_FEATURE_WINSOCKETS              1
	#define PLATFORM_USES_MICROSOFT_LIBC_FUNCTIONS                  1
	#define PLATFORM_IS_ANSI_MALLOC_THREADSAFE                      1
	#define PLATFORM_SUPPORTS_TBB                                   1
	#define PLATFORM_SUPPORTS_NAMED_PIPES                           1
	#define PLATFORM_COMPILER_HAS_TCHAR_WMAIN                       1
	#define PLATFORM_SUPPORTS_EARLY_MOVIE_PLAYBACK                  (!WITH_EDITOR) // movies will start before engine is initalized
	#define PLATFORM_RHITHREAD_DEFAULT_BYPASS                       0
	#define PLATFORM_USE_GENERIC_STRING_IMPLEMENTATION              0
	#define PLATFORM_SUPPORTS_VIRTUAL_TEXTURE_STREAMING             1

	#define PLATFORM_SUPPORTS_STACK_SYMBOLS                         1
	#define PLATFORM_COMPILER_HAS_DECLTYPE_AUTO                     1
	#define PLATFORM_IS_ANSI_MALLOC_THREADSAFE                      1

	// Q: Why is there a __nop() before __debugbreak()?
	// A: VS' debug engine has a bug where it will silently swallow explicit
	// breakpoint interrupts when single-step debugging either line-by-line or
	// over call instructions. This can hide legitimate reasons to trap. Asserts
	// for example, which can appear as if the did not fire, leaving a programmer
	// unknowingly debugging an undefined process.
	#define PLATFORM_BREAK() (__nop(), __debugbreak())

	// Intrinsics for 128-bit atomics on Windows platform requires Windows 8 or higher (WINVER>=0x0602)
	// http://msdn.microsoft.com/en-us/library/windows/desktop/hh972640.aspx
	#define PLATFORM_HAS_128BIT_ATOMICS                            (!HACK_HEADER_GENERATOR && PLATFORM_64BITS && (WINVER >= 0x602))
	#define PLATFORM_USES_ANSI_STRING_FOR_EXTERNAL_PROFILING    0

	// Function type macros.
	#define VARARGS     __cdecl                                             /* Functions with variable arguments */
	#define CDECL        __cdecl                                            /* Standard C function */
	#define STDCALL        __stdcall                                        /* Standard calling convention */
	#define FORCEINLINE __forceinline                                       /* Force code to be inline */
	#define FORCENOINLINE __declspec(noinline)                              /* Force code to NOT be inline */
	#define FUNCTION_NO_RETURN_START __declspec(noreturn)                   /* Indicate that the function never returns. */
	#define FUNCTION_NON_NULL_RETURN_START _Ret_notnull_                    /* Indicate that the function never returns nullptr. */

	// Hints compiler that expression is true; generally restricted to comparisons against constants
	#if !defined(__clang__) || defined(_MSC_VER)    // Clang only supports __assume when using -fms-extensions
	#define ASSUME(expr) __assume(expr)
	#endif

	#define DECLARE_UINT64(x)    x

	// Optimization macros (uses __pragma to enable inside a #define).
	#if !defined(__clang__)
	#define PRAGMA_DISABLE_OPTIMIZATION_ACTUAL __pragma(optimize("",off))
	#define PRAGMA_ENABLE_OPTIMIZATION_ACTUAL  __pragma(optimize("",on))
	#elif defined(_MSC_VER)        // Clang only supports __pragma with -fms-extensions
#define PRAGMA_DISABLE_OPTIMIZATION_ACTUAL __pragma(clang optimize off)
#define PRAGMA_ENABLE_OPTIMIZATION_ACTUAL  __pragma(clang optimize on)
	#endif

	// Tells the compiler to put the decorated function in a certain section (aka. segment) of the executable.
	#define PLATFORM_CODE_SECTION(Name) __declspec(code_seg(Name))

	// Backwater of the spec. All compilers support this except microsoft, and they will soon
	#if !defined(__clang__)        // Clang expects typename outside template
	#define TYPENAME_OUTSIDE_TEMPLATE
	#endif

	#pragma warning(disable : 4481) // nonstandard extension used: override specifier 'override'

	#if defined(__clang__) || _MSC_VER >= 1900
	#define CONSTEXPR constexpr
	#else
#define CONSTEXPR
	#endif
	#define ABSTRACT abstract

	// Strings.
	#define LINE_TERMINATOR TEXT("\r\n")
	#define LINE_TERMINATOR_ANSI "\r\n"

	// Alignment.
	#if defined(__clang__)
#define GCC_PACK(n) __attribute__((packed,aligned(n)))
#define GCC_ALIGN(n) __attribute__((aligned(n)))
	#if defined(_MSC_VER)
#define MS_ALIGN(n) __declspec(align(n)) // With -fms-extensions, Clang will accept either alignment attribute
	#endif
	#else
	#define MS_ALIGN(n) __declspec(align(n))
	#endif

	// Pragmas
	#if !defined(__clang__)
	#define MSVC_PRAGMA(Pragma) __pragma(Pragma)
	#endif

	// Prefetch
	#define PLATFORM_CACHE_LINE_SIZE    64

	// disable this now as it is annoying for generic platform implementations
	#pragma warning(disable : 4100) // unreferenced formal parameter

	#if USING_CODE_ANALYSIS && _MSC_VER == 1900
	// Disable this warning as VC2015 Update 1 produces this warning erroneously when placed on variadic templates:
	//
    // warning C28216: The checkReturn annotation only applies to postconditions for function 'Func' _Param_(N).
#define FUNCTION_CHECK_RETURN_START __pragma(warning(push)) __pragma(warning(disable: 28216)) __declspec("SAL_checkReturn")
#define FUNCTION_CHECK_RETURN_END __pragma(warning(pop))
	#else
	#define FUNCTION_CHECK_RETURN_START __declspec("SAL_checkReturn")    /* Warn that callers should not ignore the return value. */
	#endif

	// Other macros
	#ifndef ENABLE_WIN_ALLOC_TRACKING
	#define ENABLE_WIN_ALLOC_TRACKING 0
	#endif
}
#endif //VISREAL_WINDOWS_PLATFORM_H