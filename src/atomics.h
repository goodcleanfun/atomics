#ifndef ATOMICS_H
#define ATOMICS_H

#if defined(_MSC_VER) && !defined(__clang__)
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define ATOMICS_UNDEF_WIN32_LEAN_AND_MEAN
#include <windows.h>
#ifdef ATOMICS_UNDEF_WIN32_LEAN_AND_MEAN
#undef ATOMICS_UNDEF_WIN32_LEAN_AND_MEAN
#undef WIN32_LEAN_AND_MEAN
#endif
#endif

#include <intrin.h>

#define _Atomic volatile

typedef _Atomic bool atomic_bool;
typedef _Atomic char atomic_char;
typedef _Atomic signed char atomic_schar;
typedef _Atomic unsigned char atomic_uchar;
typedef _Atomic short atomic_short;
typedef _Atomic unsigned short atomic_ushort;
typedef _Atomic int atomic_int;
typedef _Atomic unsigned int atomic_uint;
typedef _Atomic long atomic_long;
typedef _Atomic unsigned long atomic_ulong;
typedef _Atomic long long atomic_llong;
typedef _Atomic unsigned long long atomic_ullong;
typedef _Atomic intptr_t atomic_intptr_t;
typedef _Atomic uintptr_t atomic_uintptr_t;
typedef _Atomic size_t atomic_size_t;
typedef _Atomic ptrdiff_t atomic_ptrdiff_t;
typedef _Atomic intmax_t atomic_intmax_t;
typedef _Atomic uintmax_t atomic_uintmax_t;

typedef struct atomic_flag { atomic_bool _Value; } atomic_flag;

typedef enum {
    memory_order_relaxed = 0,
    memory_order_consume = 1,
    memory_order_acquire = 2,
    memory_order_release = 3,
    memory_order_acq_rel = 4,
    memory_order_seq_cst = 5
} memory_order;

#define ATOMIC_BOOL_LOCK_FREE 1
#define ATOMIC_CHAR_LOCK_FREE 1
#define ATOMIC_CHAR16_T_LOCK_FREE 1
#define ATOMIC_CHAR32_T_LOCK_FREE 1
#define ATOMIC_WCHAR_T_LOCK_FREE 1
#define ATOMIC_SHORT_LOCK_FREE 1
#define ATOMIC_INT_LOCK_FREE 1
#define ATOMIC_LONG_LOCK_FREE 1
#define ATOMIC_LLONG_LOCK_FREE 1
#define ATOMIC_POINTER_LOCK_FREE 1

#define atomic_init(PTR, VAL) \
    atomic_store_explicit((PTR), (VAL), memory_order_relaxed)


static inline bool atomic_load_bool(const atomic_bool *obj) {
    bool val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}
static inline char atomic_load_char(const atomic_char *obj) {
    char val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}
static inline signed char atomic_load_schar(const atomic_schar *obj) {
    signed char val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}
static inline unsigned char atomic_load_uchar(const atomic_uchar *obj) {
    unsigned char val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}
static inline short atomic_load_short(const atomic_short *obj) {
    short val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}
static inline unsigned short atomic_load_ushort(const atomic_ushort *obj) {
    unsigned short val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}
static inline int atomic_load_int(const atomic_int *obj) {
    int val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}
static inline unsigned int atomic_load_uint(const atomic_uint *obj) {
    unsigned int val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}
static inline long atomic_load_long(const atomic_long *obj) {
    long val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}
static inline unsigned long atomic_load_ulong(const atomic_ulong *obj) {
    unsigned long val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}
static inline long long atomic_load_llong(const atomic_llong *obj) {
    long long val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}
static inline unsigned long long atomic_load_ullong(const atomic_ullong *obj) {
    unsigned long long val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}
static inline intptr_t atomic_load_intptr_t(const atomic_intptr_t *obj) {
    intptr_t val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}
static inline uintptr_t atomic_load_uintptr_t(const atomic_uintptr_t *obj) {
    uintptr_t val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}
static inline size_t atomic_load_size_t(const atomic_size_t *obj) {
    size_t val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}
static inline ptrdiff_t atomic_load_ptrdiff_t(const atomic_ptrdiff_t *obj) {
    ptrdiff_t val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}
static inline intmax_t atomic_load_intmax_t(const atomic_intmax_t *obj) {
    intmax_t val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}
static inline uintmax_t atomic_load_uintmax_t(const atomic_uintmax_t *obj) {
    uintmax_t val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}

