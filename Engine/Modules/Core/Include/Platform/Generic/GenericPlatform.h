/**
 * Created by rayfalling on 2020/11/9.
 * */

// ReSharper disable CppClangTidyClangDiagnosticUnusedMacros
// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
#pragma once

#ifndef VISREAL_GENERIC_PLATFORM_H
#define VISREAL_GENERIC_PLATFORM_H

namespace Engine::Core {
	// define all other platforms to be zero
	//@port Define the platform here to be zero when compiling for other platforms
	#if !defined(PLATFORM_WINDOWS)
	#define PLATFORM_WINDOWS 0
	#endif
	#if !defined(PLATFORM_ANDROID)
	#define PLATFORM_ANDROID 0
	#endif
	#if !defined(PLATFORM_APPLE)
	#define PLATFORM_APPLE 0
	#endif
	#if !defined(PLATFORM_LINUX)
	#define PLATFORM_LINUX 0
	#endif

	// Platform specific compiler pre-setup.
	#include "Marco/PreprocessorHelpers.h"

	// Whether the CPU is x86/x64 (i.e. both 32 and 64-bit variants)
	#ifndef PLATFORM_CPU_X86_FAMILY
	#if (defined(_M_IX86) || defined(__i386__) || defined(_M_X64) || defined(__amd64__) || defined(__x86_64__))
	#define PLATFORM_CPU_X86_FAMILY	1
	#else
	#define PLATFORM_CPU_X86_FAMILY	0
	#endif
	#endif

	// Whether the CPU is AArch32/AArch64 (i.e. both 32 and 64-bit variants)
	#ifndef PLATFORM_CPU_ARM_FAMILY
	#if (defined(__arm__) || defined(_M_ARM) || defined(__aarch64__) || defined(_M_ARM64))
	#define PLATFORM_CPU_ARM_FAMILY	1
	#else
	#define PLATFORM_CPU_ARM_FAMILY	0
	#endif
	#endif

	#if PLATFORM_APPLE
	#include <stddef.h> // needed for size_t
	#endif

	//------------------------------------------------------------------
	// Setup macros for static code analysis
	//------------------------------------------------------------------
	#ifndef PLATFORM_COMPILER_CLANG
	#if defined(__clang__)
	#define PLATFORM_COMPILER_CLANG			1
	#else
	#define PLATFORM_COMPILER_CLANG			0
	#endif // defined(__clang__)
	#endif

	#ifndef USING_ADDRESS_SANITISER
	#define USING_ADDRESS_SANITISER 0
	#endif

