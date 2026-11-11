#include <stddef.h>
#include <limits.h>
#include "ft_printf.h"

void	null_string(void)
{
	ft_printf("|%.03s|\n", NULL);
	printf("|%.03s|\n", NULL);
	ft_printf("|%.3s|\n", NULL);
	printf("|%.3s|\n", NULL);
	ft_printf("|%.06s|\n", NULL);
	printf("|%.06s|\n", NULL);
	ft_printf("|%.05s|\n", NULL);
	printf("|%.05s|\n", NULL);
	ft_printf("|%5.3s|\n", NULL);
	printf("|%5.3s|\n", NULL);
}

void	char_thing(void)
{
	ft_printf("|%5%|\n");
	printf("|%5%|\n");
	ft_printf("|%5c|\n", '%');
	printf("|%5c|\n", '%');
	ft_printf("|%-5c|\n", '%');
	printf("|%-5c|\n", '%');
}

void	negative_signed(void)
{
	int	ret = 0;
	ret += ft_printf(" %d ", -9);
	ret += ft_printf(" %d ", -10);
	ret += ft_printf(" %d ", -11);
	ret += ft_printf(" %d ", -14);
	ret += ft_printf(" %d ", -15);
	ret += ft_printf(" %d ", -16);
	ret += ft_printf(" %d ", -99);
	ret += ft_printf(" %d ", -100);
	ret += ft_printf(" %d ", -101);
	ft_printf("written: %d\n", ret);
	ret = 0;
	ret += printf(" %d ", -9);
	ret += printf(" %d ", -10);
	ret += printf(" %d ", -11);
	ret += printf(" %d ", -14);
	ret += printf(" %d ", -15);
	ret += printf(" %d ", -16);
	ret += printf(" %d ", -99);
	ret += printf(" %d ", -100);
	ret += printf(" %d ", -101);
	printf("written: %d\n", ret);
	ft_printf(" %04d \n", -14);
	ft_printf(" %05d \n", -15);
	ft_printf(" %06d \n", -16);
	printf(" %04d \n", -14);
	printf(" %05d \n", -15);
	printf(" %06d \n", -16);
	ft_printf(" %4d \n", -14);
	ft_printf(" %5d \n", -15);
	ft_printf(" %6d \n", -16);
	printf(" %4d \n", -14);
	printf(" %5d \n", -15);
	printf(" %6d \n", -16);
}

void	signed_precision(void)
{
	ft_printf("1:|%.2d|\n", 5);
	printf("1:|%.2d|\n", 5);
	ft_printf("2:|%.2d|\n", -5);
	printf("2:|%.2d|\n", -5);
	ft_printf("3:|%d|\n", -5);
	printf("3:|%d|\n", -5);
}