#define atomic_load_generic(obj) \
    _Generic((obj), \
        atomic_bool * : atomic_load_bool, \
        const atomic_bool * : atomic_load_bool, \
        atomic_char * : atomic_load_char, \
        const atomic_char * : atomic_load_char, \
        atomic_schar * : atomic_load_schar, \
        const atomic_schar * : atomic_load_schar, \
        atomic_uchar * : atomic_load_uchar, \
        const atomic_uchar * : atomic_load_uchar, \
        atomic_short * : atomic_load_short, \
        const atomic_short * : atomic_load_short, \
        atomic_ushort * : atomic_load_ushort, \
        const atomic_ushort * : atomic_load_ushort, \
        atomic_int * : atomic_load_int, \
        const atomic_int * : atomic_load_int, \
        atomic_uint * : atomic_load_uint, \
        const atomic_uint * : atomic_load_uint, \
        atomic_long * : atomic_load_long, \
        const atomic_long * : atomic_load_long, \
        atomic_ulong * : atomic_load_ulong, \
        const atomic_ulong * : atomic_load_ulong, \
        atomic_llong * : atomic_load_llong, \
        const atomic_llong * : atomic_load_llong, \
        atomic_ullong * : atomic_load_ullong, \
        const atomic_ullong * : atomic_load_ullong, \
        atomic_intptr_t * : atomic_load_intptr_t, \
        const atomic_intptr_t * : atomic_load_intptr_t, \
        atomic_uintptr_t * : atomic_load_uintptr_t, \
        const atomic_uintptr_t * : atomic_load_uintptr_t, \
        atomic_size_t * : atomic_load_size_t, \
        const atomic_size_t * : atomic_load_size_t, \
        atomic_ptrdiff_t * : atomic_load_ptrdiff_t, \
        const atomic_ptrdiff_t * : atomic_load_ptrdiff_t, \
        atomic_intmax_t * : atomic_load_intmax_t, \
        const atomic_intmax_t * : atomic_load_intmax_t, \
        atomic_uintmax_t * :  atomic_load_uintmax_t \
    )(obj)

#define atomic_load(obj) atomic_load_generic(obj)


static inline __int8 ms_interlocked_exchange_i8(__int8 volatile *addr, __int8 desired) {
    return _InterlockedExchange8(addr, desired);
}

static inline __int16 ms_interlocked_exchange_i16(__int16 volatile *addr, __int16 desired) {
    return _InterlockedExchange16((__int16 *)addr, desired);
}

static inline __int32 ms_interlocked_exchange_i32(__int32 volatile *addr, __int32 desired) {
    return _InterlockedExchange((long *)addr, desired);
}

static inline __int64 ms_interlocked_exchange_i64(__int64 volatile *addr, __int64 desired) {
    return _InterlockedExchange64((__int64 *)addr, desired);
}

static inline atomic_exchange_bool(atomic_bool *obj, bool desired) {
    return ms_interlocked_exchange_i8((volatile __int8 *)obj, desired);
}

static inline atomic_exchange_char(atomic_char *obj, char desired) {
    return ms_interlocked_exchange_i8((volatile __int8 *)obj, desired);
}

static inline atomic_exchange_schar(atomic_schar *obj, signed char desired) {
    return ms_interlocked_exchange_i8((volatile __int8 *)obj, desired);
}

static inline atomic_exchange_uchar(atomic_uchar *obj, unsigned char desired) {
    return ms_interlocked_exchange_i8((volatile __int8 *)obj, desired);
}

static inline atomic_exchange_short(atomic_short *obj, short desired) {
    return ms_interlocked_exchange_i16((volatile __int16 *)obj, desired);
}

static inline atomic_exchange_ushort(atomic_ushort *obj, unsigned short desired) {
    return ms_interlocked_exchange_i16((volatile __int16 *)obj, desired);
}

static inline atomic_exchange_int(atomic_int *obj, int desired) {
    return ms_interlocked_exchange_i32((volatile __int32 *)obj, desired);
}

static inline atomic_exchange_uint(atomic_uint *obj, unsigned int desired) {
    return ms_interlocked_exchange_i32((volatile __int32 *)obj, desired);
}

static inline atomic_exchange_long(atomic_long *obj, long desired) {
    return ms_interlocked_exchange_i32((volatile __int32 *)obj, desired);
}

static inline atomic_exchange_ulong(atomic_ulong *obj, unsigned long desired) {
    return ms_interlocked_exchange_i32((volatile __int32 *)obj, desired);
}

static inline atomic_exchange_llong(atomic_llong *obj, long long desired) {
    return ms_interlocked_exchange_i64((volatile __int64 *)obj, desired);
}

static inline atomic_exchange_ullong(atomic_ullong *obj, unsigned long long desired) {
    return ms_interlocked_exchange_i64((volatile __int64 *)obj, desired);
}

static inline atomic_exchange_intptr_t(atomic_intptr_t *obj, intptr_t desired) {
    return ms_interlocked_exchange_i64((volatile __int64 *)obj, desired);
}

static inline atomic_exchange_uintptr_t(atomic_uintptr_t *obj, uintptr_t desired) {
    return ms_interlocked_exchange_i64((volatile __int64 *)obj, desired);
}

static inline atomic_exchange_size_t(atomic_size_t *obj, size_t desired) {
    return ms_interlocked_exchange_i64((volatile __int64 *)obj, desired);
}

static inline atomic_exchange_ptrdiff_t(atomic_ptrdiff_t *obj, ptrdiff_t desired) {
    return ms_interlocked_exchange_i64((volatile __int64 *)obj, desired);
}

static inline atomic_exchange_intmax_t(atomic_intmax_t *obj, intmax_t desired) {
    return ms_interlocked_exchange_i64((volatile __int64 *)obj, desired);
}

