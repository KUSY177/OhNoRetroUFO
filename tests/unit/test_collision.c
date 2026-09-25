#include "collision.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    // Пересекаются
    assert(rects_intersect(10, 10, 20, 20, 15, 15, 20, 20) == 1);

    // Не пересекаются
    assert(rects_intersect(0, 0, 10, 10, 20, 20, 10, 10) == 0);

    // Касаются краями
    assert(rects_intersect(0, 0, 10, 10, 10, 0, 10, 10) == 1);

    printf("test_collision: OK\n");
    return 0;
}
