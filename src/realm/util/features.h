/*************************************************************************
 *
 * REALM CONFIDENTIAL
 * __________________
 *
 *  [2011] - [2012] Realm Inc
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Realm Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Realm Incorporated
 * and its suppliers and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Realm Incorporated.
 *
 *************************************************************************/
#ifndef REALM_UTIL_FEATURES_H
#define REALM_UTIL_FEATURES_H

#ifdef _MSC_VER
#  pragma warning(disable:4800) // Visual Studio int->bool performance warnings
#endif

#ifdef REALM_HAVE_CONFIG
#  include <realm/util/config.h>
#else
#  define REALM_VERSION               "unknown"
#  define REALM_ENABLE_ALLOC_SET_ZERO 0
#  define REALM_ENABLE_ENCRYPTION     0
#  define REALM_ENABLE_ASSERTIONS     0

#  ifndef _WIN32
#    define REALM_INSTALL_PREFIX      "/usr/local"
#    define REALM_INSTALL_EXEC_PREFIX REALM_INSTALL_PREFIX
#    define REALM_INSTALL_INCLUDEDIR  REALM_INSTALL_PREFIX "/include"
#    define REALM_INSTALL_BINDIR      REALM_INSTALL_EXEC_PREFIX "/bin"
#    define REALM_INSTALL_LIBDIR      REALM_INSTALL_EXEC_PREFIX "/lib"
#    define REALM_INSTALL_LIBEXECDIR  REALM_INSTALL_EXEC_PREFIX "/libexec"
#  endif
#endif

/* The maximum number of elements in a B+-tree node. Applies to inner nodes and
 * to leaves. The minimum allowable value is 2.
 */
#ifndef REALM_MAX_BPNODE_SIZE
#  define REALM_MAX_BPNODE_SIZE 1000
#endif


/* See these links for information about feature check macroes in GCC,
 * Clang, and MSVC:
 *
 * http://gcc.gnu.org/projects/cxx0x.html
 * http://clang.llvm.org/cxx_status.html
 * http://clang.llvm.org/docs/LanguageExtensions.html#checks-for-standard-language-features
 * http://msdn.microsoft.com/en-us/library/vstudio/hh567368.aspx
 * http://sourceforge.net/p/predef/wiki/Compilers
 */


/* Compiler is GCC and version is greater than or equal to the specified version */
#define REALM_HAVE_AT_LEAST_GCC(maj, min) \
    (__GNUC__ > (maj) || __GNUC__ == (maj) && __GNUC_MINOR__ >= (min))

#if __clang__
#  define REALM_HAVE_CLANG_FEATURE(feature) __has_feature(feature)
#else
#  define REALM_HAVE_CLANG_FEATURE(feature) 0
#endif

/* Compiler is MSVC (Microsoft Visual C++) */
#if _MSC_VER >= 1600
#  define REALM_HAVE_AT_LEAST_MSVC_10_2010 1
#endif
#if _MSC_VER >= 1700
#  define REALM_HAVE_AT_LEAST_MSVC_11_2012 1
#endif
#if _MSC_VER >= 1800
#  define REALM_HAVE_AT_LEAST_MSVC_12_2013 1
#endif


/* The way to specify that a function never returns. */
#if REALM_HAVE_AT_LEAST_GCC(4, 8) || REALM_HAVE_CLANG_FEATURE(cxx_attributes)
#  define REALM_NORETURN [[noreturn]]
#elif __GNUC__
#  define REALM_NORETURN __attribute__((noreturn))
#elif _MSC_VER
#  define REALM_NORETURN __declspec(noreturn)
#else
#  define REALM_NORETURN
#endif


/* The way to specify that a variable or type is intended to possibly
 * not be used. Use it to suppress a warning from the compiler. */
#if __GNUC__
#  define REALM_UNUSED __attribute__((unused))
#else
#  define REALM_UNUSED
#endif


#if __GNUC__ || defined __INTEL_COMPILER
#  define REALM_UNLIKELY(expr) __builtin_expect(!!(expr), 0)
#  define REALM_LIKELY(expr)   __builtin_expect(!!(expr), 1)
#else
#  define REALM_UNLIKELY(expr) (expr)
#  define REALM_LIKELY(expr)   (expr)
#endif


#if defined(__GNUC__) || defined(__HP_aCC)
#  define REALM_FORCEINLINE inline __attribute__((always_inline))
#elif defined(_MSC_VER)
#  define REALM_FORCEINLINE __forceinline
#else
#  define REALM_FORCEINLINE inline
#endif


#if defined(__GNUC__) || defined(__HP_aCC)
#  define REALM_NOINLINE  __attribute__((noinline))
#elif defined(_MSC_VER)
#  define REALM_NOINLINE __declspec(noinline)
#else
#  define REALM_NOINLINE
#endif


/* Thread specific data (only for POD types) */
#if defined __clang__
#  define REALM_THREAD_LOCAL __thread
#else
#  define REALM_THREAD_LOCAL thread_local
#endif


#if defined __ANDROID__
#  define REALM_ANDROID 1
#endif


#if defined __APPLE__ && defined __MACH__
#  define REALM_PLATFORM_APPLE 1
/* Apple OSX and iOS (Darwin). */
#  include <TargetConditionals.h>
#  if TARGET_OS_IPHONE == 1
/* Device (iPhone or iPad) or simulator. */
#    define REALM_IOS 1
#  endif
#  if TARGET_OS_WATCH == 1
/* Device (Apple Watch) or simulator. */
#    define REALM_WATCHOS 1
/* The necessary signal handling / mach exception APIs are all unavailable */
#    undef  REALM_ENABLE_ENCRYPTION
#    define REALM_ENABLE_ENCRYPTION 0
#  endif
#  if TARGET_OS_TV
/* Device (Apple TV) or simulator. */
#    define REALM_TVOS 1
/* The necessary signal handling / mach exception APIs are all unavailable */
#    undef  REALM_ENABLE_ENCRYPTION
#    define REALM_ENABLE_ENCRYPTION 0
#  endif
#else
#  define REALM_PLATFORM_APPLE 0
#endif


#if REALM_ANDROID || REALM_IOS || REALM_WATCHOS
#  define REALM_MOBILE 1
#endif


#if defined(REALM_DEBUG) && !defined(REALM_COOKIE_CHECK)
#  define REALM_COOKIE_CHECK
#endif

#if !REALM_IOS && !REALM_WATCHOS && !REALM_TVOS && !defined(_WIN32)
#  define REALM_ASYNC_DAEMON
#endif


#endif /* REALM_UTIL_FEATURES_H */