static inline atomic_exchange_uintmax_t(atomic_uintmax_t *obj, uintmax_t desired) {
    return ms_interlocked_exchange_i64((volatile __int64 *)obj, desired);
}

#define atomic_exchange(obj, desired) \
    _Generic((obj), \
        atomic_bool * : atomic_exchange_bool, \
        const atomic_bool * : atomic_exchange_bool, \
        atomic_char * : atomic_exchange_char, \
        const atomic_char * : atomic_exchange_char, \
        atomic_schar * : atomic_exchange_schar, \
        const atomic_schar * : atomic_exchange_schar, \
        atomic_uchar * : atomic_exchange_uchar, \
        const atomic_uchar * : atomic_exchange_uchar, \
        atomic_short * : atomic_exchange_short, \
        const atomic_short * : atomic_exchange_short, \
        atomic_ushort * : atomic_exchange_ushort, \
        const atomic_ushort * : atomic_exchange_ushort, \
        atomic_int * : atomic_exchange_int, \
        const atomic_int * : atomic_exchange_int, \
        atomic_uint * : atomic_exchange_uint, \
        const atomic_uint * : atomic_exchange_uint, \
        atomic_long * : atomic_exchange_long, \
        const atomic_long * : atomic_exchange_long, \
        atomic_ulong * : atomic_exchange_ulong, \
        const atomic_ulong * : atomic_exchange_ulong, \
        atomic_llong * : atomic_exchange_llong, \
        const atomic_llong * : atomic_exchange_llong, \
        atomic_ullong * : atomic_exchange_ullong, \
        const atomic_ullong * : atomic_exchange_ullong, \
        atomic_intptr_t * : atomic_exchange_intptr_t, \
        const atomic_intptr_t * : atomic_exchange_intptr_t, \
        atomic_uintptr_t * : atomic_exchange_uintptr_t, \
        const atomic_uintptr_t * : atomic_exchange_uintptr_t, \
        atomic_size_t * : atomic_exchange_size_t, \
        const atomic_size_t * : atomic_exchange_size_t, \
        atomic_ptrdiff_t * : atomic_exchange_ptrdiff_t, \
        const atomic_ptrdiff_t * : atomic_exchange_ptrdiff_t, \
        atomic_intmax_t * : atomic_exchange_intmax_t, \
        const atomic_intmax_t * : atomic_exchange_intmax_t, \
        atomic_uintmax_t * :  atomic_exchange_uintmax_t \
        const atomic_uintmax_t * :  atomic_exchange_uintmax_t \
    )(obj, desired)

#define atomic_store(obj, desired) atomic_exchange(obj, desired)
#define atomic_exchange_explicit(obj, desired, order) atomic_exchange(obj, desired)
#define atomic_store_explicit(obj, desired, order) atomic_exchange(obj, desired)

static inline __int8 ms_interlocked_compare_exchange_i8(__int8 volatile *addr, __int8 exchange, __int8 compare) {
    return _InterlockedCompareExchange8(addr, exchange, compare);
}

static inline __int16 ms_interlocked_compare_exchange_i16(__int16 volatile *addr, __int16 exchange, __int16 compare) {
    return _InterlockedCompareExchange16((__int16 *)addr, exchange, compare);
}

static inline __int32 ms_interlocked_compare_exchange_i32(__int32 volatile *addr, __int32 exchange, __int32 compare) {
    return _InterlockedCompareExchange((long *)addr, exchange, compare);
}

static inline __int64 ms_interlocked_compare_exchange_i64(__int64 volatile *addr, __int64 exchange, __int64 compare) {
    return _InterlockedCompareExchange64((__int64 *)addr, exchange, compare);
}

static bool atomic_compare_exchange_bool(atomic_bool *obj, bool *expected, bool desired) {
    bool val = *expected;
    *expected = ms_interlocked_compare_exchange_i8((volatile __int8 *)obj, (__int8)val, (__int8)desired);
    return *expected == val;
}

static bool atomic_compare_exchange_char(atomic_char *obj, char *expected, char desired) {
    char val = *expected;
    *expected = ms_interlocked_compare_exchange_i8((volatile __int8 *)obj, (__int8)val, (__int8)desired);
    return *expected == val;
}

static bool atomic_compare_exchange_schar(atomic_schar *obj, signed char *expected, signed char desired) {
    signed char val = *expected;
    *expected = ms_interlocked_compare_exchange_i8((volatile __int8 *)obj, (__int8)val, (__int8)desired);
    return *expected == val;
}

static bool atomic_compare_exchange_uchar(atomic_uchar *obj, unsigned char *expected, unsigned char desired) {
    unsigned char val = *expected;
    *expected = ms_interlocked_compare_exchange_i8((volatile __int8 *)obj, (__int8)val, (__int8)desired);
    return *expected == val;
}

static bool atomic_compare_exchange_short(atomic_short *obj, short *expected, short desired) {
    short val = *expected;
    *expected = ms_interlocked_compare_exchange_i16((volatile __int16 *)obj, (__int16)val, (__int16)desired);
    return *expected == val;
}