int main(void)
{
	int	ret = 0;
	ft_printf("|%--194.54X|\n" ,3852169892u);
	printf("|%--194.54X|\n" ,3852169892u);
	null_string();
//	ft_printf("%.2u\n", 1);
//	printf("%.2u\n", 1);
	/*
	ft_printf("%#x\n", 0);
	printf("%#x\n", 0);
	*/
	/*
	ft_printf("1: %p \n", -1);
	ft_printf("2: %p \n", 1);
	ft_printf("3: %p \n", 15);
	ft_printf("4: %p \n", 16);
	ft_printf("5: %p \n", 17);
	ft_printf("6: %p %p \n", LONG_MIN, LONG_MAX);
	ft_printf("7: %p %p \n", INT_MIN, INT_MAX);
	ft_printf("8: %p %p \n", ULONG_MAX, -ULONG_MAX);
	*/
	/*
	// Null pointer — well-defined
	printf("|%p|\n", (void *)NULL);
	printf("|%p|\n", (void *)0);
	printf("|%15p|\n", (void *)NULL);
	printf("|%-15p|\n", (void *)NULL);

	// Null string — undefined behavior; avoid in portable code
	printf("|%s|\n", (char *)NULL);
	printf("|%10s|\n", (char *)NULL);
	printf("|%-10s|\n", (char *)NULL);
	printf("|%.3s|dafuq\n", (char *)NULL);

	// Safe stand-ins for null strings
	printf("|%s|\n", "");
	printf("|%10s|\n", "");
	printf("|%-10s|\n", "");
	printf("|%.3s|\n", "");
	*/
	
	ft_printf("%1d\n", 123);
	ft_printf("%1i\n", 123);
	ft_printf("%1u\n", 123);
	ft_printf("%1x\n", 123);
	ft_printf("%1X\n", 123);
	ft_printf("%2d\n", 123);
	ft_printf("%2i\n", 123);
	ft_printf("%2u\n", 123);
	ft_printf("%2x\n", 123);
	ft_printf("%2X\n", 123);
	ft_printf("%3d\n", 123);
	ft_printf("%3i\n", 123);
	ft_printf("%3u\n", 123);
	ft_printf("%3x\n", 123);
	ft_printf("%3X\n", 123);
	ft_printf("%5d\n", 123);
	ft_printf("%5i\n", 123);
	ft_printf("%5u\n", 123);
	ft_printf("%5x\n", 123);
	ft_printf("%5X\n", 123);
	ft_printf("%8d\n", 123);
	ft_printf("%8i\n", 123);
	ft_printf("%8u\n", 123);
	ft_printf("%8x\n", 123);
	ft_printf("%8X\n", 123);
	ft_printf("%10d\n", 123);
	ft_printf("%10i\n", 123);
	ft_printf("%10u\n", 123);
	ft_printf("%10x\n", 123);
	ft_printf("%10X\n", 123);
	ft_printf("%12d\n", 123);
	ft_printf("%12i\n", 123);
	ft_printf("%12u\n", 123);
	ft_printf("%12x\n", 123);
	ft_printf("%12X\n", 123);
	ft_printf("%3s\n", "hello");
	ft_printf("%3c\n", 'A');
	ft_printf("%3p\n", (void*)0x1234);
	ft_printf("%5s\n", "hello");
	ft_printf("%5c\n", 'A');
	ft_printf("%5p\n", (void*)0x1234);
	ft_printf("%8s\n", "hello");
	ft_printf("%8c\n", 'A');
	ft_printf("%8p\n", (void*)0x1234);
	ft_printf("%10s\n", "hello");
	ft_printf("%10c\n", 'A');
	ft_printf("%10p\n", (void*)0x1234);
	ft_printf("%12s\n", "hello");
	ft_printf("%12c\n", 'A');
	ft_printf("%12p\n", (void*)0x1234);
	ft_printf("%-5d\n", 123);
	ft_printf("%-5i\n", 123);
	ft_printf("%-5u\n", 123);
	ft_printf("%-5x\n", 123);
	ft_printf("%-5X\n", 123);
	ft_printf("%-5s\n", "hello");
	ft_printf("%-5c\n", 'A');
	ft_printf("%-5p\n", (void*)0x1234);
	ft_printf("%-8d\n", 123);
	ft_printf("%-8i\n", 123);
	ft_printf("%-8u\n", 123);
	ft_printf("%-8x\n", 123);
	ft_printf("%-8X\n", 123);
	ft_printf("%-8s\n", "hello");
	ft_printf("%-8c\n", 'A');
	ft_printf("%-8p\n", (void*)0x1234);
	ft_printf("%-10d\n", 123);
	ft_printf("%-10i\n", 123);
	ft_printf("%-10u\n", 123);
	ft_printf("%-10x\n", 123);
	ft_printf("%-10X\n", 123);
	ft_printf("%-10s\n", "hello");
	ft_printf("%-10c\n", 'A');
	ft_printf("%-10p\n", (void*)0x1234);
	ft_printf("%-12d\n", 123);
	ft_printf("%-12i\n", 123);
	ft_printf("%-12u\n", 123);
	ft_printf("%-12x\n", 123);
	ft_printf("%-12X\n", 123);
	ft_printf("%-12s\n", "hello");
	ft_printf("%-12c\n", 'A');
	ft_printf("%-12p\n", (void*)0x1234);
	ft_printf("%05d\n", 123);
	ft_printf("%05i\n", 123);
	ft_printf("%05u\n", 123);
	ft_printf("%05x\n", 123);
	ft_printf("%05X\n", 123);
	ft_printf("%08d\n", 123);
	ft_printf("%08i\n", 123);
	ft_printf("%08u\n", 123);
	ft_printf("%08x\n", 123);
	ft_printf("%08X\n", 123);
	ft_printf("%010d\n", 123);
	ft_printf("%010i\n", 123);
	ft_printf("%010u\n", 123);
	ft_printf("%010x\n", 123);
	ft_printf("%010X\n", 123);
	ft_printf("%012d\n", 123);
	ft_printf("%012i\n", 123);
	ft_printf("%012u\n", 123);
	
	(void) ret;
	fflush(stdout);
}
