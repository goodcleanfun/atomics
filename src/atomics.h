#ifndef ATOMICS_H
#define ATOMICS_H

#if defined(_MSC_VER) && !defined(__clang__)
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

typedef _Atomic _Bool atomic_bool;
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
typedef void * _Atomic atomic_ptr;

#define ATOMICS_CONCAT_(a, b) a##b
#define ATOMICS_CONCAT(a, b) ATOMICS_CONCAT_(a, b)


#if UINTPTR_MAX == 0xFFFFFFFFFFFFFFFFull
#define PTR_INTRINSIC __int64
#define PTR_SIZE i64
#elif UINTPTR_MAX == 0xFFFFFFFFu
#define PTR_INTRINSIC __int32
#define PTR_SIZE i32
#else
#error unable to determine pointer width
#endif

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

static inline char atomic_load_char(const atomic_char *obj) {
    char val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
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

static inline void *atomic_load_ptr(const atomic_ptr *obj) {
    void *val; _ReadBarrier(); val = *obj; _ReadWriteBarrier(); return val;
}

#define atomic_load(obj) \
    _Generic((obj), \
        atomic_char *: atomic_load_char, \
        atomic_uchar *: atomic_load_uchar, \
        atomic_short *: atomic_load_short, \
        atomic_ushort *: atomic_load_ushort, \
        atomic_int *: atomic_load_int, \
        atomic_uint *: atomic_load_uint, \
        atomic_long *: atomic_load_long, \
        atomic_ulong *: atomic_load_ulong, \
        atomic_llong *: atomic_load_llong, \
        atomic_ullong *: atomic_load_ullong, \
        atomic_ptr *: atomic_load_ptr \
    )(obj)

#define atomic_load_explicit(obj, order) atomic_load(obj)

static __int8 ms_interlocked_exchange_i8(__int8 volatile *addr, __int8 desired) {
    return _InterlockedExchange8(addr, desired);
}

static __int16 ms_interlocked_exchange_i16(__int16 volatile *addr, __int16 desired) {
    return _InterlockedExchange16((__int16 *)addr, desired);
}

static __int32 ms_interlocked_exchange_i32(__int32 volatile *addr, __int32 desired) {
    return _InterlockedExchange((long *)addr, desired);
}

static __int64 ms_interlocked_exchange_i64(__int64 volatile *addr, __int64 desired) {
    return _InterlockedExchange64((__int64 *)addr, desired);
}

static inline atomic_exchange_char(atomic_char *obj, char desired) {
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

static inline atomic_exchange_ptr(atomic_ptr *obj, void *desired) {
    return ATOMICS_CONCAT(ms_interlocked_exchange_, PTR_SIZE)((PTR_INTRINSIC volatile *)obj, (ptrdiff_t)desired);
}


#define atomic_exchange(obj, desired) \
    _Generic((obj), \
        atomic_char *: atomic_exchange_char, \
        atomic_uchar *: atomic_exchange_uchar, \
        atomic_short *: atomic_exchange_short, \
        atomic_ushort *: atomic_exchange_ushort, \
        atomic_int *: atomic_exchange_int, \
        atomic_uint *: atomic_exchange_uint, \
        atomic_long *: atomic_exchange_long, \
        atomic_ulong *: atomic_exchange_ulong, \
        atomic_llong *: atomic_exchange_llong, \
        atomic_ullong *: atomic_exchange_ullong, \
        atomic_ptr *: atomic_exchange_ptr \
    )(obj, desired)

#define atomic_store(obj, desired) atomic_exchange(obj, desired)
#define atomic_exchange_explicit(obj, desired, order) atomic_exchange(obj, desired)
#define atomic_store_explicit(obj, desired, order) atomic_exchange(obj, desired)

#define atomic_init(ptr, val) \
    atomic_store_explicit(ptr, val, memory_order_relaxed)

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

static inline _Bool atomic_compare_exchange_char(atomic_char *obj, char *expected, char desired) {
    char cmp = *expected;
    char val = ms_interlocked_compare_exchange_i8((volatile __int8 *)obj, (__int8)val, (__int8)desired);
    return val == cmp;
}

static inline _Bool atomic_compare_exchange_uchar(atomic_uchar *obj, unsigned char *expected, unsigned char desired) {
    unsigned char cmp = *expected;
    unsigned char val = ms_interlocked_compare_exchange_i8((volatile __int8 *)obj, (__int8)val, (__int8)desired);
    return val == cmp;
}

static inline _Bool atomic_compare_exchange_short(atomic_short *obj, short *expected, short desired) {
    short cmp = *expected;
    short val = ms_interlocked_compare_exchange_i16((volatile __int16 *)obj, (__int16)val, (__int16)desired);
    return val == cmp;
}

static inline _Bool atomic_compare_exchange_ushort(atomic_ushort *obj, unsigned short *expected, unsigned short desired) {
    unsigned short cmp = *expected;
    unsigned short val = ms_interlocked_compare_exchange_i16((volatile __int16 *)obj, (__int16)val, (__int16)desired);
    return val == cmp;
}

static inline _Bool atomic_compare_exchange_int(atomic_int *obj, int *expected, int desired) {
    int cmp = *expected;
    int val = ms_interlocked_compare_exchange_i32((volatile __int32 *)obj, (__int32)val, (__int32)desired);
    return val == cmp;
}

static inline _Bool atomic_compare_exchange_uint(atomic_uint *obj, unsigned int *expected, unsigned int desired) {
    unsigned int cmp = *expected;
    unsigned int val = ms_interlocked_compare_exchange_i32((volatile __int32 *)obj, (__int32)val, (__int32)desired);
    return val == cmp;
}

static inline _Bool atomic_compare_exchange_long(atomic_long *obj, long *expected, long desired) {
    long cmp = *expected;
    long val = ms_interlocked_compare_exchange_i32((volatile __int32 *)obj, (__int32)val, (__int32)desired);
    return val == cmp;
}

static inline _Bool atomic_compare_exchange_ulong(atomic_ulong *obj, unsigned long *expected, unsigned long desired) {
    unsigned long cmp = *expected;
    unsigned long val = ms_interlocked_compare_exchange_i32((volatile __int32 *)obj, (__int32)val, (__int32)desired);
    return val == cmp;
}

static inline _Bool atomic_compare_exchange_llong(atomic_llong *obj, long long *expected, long long desired) {
    long long cmp = *expected;
    long long val = ms_interlocked_compare_exchange_i64((volatile __int64 *)obj, (__int64)val, (__int64)desired);
    return val == cmp;
}

static inline _Bool atomic_compare_exchange_ullong(atomic_ullong *obj, unsigned long long *expected, unsigned long long desired) {
    unsigned long long cmp = *expected;
    unsigned long long val = ms_interlocked_compare_exchange_i64((volatile __int64 *)obj, (__int64)val, (__int64)desired);
    return val == cmp;
}

static inline _Bool atomic_compare_exchange_ptr(atomic_ptr *obj, void **expected, void *desired) {
    ptrdiff_t cmp = *(ptrdiff_t *)expected;
    ptrdiff_t val = ATOMICS_CONCAT(ms_interlocked_compare_exchange_, PTR_SIZE)((PTR_INTRINSIC volatile *)obj, (ptrdiff_t)val, (ptrdiff_t)desired);
    return (ptrdiff_t)val == cmp;
}

#define atomic_compare_exchange_generic(obj, expected, desired) \
    _Generic((obj), \
        atomic_char *: atomic_compare_exchange_char, \
        atomic_uchar *: atomic_compare_exchange_uchar, \
        atomic_short *: atomic_compare_exchange_short, \
        atomic_ushort *: atomic_compare_exchange_ushort, \
        atomic_int *: atomic_compare_exchange_int, \
        atomic_uint *: atomic_compare_exchange_uint, \
        atomic_long *: atomic_compare_exchange_long, \
        atomic_ulong *: atomic_compare_exchange_ulong, \
        atomic_llong *: atomic_compare_exchange_llong, \
        atomic_ullong *: atomic_compare_exchange_ullong, \
        atomic_ptr *: atomic_compare_exchange_ptr \
    )(obj, expected, desired)


#define atomic_compare_exchange_strong(obj, expected, desired) atomic_compare_exchange_generic((obj), (expected), (desired))
#define atomic_compare_exchange_weak(obj, expected, desired) atomic_compare_exchange_generic((obj), (expected), (desired))

static void atomic_thread_fence(memory_order order) {
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

static void atomic_signal_fence(memory_order order) {
    (void)order;
    _ReadWriteBarrier();
}

static inline _Bool atomic_compare_exchange_explicit_char(atomic_char *obj, char *expected, char desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    _Bool ret = atomic_compare_exchange_char(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static inline _Bool atomic_compare_exchange_explicit_uchar(atomic_uchar *obj, unsigned char *expected, unsigned char desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    _Bool ret = atomic_compare_exchange_uchar(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static inline _Bool atomic_compare_exchange_explicit_short(atomic_short *obj, short *expected, short desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    _Bool ret = atomic_compare_exchange_short(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static inline _Bool atomic_compare_exchange_explicit_ushort(atomic_ushort *obj, unsigned short *expected, unsigned short desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    _Bool ret = atomic_compare_exchange_ushort(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static inline _Bool atomic_compare_exchange_explicit_int(atomic_int *obj, int *expected, int desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    _Bool ret = atomic_compare_exchange_int(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static inline _Bool atomic_compare_exchange_explicit_uint(atomic_uint *obj, unsigned int *expected, unsigned int desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    _Bool ret = atomic_compare_exchange_uint(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static inline _Bool atomic_compare_exchange_explicit_long(atomic_long *obj, long *expected, long desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    _Bool ret = atomic_compare_exchange_long(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static inline _Bool atomic_compare_exchange_explicit_ulong(atomic_ulong *obj, unsigned long *expected, unsigned long desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    _Bool ret = atomic_compare_exchange_ulong(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static inline _Bool atomic_compare_exchange_explicit_llong(atomic_llong *obj, long long *expected, long long desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    _Bool ret = atomic_compare_exchange_llong(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static inline _Bool atomic_compare_exchange_explicit_ullong(atomic_ullong *obj, unsigned long long *expected, unsigned long long desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    _Bool ret = atomic_compare_exchange_ullong(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

static inline _Bool atomic_compare_exchange_explicit_ptr(atomic_ptr *obj, void **expected, void *desired, memory_order success, memory_order failure) {
    atomic_thread_fence(success);
    _Bool ret = atomic_compare_exchange_ptr(obj, expected, desired);
    if (!ret) atomic_thread_fence(failure);
    return ret;
}

#define atomic_compare_exchange_strong_explicit_generic(obj, expected, desired, success, failure) \
    _Generic((obj), \
        atomic_char *: atomic_compare_exchange_explicit_char, \
        atomic_uchar *: atomic_compare_exchange_explicit_uchar, \
        atomic_short *: atomic_compare_exchange_explicit_short, \
        atomic_ushort *: atomic_compare_exchange_explicit_ushort, \
        atomic_int *: atomic_compare_exchange_explicit_int, \
        atomic_uint *: atomic_compare_exchange_explicit_uint, \
        atomic_long *: atomic_compare_exchange_explicit_long, \
        atomic_ulong *: atomic_compare_exchange_explicit_ulong, \
        atomic_llong *: atomic_compare_exchange_explicit_llong, \
        atomic_ullong *: atomic_compare_exchange_explicit_ullong, \
        atomic_ptr *: atomic_compare_exchange_explicit_ptr \
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

static inline char atomic_fetch_add_char(atomic_char *obj, char val) {
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

static inline void *atomic_fetch_add_ptr(atomic_ptr *obj, ptrdiff_t val) {
    return (void *)ATOMICS_CONCAT(ms_interlocked_exchange_add_, PTR_SIZE)((PTR_INTRINSIC volatile *)obj, (PTR_INTRINSIC)val);
}

#define atomic_fetch_add(obj, arg) \
    _Generic((obj), \
        atomic_char *: atomic_fetch_add_char, \
        atomic_uchar *: atomic_fetch_add_uchar, \
        atomic_short *: atomic_fetch_add_short, \
        atomic_ushort *: atomic_fetch_add_ushort, \
        atomic_int *: atomic_fetch_add_int, \
        atomic_uint *: atomic_fetch_add_uint, \
        atomic_long *: atomic_fetch_add_long, \
        atomic_ulong *: atomic_fetch_add_ulong, \
        atomic_llong *: atomic_fetch_add_llong, \
        atomic_ullong *: atomic_fetch_add_ullong, \
        atomic_ptr *: atomic_fetch_add_ptr \
    )(obj, arg)

#define atomic_fetch_sub(obj, arg) atomic_fetch_add(obj, -(arg))
#define atomic_fetch_add_explicit(obj, arg, order) atomic_fetch_add(obj, arg)
#define atomic_fetch_sub_explicit(obj, arg, order) atomic_fetch_sub(obj, arg)

#define atomic_fetch_op(name, atomic_type, type, op) \
    static inline type name(atomic_type *obj, type val) { \
        type oldval, newval; \
        do { \
            oldval = atomic_load(obj); \
            newval = oldval op val; \
        } while (!(atomic_compare_exchange_strong(obj, &oldval, newval))); \
        return oldval; \
    }

#define atomic_fetch_op_ptr(name, op) \
    static inline void *name(atomic_ptr *obj, void *arg) { \
        ptrdiff_t oldval, newval; \
        do { \
            oldval = (ptrdiff_t)atomic_load(obj); \
            newval = oldval op (ptrdiff_t)arg; \
        } while (!(atomic_compare_exchange_strong(obj, (void **)&oldval, (void *)newval))); \
        return (void *)oldval; \
    }

atomic_fetch_op(atomic_fetch_and_char, atomic_char, char, &)
atomic_fetch_op(atomic_fetch_and_uchar, atomic_uchar, unsigned char, &)
atomic_fetch_op(atomic_fetch_and_short, atomic_short, short, &)
atomic_fetch_op(atomic_fetch_and_ushort, atomic_ushort, unsigned short, &)
atomic_fetch_op(atomic_fetch_and_int, atomic_int, int, &)
atomic_fetch_op(atomic_fetch_and_uint, atomic_uint, unsigned int, &)
atomic_fetch_op(atomic_fetch_and_long, atomic_long, long, &)
atomic_fetch_op(atomic_fetch_and_ulong, atomic_ulong, unsigned long, &)
atomic_fetch_op(atomic_fetch_and_llong, atomic_llong, long long, &)
atomic_fetch_op(atomic_fetch_and_ullong, atomic_ullong, unsigned long long, &)
atomic_fetch_op_ptr(atomic_fetch_and_ptr, &)

#define atomic_fetch_and(obj, arg) \
    _Generic((obj), \
        atomic_char * : atomic_fetch_and_char, \
        atomic_uchar * : atomic_fetch_and_uchar, \
        atomic_short * : atomic_fetch_and_short, \
        atomic_ushort * : atomic_fetch_and_ushort, \
        atomic_int * : atomic_fetch_and_int, \
        atomic_uint * : atomic_fetch_and_uint, \
        atomic_long * : atomic_fetch_and_long, \
        atomic_ulong * : atomic_fetch_and_ulong, \
        atomic_llong * : atomic_fetch_and_llong, \
        atomic_ullong * : atomic_fetch_and_ullong, \
        atomic_ptr * : atomic_fetch_and_ptr \
    )(obj, arg)

#define atomic_fetch_and_explicit(obj, arg, order) atomic_fetch_and(obj, arg)

atomic_fetch_op(atomic_fetch_or_char, atomic_char, char, |)
atomic_fetch_op(atomic_fetch_or_uchar, atomic_uchar, unsigned char, |)
atomic_fetch_op(atomic_fetch_or_short, atomic_short, short, |)
atomic_fetch_op(atomic_fetch_or_ushort, atomic_ushort, unsigned short, |)
atomic_fetch_op(atomic_fetch_or_int, atomic_int, int, |)
atomic_fetch_op(atomic_fetch_or_uint, atomic_uint, unsigned int, |)
atomic_fetch_op(atomic_fetch_or_long, atomic_long, long, |)
atomic_fetch_op(atomic_fetch_or_ulong, atomic_ulong, unsigned long, |)
atomic_fetch_op(atomic_fetch_or_llong, atomic_llong, long long, |)
atomic_fetch_op(atomic_fetch_or_ullong, atomic_ullong, unsigned long long, |)
atomic_fetch_op_ptr(atomic_fetch_or_ptr, |)

#define atomic_fetch_or(obj, arg) \
    _Generic((obj), \
        atomic_char * : atomic_fetch_or_char, \
        atomic_uchar * : atomic_fetch_or_uchar, \
        atomic_short * : atomic_fetch_or_short, \
        atomic_ushort * : atomic_fetch_or_ushort, \
        atomic_int * : atomic_fetch_or_int, \
        atomic_uint * : atomic_fetch_or_uint, \
        atomic_long * : atomic_fetch_or_long, \
        atomic_ulong * : atomic_fetch_or_ulong, \
        atomic_llong * : atomic_fetch_or_llong, \
        atomic_ullong * : atomic_fetch_or_ullong, \
        atomic_ptr * : atomic_fetch_or_ptr \
    )(obj, arg)


#define atomic_fetch_or_explicit(obj, arg, order) atomic_fetch_or(obj, arg)

atomic_fetch_op(atomic_fetch_xor_char, atomic_char, char, ^)
atomic_fetch_op(atomic_fetch_xor_uchar, atomic_uchar, unsigned char, ^)
atomic_fetch_op(atomic_fetch_xor_short, atomic_short, short, ^)
atomic_fetch_op(atomic_fetch_xor_ushort, atomic_ushort, unsigned short, ^)
atomic_fetch_op(atomic_fetch_xor_int, atomic_int, int, ^)
atomic_fetch_op(atomic_fetch_xor_uint, atomic_uint, unsigned int, ^)
atomic_fetch_op(atomic_fetch_xor_long, atomic_long, long, ^)
atomic_fetch_op(atomic_fetch_xor_ulong, atomic_ulong, unsigned long, ^)
atomic_fetch_op(atomic_fetch_xor_llong, atomic_llong, long long, ^)
atomic_fetch_op(atomic_fetch_xor_ullong, atomic_ullong, unsigned long long, ^)
atomic_fetch_op_ptr(atomic_fetch_xor_ptr, ^)

#define atomic_fetch_xor(obj, arg) \
    _Generic((obj), \
        atomic_char * : atomic_fetch_xor_char, \
        atomic_uchar * : atomic_fetch_xor_uchar, \
        atomic_short * : atomic_fetch_xor_short, \
        atomic_ushort * : atomic_fetch_xor_ushort, \
        atomic_int * : atomic_fetch_xor_int, \
        atomic_uint * : atomic_fetch_xor_uint, \
        atomic_long * : atomic_fetch_xor_long, \
        atomic_ulong * : atomic_fetch_xor_ulong, \
        atomic_llong * : atomic_fetch_xor_llong, \
        atomic_ullong * : atomic_fetch_xor_ullong, \
        atomic_ptr * : atomic_fetch_xor_ptr \
    )(obj, arg)

#define atomic_fetch_xor_explicit(obj, arg, order) atomic_fetch_xor(obj, arg)

static _Bool atomic_flag_test_and_set(atomic_flag *obj) {
    unsigned char val = 0;
    return atomic_compare_exchange_strong((atomic_uchar *)&(obj->_Value), &val, 1) ? 0: 1;
}

static void atomic_flag_clear(atomic_flag* obj) {
    atomic_store_explicit((atomic_uchar *)&(obj->_Value), 0, memory_order_relaxed);
}

#define atomic_flag_test_and_set_explicit(obj, order) atomic_flag_test_and_set(obj)
#define atomic_flag_clear_explicit(obj, order) atomic_flag_clear(obj)

static inline _Bool atomic_is_lock_free_char(atomic_char *obj) { (void)obj; return 1; }
static inline _Bool atomic_is_lock_free_uchar(atomic_uchar *obj) { (void)obj; return 1; }
static inline _Bool atomic_is_lock_free_short(atomic_short *obj) { (void)obj; return 1; }
static inline _Bool atomic_is_lock_free_ushort(atomic_ushort *obj) { (void)obj; return 1; }
static inline _Bool atomic_is_lock_free_int(atomic_int *obj) { (void)obj; return 1; }
static inline _Bool atomic_is_lock_free_uint(atomic_uint *obj) { (void)obj; return 1; }
static inline _Bool atomic_is_lock_free_long(atomic_long *obj) { (void)obj; return 1; }
static inline _Bool atomic_is_lock_free_ulong(atomic_ulong *obj) { (void)obj; return 1; }
static inline _Bool atomic_is_lock_free_llong(atomic_llong *obj) { (void)obj; return 1; }
static inline _Bool atomic_is_lock_free_ullong(atomic_ullong *obj) { (void)obj; return 1; }

#define atomic_is_lock_free(obj) \
    _Generic((obj), \
        atomic_char: atomic_is_lock_free_char, \
        atomic_uchar: atomic_is_lock_free_uchar, \
        atomic_short: atomic_is_lock_free_short, \
        atomic_ushort: atomic_is_lock_free_ushort, \
        atomic_int: atomic_is_lock_free_int, \
        atomic_uint: atomic_is_lock_free_uint, \
        atomic_long: atomic_is_lock_free_long, \
        atomic_ulong: atomic_is_lock_free_ulong, \
        atomic_llong: atomic_is_lock_free_llong, \
        atomic_ullong: atomic_is_lock_free_ullong \
    )(obj)

#undef ATOMICS_CONCAT_
#undef ATOMICS_CONCAT

#else
#include <stdatomic.h>
#endif // #if defined(_MSC_VER) && !defined(__clang__)
#endif // ATOMICS_H