static bool atomic_compare_exchange_ushort(atomic_ushort *obj, unsigned short *expected, unsigned short desired) {
    unsigned short val = *expected;
    *expected = ms_interlocked_compare_exchange_i16((volatile __int16 *)obj, (__int16)val, (__int16)desired);
    return *expected == val;
}

static bool atomic_compare_exchange_int(atomic_int *obj, int *expected, int desired) {
    int val = *expected;
    *expected = ms_interlocked_compare_exchange_i32((volatile __int32 *)obj, (__int32)val, (__int32)desired);
    return *expected == val;
}

static bool atomic_compare_exchange_uint(atomic_uint *obj, unsigned int *expected, unsigned int desired) {
    unsigned int val = *expected;
    *expected = ms_interlocked_compare_exchange_i32((volatile __int32 *)obj, (__int32)val, (__int32)desired);
    return *expected == val;
}

static bool atomic_compare_exchange_long(atomic_long *obj, long *expected, long desired) {
    long val = *expected;
    *expected = ms_interlocked_compare_exchange_i32((volatile __int32 *)obj, (__int32)val, (__int32)desired);
    return *expected == val;
}

static bool atomic_compare_exchange_ulong(atomic_ulong *obj, unsigned long *expected, unsigned long desired) {
    unsigned long val = *expected;
    *expected = ms_interlocked_compare_exchange_i32((volatile __int32 *)obj, (__int32)val, (__int32)desired);
    return *expected == val;
}

static bool atomic_compare_exchange_llong(atomic_llong *obj, long long *expected, long long desired) {
    long long val = *expected;
    *expected = ms_interlocked_compare_exchange_i64((volatile __int64 *)obj, (__int64)val, (__int64)desired);
    return *expected == val;
}

static bool atomic_compare_exchange_ullong(atomic_ullong *obj, unsigned long long *expected, unsigned long long desired) {
    unsigned long long val = *expected;
    *expected = ms_interlocked_compare_exchange_i64((volatile __int64 *)obj, (__int64)val, (__int64)desired);
    return *expected == val;
}

static bool atomic_compare_exchange_intptr_t(atomic_intptr_t *obj, intptr_t *expected, intptr_t desired) {
    intptr_t val = *expected;
    *expected = ms_interlocked_compare_exchange_i64((volatile __int64 *)obj, (__int64)val, (__int64)desired);
    return *expected == val;
}

static bool atomic_compare_exchange_uintptr_t(atomic_uintptr_t *obj, uintptr_t *expected, uintptr_t desired) {
    uintptr_t val = *expected;
    *expected = ms_interlocked_compare_exchange_i64((volatile __int64 *)obj, (__int64)val, (__int64)desired);
    return *expected == val;
}

static bool atomic_compare_exchange_size_t(atomic_size_t *obj, size_t *expected, size_t desired) {
    size_t val = *expected;
    *expected = ms_interlocked_compare_exchange_i64((volatile __int64 *)obj, (__int64)val, (__int64)desired);
    return *expected == val;
}

static bool atomic_compare_exchange_ptrdiff_t(atomic_ptrdiff_t *obj, ptrdiff_t *expected, ptrdiff_t desired) {
    ptrdiff_t val = *expected;
    *expected = ms_interlocked_compare_exchange_i64((volatile __int64 *)obj, (__int64)val, (__int64)desired);
    return *expected == val;
}

static bool atomic_compare_exchange_intmax_t(atomic_intmax_t *obj, intmax_t *expected, intmax_t desired) {
    intmax_t val = *expected;
    *expected = ms_interlocked_compare_exchange_i64((volatile __int64 *)obj, (__int64)val, (__int64)desired);
    return *expected == val;
}

static bool atomic_compare_exchange_uintmax_t(atomic_uintmax_t *obj, uintmax_t *expected, uintmax_t desired) {
    uintmax_t val = *expected;
    *expected = ms_interlocked_compare_exchange_i64((volatile __int64 *)obj, (__int64)val, (__int64)desired);
    return *expected == val;
}

