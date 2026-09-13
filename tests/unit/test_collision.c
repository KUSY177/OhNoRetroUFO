#include "../core/collision.h"
#include <assert.h>

int main() {
    assert(rects_intersect(0,0,10,10,5,5,10,10) == 1);
    assert(rects_intersect(0,0,10,10,20,20,10,10) == 0);
    return 0;
}