	// Base defines, these have defaults
	#ifndef PLATFORM_LITTLE_ENDIAN
	#define PLATFORM_LITTLE_ENDIAN				0
	#endif
	#ifndef PLATFORM_SUPPORTS_UNALIGNED_LOADS
	#define PLATFORM_SUPPORTS_UNALIGNED_LOADS	0
	#endif
	#ifndef PLATFORM_EXCEPTIONS_DISABLED
	#define PLATFORM_EXCEPTIONS_DISABLED		!PLATFORM_DESKTOP
	#endif
	#ifndef PLATFORM_SEH_EXCEPTIONS_DISABLED
	#define PLATFORM_SEH_EXCEPTIONS_DISABLED	0
	#endif
	#ifndef PLATFORM_SUPPORTS_PRAGMA_PACK
	#define PLATFORM_SUPPORTS_PRAGMA_PACK		0
	#endif
	#ifndef PLATFORM_ENABLE_VECTORINTRINSICS
	#define PLATFORM_ENABLE_VECTORINTRINSICS	0
	#endif
	#ifndef PLATFORM_HAS_CPUID
	#if defined(_M_IX86) || defined(__i386__) || defined(_M_X64) || defined(__x86_64__) || defined (__amd64__)
	#define PLATFORM_HAS_CPUID				1
	#else
	#define PLATFORM_HAS_CPUID				0
	#endif
	#endif
	#ifndef PLATFORM_ENABLE_POPCNT_INTRINSIC
	// PC is disabled by default, but linux and mac are enabled
	// if your min spec is an AMD cpu mid-2007 or Intel 2008, you should enable this
	#define PLATFORM_ENABLE_POPCNT_INTRINSIC						0
	#endif
	#ifndef PLATFORM_ENABLE_VECTORINTRINSICS_NEON
	#define PLATFORM_ENABLE_VECTORINTRINSICS_NEON					0
	#endif
	#ifndef PLATFORM_USE_LS_SPEC_FOR_WCHAR
	#define PLATFORM_USE_LS_SPEC_FOR_WCHAR							1
	#endif
	#ifndef PLATFORM_USE_SYSTEM_VSWPRINTF
	#define PLATFORM_USE_SYSTEM_VSWPRINTF							1
	#endif
	#ifndef PLATFORM_COMPILER_DISTINGUISHES_INT_AND_LONG
	#define PLATFORM_COMPILER_DISTINGUISHES_INT_AND_LONG			0
	#endif
	#ifdef _MSC_VER
	#define PLATFORM_COMPILER_HAS_AUTO_RETURN_TYPES					1
	#ifndef __clang__
	#pragma deprecated("PLATFORM_COMPILER_HAS_AUTO_RETURN_TYPES")
	#endif
	#else
	#define PLATFORM_COMPILER_HAS_AUTO_RETURN_TYPES					1
	#endif
	#ifndef PLATFORM_COMPILER_HAS_GENERIC_KEYWORD
	#define PLATFORM_COMPILER_HAS_GENERIC_KEYWORD					0
	#endif
	#ifdef _MSC_VER
	#define PLATFORM_COMPILER_HAS_DEFAULTED_FUNCTIONS				1
	#ifndef __clang__
	#pragma deprecated("PLATFORM_COMPILER_HAS_DEFAULTED_FUNCTIONS")
	#endif
	#else
	#define PLATFORM_COMPILER_HAS_DEFAULTED_FUNCTIONS				1
	#endif
	#ifndef PLATFORM_COMPILER_COMMON_LANGUAGE_RUNTIME_COMPILATION
	#define PLATFORM_COMPILER_COMMON_LANGUAGE_RUNTIME_COMPILATION	0
	#endif
	#ifndef PLATFORM_COMPILER_HAS_TCHAR_WMAIN
	#define PLATFORM_COMPILER_HAS_TCHAR_WMAIN						0
	#endif
	#ifndef PLATFORM_COMPILER_HAS_DECLTYPE_AUTO
	#define PLATFORM_COMPILER_HAS_DECLTYPE_AUTO						1
	#endif
	#ifndef PLATFORM_COMPILER_HAS_IF_CONSTEXPR
	#define PLATFORM_COMPILER_HAS_IF_CONSTEXPR						1
	#endif
	#ifndef PLATFORM_TCHAR_IS_1_BYTE
	#define PLATFORM_TCHAR_IS_1_BYTE								0
	#endif
	#ifndef PLATFORM_TCHAR_IS_4_BYTES
	#define PLATFORM_TCHAR_IS_4_BYTES								0
	#endif
	#ifndef PLATFORM_WCHAR_IS_4_BYTES
	#define PLATFORM_WCHAR_IS_4_BYTES								0
	#endif
	#ifndef PLATFORM_TCHAR_IS_CHAR16
	#define PLATFORM_TCHAR_IS_CHAR16								0
	#endif
	#ifndef PLATFORM_HAS_BSD_TIME
	#define PLATFORM_HAS_BSD_TIME									1
	#endif
	#ifndef PLATFORM_HAS_BSD_SOCKETS
	#define PLATFORM_HAS_BSD_SOCKETS								1
	#endif
	#ifndef PLATFORM_HAS_BSD_IPV6_SOCKETS
	#define PLATFORM_HAS_BSD_IPV6_SOCKETS							0
	#endif
	#ifndef PLATFORM_SUPPORTS_UDP_MULTICAST_GROUP
	#define PLATFORM_SUPPORTS_UDP_MULTICAST_GROUP					1
	#endif
	#ifndef PLATFORM_USE_PTHREADS
	#define PLATFORM_USE_PTHREADS									1
	#endif
	#ifndef PLATFORM_MAX_FILEPATH_LENGTH_DEPRECATED
	#define PLATFORM_MAX_FILEPATH_LENGTH_DEPRECATED					128
	#endif
	#ifndef PLATFORM_SUPPORTS_TEXTURE_STREAMING
	#define PLATFORM_SUPPORTS_TEXTURE_STREAMING						1
	#endif
	#ifndef PLATFORM_SUPPORTS_VIRTUAL_TEXTURE_STREAMING
	#define PLATFORM_SUPPORTS_VIRTUAL_TEXTURE_STREAMING				0
	#endif
	#ifndef PLATFORM_SUPPORTS_VIRTUAL_TEXTURES
	#define PLATFORM_SUPPORTS_VIRTUAL_TEXTURES						0
	#endif
	#ifndef PLATFORM_REQUIRES_FILESERVER
	#define PLATFORM_REQUIRES_FILESERVER							0
	#endif
	#ifndef PLATFORM_SUPPORTS_MULTITHREADED_GC
	#define PLATFORM_SUPPORTS_MULTITHREADED_GC						1
	#endif
	#ifndef PLATFORM_HAS_BSD_SOCKET_FEATURE_IOCTL
	#define PLATFORM_HAS_BSD_SOCKET_FEATURE_IOCTL					1
	#endif
	#ifndef PLATFORM_HAS_BSD_SOCKET_FEATURE_SELECT
	#define PLATFORM_HAS_BSD_SOCKET_FEATURE_SELECT					1
	#endif
	#ifndef PLATFORM_HAS_BSD_SOCKET_FEATURE_WINSOCKETS
	#define PLATFORM_HAS_BSD_SOCKET_FEATURE_WINSOCKETS				0
	#endif
	#ifndef PLATFORM_HAS_BSD_SOCKET_FEATURE_GETHOSTNAME
	#define PLATFORM_HAS_BSD_SOCKET_FEATURE_GETHOSTNAME				1
	#endif
	#ifndef PLATFORM_HAS_BSD_SOCKET_FEATURE_GETADDRINFO
	#define PLATFORM_HAS_BSD_SOCKET_FEATURE_GETADDRINFO				1
	#endif
	#ifndef PLATFORM_HAS_BSD_SOCKET_FEATURE_GETNAMEINFO
	#define PLATFORM_HAS_BSD_SOCKET_FEATURE_GETNAMEINFO				1
	#endif
	#ifndef PLATFORM_HAS_BSD_SOCKET_FEATURE_CLOSE_ON_EXEC
	#define PLATFORM_HAS_BSD_SOCKET_FEATURE_CLOSE_ON_EXEC			0
	#endif
	#ifndef PLATFORM_HAS_BSD_SOCKET_FEATURE_MSG_DONTWAIT
	#define PLATFORM_HAS_BSD_SOCKET_FEATURE_MSG_DONTWAIT			0
	#endif
	#ifndef PLATFORM_HAS_BSD_SOCKET_FEATURE_RECVMMSG
	#define PLATFORM_HAS_BSD_SOCKET_FEATURE_RECVMMSG				0
	#endif
	#ifndef PLATFORM_HAS_BSD_SOCKET_FEATURE_TIMESTAMP
	#define PLATFORM_HAS_BSD_SOCKET_FEATURE_TIMESTAMP				0
	#endif
	#ifndef PLATFORM_HAS_BSD_SOCKET_FEATURE_NODELAY
	#define PLATFORM_HAS_BSD_SOCKET_FEATURE_NODELAY					1
	#endif
	#ifndef PLATFORM_HAS_NO_EPROCLIM
	#define PLATFORM_HAS_NO_EPROCLIM								0
	#endif
	#ifndef PLATFORM_USES_MICROSOFT_LIBC_FUNCTIONS
	#define PLATFORM_USES_MICROSOFT_LIBC_FUNCTIONS					0
	#endif

