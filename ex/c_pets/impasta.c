#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <inttypes.h>

int main(void)
{
    uint32_t exp = 0x80;
    uint32_t mantissa = 0;

    uint32_t bits = (exp << 23) | mantissa;

    float a;
    memcpy(&a, &bits, sizeof a);

    printf("bits = 0x%08" PRIx32 "\n", bits);
    printf("a    = %.9e\n", a);
}