#define atomic_compare_exchange_generic(obj, expected, desired) \
    _Generic((obj), \
        atomic_bool * : atomic_compare_exchange_bool, \
        const atomic_bool * : atomic_compare_exchange_bool, \
        atomic_char * : atomic_compare_exchange_char, \
        const atomic_char * : atomic_compare_exchange_char, \
        atomic_schar * : atomic_compare_exchange_schar, \
        const atomic_schar * : atomic_compare_exchange_schar, \
        atomic_uchar * : atomic_compare_exchange_uchar, \
        const atomic_uchar * : atomic_compare_exchange_uchar, \
        atomic_short * : atomic_compare_exchange_short, \
        const atomic_short * : atomic_compare_exchange_short, \
        atomic_ushort * : atomic_compare_exchange_ushort, \
        const atomic_ushort * : atomic_compare_exchange_ushort, \
        atomic_int * : atomic_compare_exchange_int, \
        const atomic_int * : atomic_compare_exchange_int, \
        atomic_uint * : atomic_compare_exchange_uint, \
        const atomic_uint * : atomic_compare_exchange_uint, \
        atomic_long * : atomic_compare_exchange_long, \
        const atomic_long * : atomic_compare_exchange_long, \
        atomic_ulong * : atomic_compare_exchange_ulong, \
        const atomic_ulong * : atomic_compare_exchange_ulong, \
        atomic_llong * : atomic_compare_exchange_llong, \
        const atomic_llong * : atomic_compare_exchange_llong, \
        atomic_ullong * : atomic_compare_exchange_ullong, \
        const atomic_ullong * : atomic_compare_exchange_ullong, \
        atomic_intptr_t * : atomic_compare_exchange_intptr_t, \
        const atomic_intptr_t * : atomic_compare_exchange_intptr_t, \
        atomic_uintptr_t * : atomic_compare_exchange_uintptr_t, \
        const atomic_uintptr_t * : atomic_compare_exchange_uintptr_t, \
        atomic_size_t * : atomic_compare_exchange_size_t, \
        const atomic_size_t * : atomic_compare_exchange_size_t, \
        atomic_ptrdiff_t * : atomic_compare_exchange_ptrdiff_t, \
        const atomic_ptrdiff_t * : atomic_compare_exchange_ptrdiff_t, \
        atomic_intmax_t * : atomic_compare_exchange_intmax_t, \
        const atomic_intmax_t * : atomic_compare_exchange_intmax_t, \
        atomic_uintmax_t * :  atomic_compare_exchange_uintmax_t \
        const atomic_uintmax_t * :  atomic_compare_exchange_uintmax_t \
    )(obj, expected, desired)


#define atomic_compare_exchange_strong(obj, expected, desired) atomic_compare_exchange_generic((obj), (expected), (desired))
#define atomic_compare_exchange_weak(obj, expected, desired) atomic_compare_exchange_generic((obj), (expected), (desired))

static inline void atomic_thread_fence(memory_order order) {
    if (order == memory_order_relaxed) {
        return;
    } else if (order == memory_order_consume || order == memory_order_acquire) {
        _ReadBarrier();
    } else if (order == memory_order_release) {
        _WriteBarrier();
    } else if (order == memory_order_acq_rel || order == memory_order_seq_cst) {
        _ReadWriteBarrier();
    }
}

static inline void atomic_signal_fence(memory_order order) {
    (void)order;
    _ReadWriteBarrier();
}