	#ifndef PLATFORM_SUPPORTS_DRAW_MESH_EVENTS
	#define PLATFORM_SUPPORTS_DRAW_MESH_EVENTS						1
	#endif

	#ifndef PLATFORM_USES_ES2
	#define PLATFORM_USES_ES2										0
	#endif

	#ifndef PLATFORM_SUPPORTS_GEOMETRY_SHADERS
	#define PLATFORM_SUPPORTS_GEOMETRY_SHADERS						1
	#endif

	#ifndef PLATFORM_SUPPORTS_TESSELLATION_SHADERS
	#define PLATFORM_SUPPORTS_TESSELLATION_SHADERS					1
	#endif

	#if PLATFORM_SUPPORTS_TESSELLATION_SHADERS && !PLATFORM_SUPPORTS_GEOMETRY_SHADERS
	#error Geometry shader support is required by tessellation
	#endif

	#ifndef PLATFORM_BUILTIN_VERTEX_HALF_FLOAT
	#define PLATFORM_BUILTIN_VERTEX_HALF_FLOAT						1
	#endif

	#ifndef PLATFORM_SUPPORTS_TBB
	#define PLATFORM_SUPPORTS_TBB									0
	#endif

	#ifndef PLATFORM_MAX_CACHED_SYNC_FILE_HANDLES_PER_GENERIC_ASYNC_FILE_HANDLE
	#define PLATFORM_MAX_CACHED_SYNC_FILE_HANDLES_PER_GENERIC_ASYNC_FILE_HANDLE		4
	#endif

