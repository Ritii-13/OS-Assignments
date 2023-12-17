#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main() {
    uint64_t count = 1;
    while (count < (1ULL << 32)) {
        count++;
    }
    printf("Child Process 1: Counted up to %" PRIu64 "\n", count);
    return 0;
}