static bool atomic_compare_exchange_explicit_bool(atomic_bool *obj, bool *expected, bool desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    bool ret = atomic_compare_exchange_bool(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static bool atomic_compare_exchange_explicit_char(atomic_char *obj, char *expected, char desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    bool ret = atomic_compare_exchange_char(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static bool atomic_compare_exchange_explicit_schar(atomic_schar *obj, signed char *expected, signed char desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    bool ret = atomic_compare_exchange_schar(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static bool atomic_compare_exchange_explicit_uchar(atomic_uchar *obj, unsigned char *expected, unsigned char desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    bool ret = atomic_compare_exchange_uchar(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static bool atomic_compare_exchange_explicit_short(atomic_short *obj, short *expected, short desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    bool ret = atomic_compare_exchange_short(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static bool atomic_compare_exchange_explicit_ushort(atomic_ushort *obj, unsigned short *expected, unsigned short desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    bool ret = atomic_compare_exchange_ushort(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static bool atomic_compare_exchange_explicit_int(atomic_int *obj, int *expected, int desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    bool ret = atomic_compare_exchange_int(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static bool atomic_compare_exchange_explicit_uint(atomic_uint *obj, unsigned int *expected, unsigned int desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    bool ret = atomic_compare_exchange_uint(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static bool atomic_compare_exchange_explicit_long(atomic_long *obj, long *expected, long desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    bool ret = atomic_compare_exchange_long(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static bool atomic_compare_exchange_explicit_ulong(atomic_ulong *obj, unsigned long *expected, unsigned long desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    bool ret = atomic_compare_exchange_ulong(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static bool atomic_compare_exchange_explicit_llong(atomic_llong *obj, long long *expected, long long desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    bool ret = atomic_compare_exchange_llong(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static bool atomic_compare_exchange_explicit_ullong(atomic_ullong *obj, unsigned long long *expected, unsigned long long desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    bool ret = atomic_compare_exchange_ullong(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static bool atomic_compare_exchange_explicit_intptr_t(atomic_intptr_t *obj, intptr_t *expected, intptr_t desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    bool ret = atomic_compare_exchange_intptr_t(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static bool atomic_compare_exchange_explicit_uintptr_t(atomic_uintptr_t *obj, uintptr_t *expected, uintptr_t desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    bool ret = atomic_compare_exchange_uintptr_t(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static bool atomic_compare_exchange_explicit_size_t(atomic_size_t *obj, size_t *expected, size_t desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    bool ret = atomic_compare_exchange_size_t(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static bool atomic_compare_exchange_explicit_ptrdiff_t(atomic_ptrdiff_t *obj, ptrdiff_t *expected, ptrdiff_t desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    bool ret = atomic_compare_exchange_ptrdiff_t(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static bool atomic_compare_exchange_explicit_intmax_t(atomic_intmax_t *obj, intmax_t *expected, intmax_t desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    bool ret = atomic_compare_exchange_intmax_t(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static bool atomic_compare_exchange_explicit_uintmax_t(atomic_uintmax_t *obj, uintmax_t *expected, uintmax_t desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    bool ret = atomic_compare_exchange_uintmax_t(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

#define atomic_compare_exchange_strong_explicit_generic(obj, expected, desired, success, failure) \
    _Generic((obj), \
        atomic_bool * : atomic_compare_exchange_explicit_bool, \
        const atomic_bool * : atomic_compare_exchange_explicit_bool, \
        atomic_char * : atomic_compare_exchange_explicit_char, \
        const atomic_char * : atomic_compare_exchange_explicit_char, \
        atomic_schar * : atomic_compare_exchange_explicit_schar, \
        const atomic_schar * : atomic_compare_exchange_explicit_schar, \
        atomic_uchar * : atomic_compare_exchange_explicit_uchar, \
        const atomic_uchar * : atomic_compare_exchange_explicit_uchar, \
        atomic_short * : atomic_compare_exchange_explicit_short, \
        const atomic_short * : atomic_compare_exchange_explicit_short, \
        atomic_ushort * : atomic_compare_exchange_explicit_ushort, \
        const atomic_ushort * : atomic_compare_exchange_explicit_ushort, \
        atomic_int * : atomic_compare_exchange_explicit_int, \
        const atomic_int * : atomic_compare_exchange_explicit_int, \
        atomic_uint * : atomic_compare_exchange_explicit_uint, \
        const atomic_uint * : atomic_compare_exchange_explicit_uint, \
        atomic_long * : atomic_compare_exchange_explicit_long, \
        const atomic_long * : atomic_compare_exchange_explicit_long, \
        atomic_ulong * : atomic_compare_exchange_explicit_ulong, \
        const atomic_ulong * : atomic_compare_exchange_explicit_ulong, \
        atomic_llong * : atomic_compare_exchange_explicit_llong, \
        const atomic_llong * : atomic_compare_exchange_explicit_llong, \
        atomic_ullong * : atomic_compare_exchange_explicit_ullong, \
        const atomic_ullong * : atomic_compare_exchange_explicit_ullong, \
        atomic_intptr_t * : atomic_compare_exchange_explicit_intptr_t, \
        const atomic_intptr_t * : atomic_compare_exchange_explicit_intptr_t, \
        atomic_uintptr_t * : atomic_compare_exchange_explicit_uintptr_t, \
        const atomic_uintptr_t * : atomic_compare_exchange_explicit_uintptr_t, \
        atomic_size_t * : atomic_compare_exchange_explicit_size_t, \
        const atomic_size_t * : atomic_compare_exchange_explicit_size_t, \
        atomic_ptrdiff_t * : atomic_compare_exchange_explicit_ptrdiff_t, \
        const atomic_ptrdiff_t * : atomic_compare_exchange_explicit_ptrdiff_t, \
        atomic_intmax_t * : atomic_compare_exchange_explicit_intmax_t, \
        const atomic_intmax_t * : atomic_compare_exchange_explicit_intmax_t, \
        atomic_uintmax_t * :  atomic_compare_exchange_explicit_uintmax_t \
        const atomic_uintmax_t * :  atomic_compare_exchange_explicit_uintmax_t \
    )(obj, expected, desired, success, failure)

#define atomic_compare_exchange_strong_explicit(obj, expected, desired, success, failure) atomic_compare_exchange_strong_explicit_generic(obj, expected, desired, success, failure)
#define atomic_compare_exchange_weak_explicit(obj, expected, desired, success, failure) atomic_compare_exchange_strong_explicit_generic(obj, expected, desired, success, failure)

static inline __int8 ms_interlocked_exchange_add_i8(__int8 volatile *addr, __int8 val) {
    return _InterlockedExchangeAdd8(addr, val);
}

static inline __int16 ms_interlocked_exchange_add_i16(__int16 volatile *addr, __int16 val) {
    return _InterlockedExchangeAdd16(addr, val);
}

static inline __int32 ms_interlocked_exchange_add_i32(__int32 volatile *addr, __int32 val) {
    return _InterlockedExchangeAdd(addr, val);
}

static inline __int64 ms_interlocked_exchange_add_i64(__int64 volatile *addr, __int64 val) {
    return _InterlockedExchangeAdd64(addr, val);
}

static inline bool atomic_fetch_add_bool(atomic_bool *obj, bool val) {
    return ms_interlocked_exchange_add_i8((__int8 volatile *)obj, val);
}

static inline char atomic_fetch_add_char(atomic_char *obj, char val) {
    return ms_interlocked_exchange_add_i8((__int8 volatile *)obj, val);
}

static inline signed char atomic_fetch_add_schar(atomic_schar *obj, signed char val) {
    return ms_interlocked_exchange_add_i8((__int8 volatile *)obj, val);
}

static inline unsigned char atomic_fetch_add_uchar(atomic_uchar *obj, unsigned char val) {
    return ms_interlocked_exchange_add_i8((__int8 volatile *)obj, val);
}

static inline short atomic_fetch_add_short(atomic_short *obj, short val) {
    return ms_interlocked_exchange_add_i16((__int16 volatile *)obj, val);
}

static inline unsigned short atomic_fetch_add_ushort(atomic_ushort *obj, unsigned short val) {
    return ms_interlocked_exchange_add_i16((__int16 volatile *)obj, val);
}

static inline int atomic_fetch_add_int(atomic_int *obj, int val) {
    return ms_interlocked_exchange_add_i32((__int32 volatile *)obj, val);
}

static inline unsigned int atomic_fetch_add_uint(atomic_uint *obj, unsigned int val) {
    return ms_interlocked_exchange_add_i32((__int32 volatile *)obj, val);
}

static inline long atomic_fetch_add_long(atomic_long *obj, long val) {
    return ms_interlocked_exchange_add_i32((__int32 volatile *)obj, val);
}

static inline unsigned long atomic_fetch_add_ulong(atomic_ulong *obj, unsigned long val) {
    return ms_interlocked_exchange_add_i32((__int32 volatile *)obj, val);
}

static inline long long atomic_fetch_add_llong(atomic_llong *obj, long long val) {
    return ms_interlocked_exchange_add_i64((__int64 volatile *)obj, val);
}

static inline unsigned long long atomic_fetch_add_ullong(atomic_ullong *obj, unsigned long long val) {
    return ms_interlocked_exchange_add_i64((__int64 volatile *)obj, val);
}

static inline intptr_t atomic_fetch_add_intptr_t(atomic_intptr_t *obj, intptr_t val) {
    return ms_interlocked_exchange_add_i64((__int64 volatile *)obj, val);
}

static inline uintptr_t atomic_fetch_add_uintptr_t(atomic_uintptr_t *obj, uintptr_t val) {
    return ms_interlocked_exchange_add_i64((__int64 volatile *)obj, val);
}

static inline size_t atomic_fetch_add_size_t(atomic_size_t *obj, size_t val) {
    return ms_interlocked_exchange_add_i64((__int64 volatile *)obj, val);
}

static inline ptrdiff_t atomic_fetch_add_ptrdiff_t(atomic_ptrdiff_t *obj, ptrdiff_t val) {
    return ms_interlocked_exchange_add_i64((__int64 volatile *)obj, val);
}

static inline intmax_t atomic_fetch_add_intmax_t(atomic_intmax_t *obj, intmax_t val) {
    return ms_interlocked_exchange_add_i64((__int64 volatile *)obj, val);
}

static inline uintmax_t atomic_fetch_add_uintmax_t(atomic_uintmax_t *obj, uintmax_t val) {
    return ms_interlocked_exchange_add_i64((__int64 volatile *)obj, val);
}

#define atomic_fetch_add(obj, arg) \
    _Generic((obj), \
        atomic_bool * : atomic_fetch_add_bool, \
        const atomic_bool * : atomic_fetch_add_bool, \
        atomic_char * : atomic_fetch_add_char, \
        const atomic_char * : atomic_fetch_add_char, \
        atomic_schar * : atomic_fetch_add_schar, \
        const atomic_schar * : atomic_fetch_add_schar, \
        atomic_uchar * : atomic_fetch_add_uchar, \
        const atomic_uchar * : atomic_fetch_add_uchar, \
        atomic_short * : atomic_fetch_add_short, \
        const atomic_short * : atomic_fetch_add_short, \
        atomic_ushort * : atomic_fetch_add_ushort, \
        const atomic_ushort * : atomic_fetch_add_ushort, \
        atomic_int * : atomic_fetch_add_int, \
        const atomic_int * : atomic_fetch_add_int, \
        atomic_uint * : atomic_fetch_add_uint, \
        const atomic_uint * : atomic_fetch_add_uint, \
        atomic_long * : atomic_fetch_add_long, \
        const atomic_long * : atomic_fetch_add_long, \
        atomic_ulong * : atomic_fetch_add_ulong, \
        const atomic_ulong * : atomic_fetch_add_ulong, \
        atomic_llong * : atomic_fetch_add_llong, \
        const atomic_llong * : atomic_fetch_add_llong, \
        atomic_ullong * : atomic_fetch_add_ullong, \
        const atomic_ullong * : atomic_fetch_add_ullong, \
        atomic_intptr_t * : atomic_fetch_add_intptr_t, \
        const atomic_intptr_t * : atomic_fetch_add_intptr_t, \
        atomic_uintptr_t * : atomic_fetch_add_uintptr_t, \
        const atomic_uintptr_t * : atomic_fetch_add_uintptr_t, \
        atomic_size_t * : atomic_fetch_add_size_t, \
        const atomic_size_t * : atomic_fetch_add_size_t, \
        atomic_ptrdiff_t * : atomic_fetch_add_ptrdiff_t, \
        const atomic_ptrdiff_t * : atomic_fetch_add_ptrdiff_t, \
        atomic_intmax_t * : atomic_fetch_add_intmax_t, \
        const atomic_intmax_t * : atomic_fetch_add_intmax_t, \
        atomic_uintmax_t * :  atomic_fetch_add_uintmax_t \
    )(obj, arg)

#define atomic_fetch_sub(obj, arg) atomic_fetch_add(obj, -(arg))
#define atomic_fetch_add_explicit(obj, arg, order) atomic_fetch_add(obj, arg)
#define atomic_fetch_sub_explicit(obj, arg, order) atomic_fetch_sub(obj, arg)


static inline bool atomic_flag_test_and_set(atomic_flag *obj) {
    bool val = 0;
    return atomic_compare_exchange_strong(&(obj->_Value), &val, 1) ? 0 : 1;
}

static inline void atomic_flag_clear(atomic_flag* obj) {
    atomic_store(&(obj->_Value), 0);
}

#define atomic_flag_test_and_set_explicit(obj, order) atomic_flag_test_and_set(obj)
#define atomic_flag_clear_explicit(obj, order) atomic_flag_clear(obj)

static inline bool atomic_is_lock_free_bool(atomic_bool *obj) { (void)obj; return 1; }
static inline bool atomic_is_lock_free_char(atomic_char *obj) { (void)obj; return 1; }
static inline bool atomic_is_lock_free_schar(atomic_schar *obj) { (void)obj; return 1; }
static inline bool atomic_is_lock_free_uchar(atomic_uchar *obj) { (void)obj; return 1; }
static inline bool atomic_is_lock_free_short(atomic_short *obj) { (void)obj; return 1; }
static inline bool atomic_is_lock_free_ushort(atomic_ushort *obj) { (void)obj; return 1; }
static inline bool atomic_is_lock_free_int(atomic_int *obj) { (void)obj; return 1; }
static inline bool atomic_is_lock_free_uint(atomic_uint *obj) { (void)obj; return 1; }
static inline bool atomic_is_lock_free_long(atomic_long *obj) { (void)obj; return 1; }
static inline bool atomic_is_lock_free_ulong(atomic_ulong *obj) { (void)obj; return 1; }
static inline bool atomic_is_lock_free_llong(atomic_llong *obj) { (void)obj; return 1; }
static inline bool atomic_is_lock_free_ullong(atomic_ullong *obj) { (void)obj; return 1; }
static inline bool atomic_is_lock_free_intptr_t(atomic_intptr_t *obj) { (void)obj; return 1; }
static inline bool atomic_is_lock_free_uintptr_t(atomic_uintptr_t *obj) { (void)obj; return 1; }
static inline bool atomic_is_lock_free_size_t(atomic_size_t *obj) { (void)obj; return 1; }
static inline bool atomic_is_lock_free_ptrdiff_t(atomic_ptrdiff_t *obj) { (void)obj; return 1; }
static inline bool atomic_is_lock_free_intmax_t(atomic_intmax_t *obj) { (void)obj; return 1; }
static inline bool atomic_is_lock_free_uintmax_t(atomic_uintmax_t *obj) { (void)obj; return 1; }

#define atomic_is_lock_free(obj) \
    _Generic((obj), \
        atomic_bool : atomic_is_lock_free_bool, \
        const atomic_bool : atomic_is_lock_free_bool, \
        atomic_char : atomic_is_lock_free_char, \
        const atomic_char : atomic_is_lock_free_char, \
        atomic_schar : atomic_is_lock_free_schar, \
        const atomic_schar : atomic_is_lock_free_schar, \
        atomic_uchar : atomic_is_lock_free_uchar, \
        const atomic_uchar : atomic_is_lock_free_uchar, \
        atomic_short : atomic_is_lock_free_short, \
        const atomic_short : atomic_is_lock_free_short, \
        atomic_ushort : atomic_is_lock_free_ushort, \
        const atomic_ushort : atomic_is_lock_free_ushort, \
        atomic_int : atomic_is_lock_free_int, \
        const atomic_int : atomic_is_lock_free_int, \
        atomic_uint : atomic_is_lock_free_uint, \
        const atomic_uint : atomic_is_lock_free_uint, \
        atomic_long : atomic_is_lock_free_long, \
        const atomic_long : atomic_is_lock_free_long, \
        atomic_ulong : atomic_is_lock_free_ulong, \
        const atomic_ulong : atomic_is_lock_free_ulong, \
        atomic_llong : atomic_is_lock_free_llong, \
        const atomic_llong : atomic_is_lock_free_llong, \
        atomic_ullong : atomic_is_lock_free_ullong, \
        const atomic_ullong : atomic_is_lock_free_ullong, \
        atomic_intptr_t : atomic_is_lock_free_intptr_t, \
        const atomic_intptr_t : atomic_is_lock_free_intptr_t, \
        atomic_uintptr_t : atomic_is_lock_free_uintptr_t, \
        const atomic_uintptr_t : atomic_is_lock_free_uintptr_t, \
        atomic_size_t : atomic_is_lock_free_size_t, \
        const atomic_size_t : atomic_is_lock_free_size_t, \
        atomic_ptrdiff_t : atomic_is_lock_free_ptrdiff_t, \
        const atomic_ptrdiff_t : atomic_is_lock_free_ptrdiff_t, \
        atomic_intmax_t : atomic_is_lock_free_intmax_t, \
        const atomic_intmax_t : atomic_is_lock_free_intmax_t, \
        atomic_uintmax_t: atomic_is_lock_free_uintmax_t \
    )(obj)



#else
#include <stdatomic.h>
#endif // #if defined(_MSC_VER) && !defined(__clang__)
#endif // ATOMICS_H