	#ifndef PLATFORM_FORCE_SINGLE_SYNC_FILE_HANDLE_PER_GENERIC_ASYNC_FILE_HANDLE
	#define PLATFORM_FORCE_SINGLE_SYNC_FILE_HANDLE_PER_GENERIC_ASYNC_FILE_HANDLE	0
	#endif

	#ifndef PLATFORM_SUPPORTS_JEMALLOC
	#define PLATFORM_SUPPORTS_JEMALLOC					0
	#endif

	#ifndef PLATFORM_CAN_SUPPORT_EDITORONLY_DATA
	#define PLATFORM_CAN_SUPPORT_EDITORONLY_DATA		0
	#endif

	#ifndef PLATFORM_SUPPORTS_NAMED_PIPES
	#define PLATFORM_SUPPORTS_NAMED_PIPES				0
	#endif

	#ifndef PLATFORM_USES_FIXED_RHI_CLASS
	#define PLATFORM_USES_FIXED_RHI_CLASS				0
	#endif

	#ifndef PLATFORM_USES_FIXED_GMalloc_CLASS
	#define PLATFORM_USES_FIXED_GMalloc_CLASS			0
	#endif

	#ifndef PLATFORM_USES_STACKBASED_MALLOC_CRASH
	#define PLATFORM_USES_STACKBASED_MALLOC_CRASH		0
	#endif

	#ifndef PLATFORM_SUPPORTS_MULTIPLE_NATIVE_WINDOWS
	#define PLATFORM_SUPPORTS_MULTIPLE_NATIVE_WINDOWS	1
	#endif

	#ifndef PLATFORM_HAS_TOUCH_MAIN_SCREEN
	#define PLATFORM_HAS_TOUCH_MAIN_SCREEN				0
	#endif

	#ifndef PLATFORM_SUPPORTS_STACK_SYMBOLS
	#define PLATFORM_SUPPORTS_STACK_SYMBOLS				0
	#endif

	#ifndef PLATFORM_RUNTIME_MALLOCPROFILER_SYMBOLICATION
	#define PLATFORM_RUNTIME_MALLOCPROFILER_SYMBOLICATION PLATFORM_SUPPORTS_STACK_SYMBOLS
	#endif

	#ifndef PLATFORM_HAS_128BIT_ATOMICS
	#define PLATFORM_HAS_128BIT_ATOMICS					0
	#endif

	#ifndef PLATFORM_USES_ANSI_STRING_FOR_EXTERNAL_PROFILING
	#define PLATFORM_USES_ANSI_STRING_FOR_EXTERNAL_PROFILING	1
	#endif

	#ifndef PLATFORM_IMPLEMENTS_BeginNamedEventStatic
	#define PLATFORM_IMPLEMENTS_BeginNamedEventStatic			0
	#endif

	#ifndef PLATFORM_RHITHREAD_DEFAULT_BYPASS
	#define PLATFORM_RHITHREAD_DEFAULT_BYPASS					1
	#endif

