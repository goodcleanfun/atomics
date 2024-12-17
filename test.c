#include <stdio.h>
#include <stdlib.h>

#include "greatest/greatest.h"
#include "threading/threading.h"

#include "atomics.h"

// Shared variables for multithreading tests
atomic_int counter = 0;
atomic_int signal_flag = 0;

// Basic load/store test
TEST atomic_load_store_test(void) {
    atomic_int a;
    atomic_init(&a, 10);

    atomic_store(&a, 20);
    ASSERT_EQ(20, atomic_load(&a));

    atomic_store(&a, -5);
    ASSERT_EQ(-5, atomic_load(&a));

    PASS();
}

// Fetch-add and fetch-subtract test
TEST atomic_fetch_add_sub_test(void) {
    atomic_int a;
    atomic_init(&a, 0);

    ASSERT_EQ(0, atomic_fetch_add(&a, 10)); // Fetch returns old value
    ASSERT_EQ(10, atomic_load(&a));        // New value is updated

    ASSERT_EQ(10, atomic_fetch_sub(&a, 5));
    ASSERT_EQ(5, atomic_load(&a));

    PASS();
}

TEST atomic_fetch_xor_test(void) {
    atomic_int a;
    atomic_init(&a, 0);

    ASSERT_EQ(0, atomic_fetch_xor(&a, 0));
    ASSERT_EQ(0, atomic_load(&a));

    ASSERT_EQ(0, atomic_fetch_xor(&a, 1));
    ASSERT_EQ(1, atomic_load(&a));

    ASSERT_EQ(1, atomic_fetch_xor(&a, 1));
    ASSERT_EQ(0, atomic_load(&a));

    PASS();
}

TEST atomic_flag_test(void) {
    atomic_flag flag = ATOMIC_FLAG_INIT;

    ASSERT_FALSE(atomic_flag_test_and_set(&flag));
    ASSERT(atomic_flag_test_and_set(&flag));
    atomic_flag_clear(&flag);
    ASSERT_FALSE(atomic_flag_test_and_set(&flag));

    PASS();
}

// Compare-and-swap test
TEST atomic_compare_exchange_test(void) {
    atomic_int a;
    atomic_init(&a, 42);
    int expected = 42;
    int desired = 100;

    ASSERT(atomic_compare_exchange_strong(&a, &expected, desired));
    ASSERT_EQ(100, atomic_load(&a));

    expected = 50;
    desired = 200;
    ASSERT_FALSE(atomic_compare_exchange_strong(&a, &expected, desired));
    ASSERT_EQ(100, atomic_load(&a));
    ASSERT_EQ(100, expected);

    PASS();
}

// Signal fence test
TEST atomic_signal_fence_test(void) {
    signal_flag = 0;

    atomic_signal_fence(memory_order_release);
    signal_flag = 1;
    atomic_signal_fence(memory_order_acquire);

    ASSERT_EQ(1, signal_flag);

    PASS();
}

int increment_counter(void *arg) {
    (void)arg;
    for (int i = 0; i < 1000; i++) {
        atomic_fetch_add(&counter, 1);
    }
    return 0;
}

TEST atomic_multithread_test(void) {
    thrd_t threads[10];

    counter = 0;
    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(thrd_success, thrd_create(&threads[i], increment_counter, NULL));
    }
    for (int i = 0; i < 10; i++) {
        thrd_join(threads[i], NULL);
    }

    ASSERT_EQ(10000, atomic_load(&counter)); // 10 threads x 1000 increments each

    PASS();
}


// Main test suite
SUITE(atomic_compat_tests) {
    RUN_TEST(atomic_load_store_test);
    RUN_TEST(atomic_fetch_add_sub_test);
    RUN_TEST(atomic_fetch_xor_test);
    RUN_TEST(atomic_flag_test);
    RUN_TEST(atomic_compare_exchange_test);
    RUN_TEST(atomic_signal_fence_test);
    RUN_TEST(atomic_multithread_test);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(atomic_compat_tests);

    GREATEST_MAIN_END();
}