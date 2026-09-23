#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void)
{
	uint32_t	exp = 0x80000000;
	uint32_t	mantissa = 0x00000000000000000000001;

	uint32_t	bruh = (exp << 23) | mantissa;
	float		a;

	memcpy(&a, &bruh, sizeof(float));
	printf("%f\n", a);
}