	#ifndef PLATFORM_HAS_UMA
	#define PLATFORM_HAS_UMA									0
	#endif

	#ifndef PLATFORM_NUM_AUDIODECOMPRESSION_PRECACHE_BUFFERS
	#define PLATFORM_NUM_AUDIODECOMPRESSION_PRECACHE_BUFFERS	2
	#endif

	#ifndef PLATFORM_SUPPORTS_EARLY_MOVIE_PLAYBACK
	#define PLATFORM_SUPPORTS_EARLY_MOVIE_PLAYBACK				0
	#endif

	#ifndef PLATFORM_VECTOR_CUBIC_INTERP_SSE
	#define PLATFORM_VECTOR_CUBIC_INTERP_SSE					0
	#endif

	#ifndef PLATFORM_UI_HAS_MOBILE_SCROLLBARS
	#define PLATFORM_UI_HAS_MOBILE_SCROLLBARS					0
	#endif

	#ifndef PLATFORM_UI_NEEDS_TOOLTIPS
	#define PLATFORM_UI_NEEDS_TOOLTIPS							1
	#endif

	#ifndef PLATFORM_UI_NEEDS_FOCUS_OUTLINES
	#define PLATFORM_UI_NEEDS_FOCUS_OUTLINES					1
	#endif

	#ifndef PLATFORM_LIMIT_MOBILE_BONE_MATRICES
	#define PLATFORM_LIMIT_MOBILE_BONE_MATRICES					0
	#endif

	#ifndef PLATFORM_WEAKLY_CONSISTENT_MEMORY
	#define PLATFORM_WEAKLY_CONSISTENT_MEMORY PLATFORM_CPU_ARM_FAMILY
	#endif

	#ifndef PLATFORM_HAS_CRC_INTRINSICS
	#define PLATFORM_HAS_CRC_INTRINSICS							0
	#endif

	#ifndef PLATFORM_NEEDS_RHIRESOURCELIST
	#define PLATFORM_NEEDS_RHIRESOURCELIST 1
	#endif

	#ifndef PLATFORM_USE_FULL_TASK_GRAPH
	#define PLATFORM_USE_FULL_TASK_GRAPH						1
	#endif

	#ifndef PLATFORM_USE_ANSI_POSIX_MALLOC
	#define PLATFORM_USE_ANSI_POSIX_MALLOC						0
	#endif

	#ifndef PLATFORM_USE_ANSI_MEMALIGN
	#define PLATFORM_USE_ANSI_MEMALIGN							0
	#endif

	#ifndef PLATFORM_USE_ANSI_POSIX_MALLOC
	#define PLATFORM_USE_ANSI_POSIX_MALLOC						0
	#endif

	#ifndef PLATFORM_IS_ANSI_MALLOC_THREADSAFE
	#define PLATFORM_IS_ANSI_MALLOC_THREADSAFE					0
	#endif

	#ifndef PLATFORM_SUPPORTS_OPUS_CODEC
	#define PLATFORM_SUPPORTS_OPUS_CODEC						1
	#endif

	#ifndef PLATFORM_SUPPORTS_VORBIS_CODEC
	#define PLATFORM_SUPPORTS_VORBIS_CODEC						1
	#endif


	#ifndef PLATFORM_USE_MINIMAL_HANG_DETECTION
	#define PLATFORM_USE_MINIMAL_HANG_DETECTION					0
	#endif

	#ifndef PLATFORM_USE_GENERIC_STRING_IMPLEMENTATION
	#define PLATFORM_USE_GENERIC_STRING_IMPLEMENTATION			1
	#endif

	#ifndef PLATFORM_SUPPORTS_LLM
	#define PLATFORM_SUPPORTS_LLM								1
	#endif

	#ifndef PLATFORM_ALLOW_ALLOCATIONS_IN_FASYNCWRITER_SERIALIZEBUFFERTOARCHIVE
	#define	PLATFORM_ALLOW_ALLOCATIONS_IN_FASYNCWRITER_SERIALIZEBUFFERTOARCHIVE		1
	#endif

