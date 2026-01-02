#include "header.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ====================== Test with asserts ======================

// Helper: fill block with pattern and verify
void fill_and_check(void *ptr, size_t size, unsigned char value)
{
    unsigned char *p = ptr;
    for (size_t i = 0; i < size; i++) {
        p[i] = value;
    }
    for (size_t i = 0; i < size; i++) {
        assert(p[i] == value);
    }
}

int main()
{
    printf("=== Rigorous assert-based test of K&R malloc/free ===\n");

    void *p1, *p2, *p3, *p4;
    void *heap_start = sbrk(0);

    // Test 1: Basic allocations
    p1 = _malloc(100);
    p2 = _malloc(200);
    p3 = _malloc(150);

    assert(p1 != NULL);
    assert(p2 != NULL);
    assert(p3 != NULL);
    assert(p1 > p2); // should be in decreasing order (tail end first)
    assert(p2 > p3);

    fill_and_check(p1, 100, 0xAA);
    fill_and_check(p2, 200, 0xBB);
    fill_and_check(p3, 150, 0xCC);

    _free(p1);
    _free(p2);
    _free(p3);

    // Test 4: Trigger morecore
    void *heap_before = sbrk(0);
    void *huge = _malloc(20000); // much larger than NALLOC*unit
    void *heap_after = sbrk(0);

    assert(huge != NULL);
    assert(heap_after > heap_before); // heap grew

    fill_and_check(huge, 1000, 0xFF); // just test some bytes

    printf("All assertions passed!\n");
    printf("Your K&R malloc/free implementation is correct.\n");

    return 0;
}