	#ifndef PLATFORM_HAS_FPlatformVirtualMemoryBlock
	#define	PLATFORM_HAS_FPlatformVirtualMemoryBlock			1
	#endif
	#ifndef PLATFORM_BYPASS_PAK_PRECACHE
	#define PLATFORM_BYPASS_PAK_PRECACHE						0
	#endif

	#ifndef PLATFORM_SUPPORTS_FLIP_TRACKING
	#define PLATFORM_SUPPORTS_FLIP_TRACKING						0
	#endif

	#ifndef PLATFORM_USE_FULL_TASK_GRAPH
	#define PLATFORM_USE_FULL_TASK_GRAPH						1
	#endif

	#ifndef PLATFORM_USE_ANSI_POSIX_MALLOC
	#define PLATFORM_USE_ANSI_POSIX_MALLOC						0
	#endif

	#ifndef PLATFORM_USE_ANSI_MEMALIGN
	#define PLATFORM_USE_ANSI_MEMALIGN							0
	#endif

	#ifndef PLATFORM_USE_ANSI_POSIX_MALLOC
	#define PLATFORM_USE_ANSI_POSIX_MALLOC						0
	#endif

	#ifndef PLATFORM_IS_ANSI_MALLOC_THREADSAFE
	#define PLATFORM_IS_ANSI_MALLOC_THREADSAFE					0
	#endif

	#ifndef PLATFORM_SUPPORTS_OPUS_CODEC
	#define PLATFORM_SUPPORTS_OPUS_CODEC						1
	#endif

	#ifndef PLATFORM_SUPPORTS_VORBIS_CODEC
	#define PLATFORM_SUPPORTS_VORBIS_CODEC						1
	#endif

	#ifndef PLATFORM_USE_MINIMAL_HANG_DETECTION
	#define PLATFORM_USE_MINIMAL_HANG_DETECTION					0
	#endif

	#ifndef PLATFORM_USE_GENERIC_STRING_IMPLEMENTATION
	#define PLATFORM_USE_GENERIC_STRING_IMPLEMENTATION			1
	#endif

	#ifndef PLATFORM_USE_SHOWFLAGS_ALWAYS_BITFIELD
	#define	PLATFORM_USE_SHOWFLAGS_ALWAYS_BITFIELD				1
	#endif

	// These is computed, not predefined
	#define PLATFORM_32BITS					(!PLATFORM_64BITS)

	// not supported by the platform system yet or maybe ever
	#define PLATFORM_VTABLE_AT_END_OF_CLASS 0

	#ifndef VARARGS
	#define VARARGS									/* Functions with variable arguments */
	#endif
	#ifndef CDECL
	#define CDECL									/* Standard C function */
	#endif
	#ifndef STDCALL
	#define STDCALL									/* Standard calling convention */
	#endif
	#ifndef FORCEINLINE
	#define FORCEINLINE 							/* Force code to be inline */
	#endif
	#ifndef FORCENOINLINE
	#define FORCENOINLINE 							/* Force code to NOT be inline */
	#endif
	#ifndef RESTRICT
	#define RESTRICT __restrict						/* no alias hint */
	#endif

	/* Wrap a function signature in these to warn that callers should not ignore the return value */
	#ifndef FUNCTION_CHECK_RETURN_START
	#define FUNCTION_CHECK_RETURN_START
	#endif
	#ifndef FUNCTION_CHECK_RETURN_END
	#define FUNCTION_CHECK_RETURN_END
	#endif

	/* Wrap a function signature in these to indicate that the function never returns */
	#ifndef FUNCTION_NO_RETURN_START
	#define FUNCTION_NO_RETURN_START
	#endif
	#ifndef FUNCTION_NO_RETURN_END
	#define FUNCTION_NO_RETURN_END
	#endif

	/* Wrap a function signature in these to indicate that the function never returns nullptr */
	#ifndef FUNCTION_NON_NULL_RETURN_START
	#define FUNCTION_NON_NULL_RETURN_START
	#endif
	#ifndef FUNCTION_NON_NULL_RETURN_END
	#define FUNCTION_NON_NULL_RETURN_END
	#endif

	#ifndef FUNCTION_CHECK_RETURN
	#define FUNCTION_CHECK_RETURN(...)
	#endif

	#ifndef ASSUME										/* Hints compiler that expression is true; generally restricted to comparisons against constants */
	#define ASSUME(...)
	#endif

	/** Branch prediction hints */
	#ifndef LIKELY						/* Hints compiler that expression is likely to be true, much softer than ASSUME - allows (penalized by worse performance) expression to be false */
	#if ( defined(__clang__) || defined(__GNUC__) )	// effect of these on non-Linux platform has not been analyzed as of 2016-03-21
	#define LIKELY(x)			__builtin_expect(!!(x), 1)
	#else
	#define LIKELY(x)			(x)
	#endif
	#endif

	#ifndef UNLIKELY					/* Hints compiler that expression is unlikely to be true, allows (penalized by worse performance) expression to be true */
	#if ( defined(__clang__) || defined(__GNUC__) )	// effect of these on non-Linux platform has not been analyzed as of 2016-03-21
	#define UNLIKELY(x)			__builtin_expect(!!(x), 0)
	#else
	#define UNLIKELY(x)			(x)
	#endif
	#endif

	// Optimization macros (uses __pragma to enable inside a #define).
	#ifndef PRAGMA_DISABLE_OPTIMIZATION_ACTUAL
	#define PRAGMA_DISABLE_OPTIMIZATION_ACTUAL
	#define PRAGMA_ENABLE_OPTIMIZATION_ACTUAL
	#endif

	// Disable optimization of a specific function
	#ifndef DISABLE_FUNCTION_OPTIMIZATION
	#define DISABLE_FUNCTION_OPTIMIZATION
	#endif

	// Enable/disable optimizations for a specific function to improve build times
	#define BEGIN_FUNCTION_BUILD_OPTIMIZATION PRAGMA_DISABLE_OPTIMIZATION
	#define END_FUNCTION_BUILD_OPTIMIZATION   PRAGMA_ENABLE_OPTIMIZATION

	#ifndef FORCEINLINE_DEBUGGABLE_ACTUAL
	#define FORCEINLINE_DEBUGGABLE_ACTUAL inline
	#endif

	#ifndef DECLARE_UINT64
	#define DECLARE_UINT64(x) x##ULL	/* Define a 64 bit immediate int **/
	#endif

	// Backwater of the spec. All compilers support this except microsoft, and they will soon
	#ifndef TYPENAME_OUTSIDE_TEMPLATE
	#define TYPENAME_OUTSIDE_TEMPLATE	typename
	#endif

	// Method modifiers
	#ifndef ABSTRACT
	#define ABSTRACT
	#endif
	#ifndef CONSTEXPR
	#define CONSTEXPR constexpr
	#endif

	// String constants
	#ifndef LINE_TERMINATOR
	#define LINE_TERMINATOR TEXT("\n")
	#endif
	#ifndef LINE_TERMINATOR_ANSI
	#define LINE_TERMINATOR_ANSI "\n"
	#endif

	// Alignment.
	#ifndef GCC_PACK
	#define GCC_PACK(n)
	#endif
	#ifndef GCC_ALIGN
	#define GCC_ALIGN(n)
	#endif
	#ifndef MS_ALIGN
	#define MS_ALIGN(n)
	#endif

	// MSVC pragmas - used so other platforms can remove them easily (by not defining this)
	#ifndef MSVC_PRAGMA
	#define MSVC_PRAGMA(...)
	#endif


	// Inlining
	#ifndef PRAGMA_DISABLE_INLINING
	#define PRAGMA_DISABLE_INLINING
	#define PRAGMA_ENABLE_INLINING
	#endif

	// Cache control
	#ifndef FLUSH_CACHE_LINE
	#define FLUSH_CACHE_LINE(x)
	#endif

	// Prefetch
	#ifndef PLATFORM_CACHE_LINE_SIZE
	#define PLATFORM_CACHE_LINE_SIZE	64
	#endif

	// Compile-time warnings and errors. Use these as "#pragma COMPILER_WARNING("XYZ")". GCC does not expand macro parameters to _Pragma, so we can't wrap the #pragma part.
	#ifdef _MSC_VER
	#define MSC_FORMAT_DIAGNOSTIC_HELPER_2(x) #x
	#define MSC_FORMAT_DIAGNOSTIC_HELPER(x) MSC_FORMAT_DIAGNOSTIC_HELPER_2(x)
	#define COMPILE_WARNING(x) __pragma(message(__FILE__ "(" MSC_FORMAT_DIAGNOSTIC_HELPER(__LINE__) "): warning: " x))
	#define COMPILE_ERROR(x) __pragma(message(__FILE__ "(" MSC_FORMAT_DIAGNOSTIC_HELPER(__LINE__) "): error: " x))
	#else
	#define GCC_DIAGNOSTIC_HELPER(x) _Pragma(#x)
	#define COMPILE_WARNING(x) GCC_DIAGNOSTIC_HELPER(GCC warning x)
	#define COMPILE_ERROR(x) GCC_DIAGNOSTIC_HELPER(GCC error x)
	#endif

	// Tells the compiler to put the decorated function in a certain section (aka. segment) of the executable.
	#ifndef PLATFORM_CODE_SECTION
	#define PLATFORM_CODE_SECTION(Name)
	#endif

	// These have to be forced inline on some OSes so the dynamic loader will not
	// resolve to our allocators for the system libraries.
	#ifndef OPERATOR_NEW_INLINE
	#define OPERATOR_NEW_INLINE FORCEINLINE
	#endif

	#ifndef OPERATOR_NEW_THROW_SPEC
	#define OPERATOR_NEW_THROW_SPEC
	#endif
	#ifndef OPERATOR_DELETE_THROW_SPEC
	#define OPERATOR_DELETE_THROW_SPEC
	#endif
	#ifndef OPERATOR_NEW_NOTHROW_SPEC
	#define OPERATOR_NEW_NOTHROW_SPEC throw()
	#endif
	#ifndef OPERATOR_DELETE_NOTHROW_SPEC
	#define OPERATOR_DELETE_NOTHROW_SPEC throw()
	#endif

	// embedded app is not default (embedding UE4 in a native view, right now just for IOS and Android)
	#ifndef BUILD_EMBEDDED_APP
	#define BUILD_EMBEDDED_APP  0
	#endif
	#ifndef FAST_BOOT_HACKS
	#define FAST_BOOT_HACKS		0
	#endif

	#ifndef DEPRECATED_FORGAME
	#define DEPRECATED_FORGAME(...)
	#endif

	// Console CHAR/TCHAR command line handling
	#if PLATFORM_COMPILER_HAS_TCHAR_WMAIN
	#define INT32_MAIN_INT32_ARGC_TCHAR_ARGV() int32 wmain(int32 ArgC, TCHAR* ArgV[])
	#else
	#define INT32_MAIN_INT32_ARGC_TCHAR_ARGV() \
	int32 tchar_main(int32 ArgC, TCHAR* ArgV[]); \
	int32 main(int32 ArgC, CHAR* Utf8ArgV[]) \
	{ \
		TCHAR** ArgV = new TCHAR*[ArgC]; \
		for (int32 a = 0; a < ArgC; a++) \
		{ \
			FUTF8ToTCHAR ConvertFromUtf8(Utf8ArgV[a]); \
			ArgV[a] = new TCHAR[ConvertFromUtf8.Length() + 1]; \
			FCString::Strcpy(ArgV[a], ConvertFromUtf8.Length() + 1, ConvertFromUtf8.Get()); \
		} \
		int32 Result = tchar_main(ArgC, ArgV); \
		for (int32 a = 0; a < ArgC; a++) \
		{ \
			delete[] ArgV[a]; \
		} \
		delete[] ArgV; \
		return Result; \
	} \
	int32 tchar_main(int32 ArgC, TCHAR* ArgV[])
	#endif

	// If we don't have a platform-specific define for the TEXT macro, define it now.
	#if !defined(TEXT) 
	#if PLATFORM_TCHAR_IS_CHAR16
	#define TEXT_PASTE(x) u ## x
	#else
	#define TEXT_PASTE(x) L ## x
	#endif
	#define TEXT(x) TEXT_PASTE(x)
	#endif
}

#endif // VISREAL_GENERIC_PLATFORM_H
