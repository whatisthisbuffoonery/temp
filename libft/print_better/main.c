#include "header_mand.h"
#include <limits.h>

int main(void)
{
/*
	ft_printf("%c\n", 'a');
	ft_printf("%s\n", "hello");
	ft_printf("%p\n", (void *) 0x123);
	ft_printf("%d\n", 42);
	ft_printf("%i\n", -123);
	ft_printf("%u\n", 4294967295U);
	ft_printf("%x\n", 255);
	ft_printf("%X\n", 255);


	ft_printf("%s\n", "");
	ft_printf("%s\n", NULL);
	ft_printf("%c\n", '\0');
	ft_printf("%d\n", INT_MIN);
	ft_printf("%d\n", INT_MAX);
	ft_printf("%u\n", 0);
	ft_printf("%u\n", UINT_MAX);
	ft_printf("%x\n", 0);
	ft_printf("%x\n", 0xDEADBEEF);
	ft_printf("%X\n", 0XDEADBEEF);
*/

	ft_printf("%s %% %d %% %x %% %c\n", "test", 42, 255, '!');
	ft_printf("%X %X %X\n", (void *) 0xface, (void *) 0xa, (void *) 0xbed);
/*
	ft_printf("%%");
	ft_printf("\n%%\n");
	ft_printf("%%\n");
	ft_printf("%%%%%%%%");
	ft_printf("\n%%%%%%%%\n");
	ft_printf("%%%%%%%%\n");

	ft_printf("%%%d", 42);
	ft_printf("\n%%%d\n%d", 43, 44);
	ft_printf("%d%%\n", 45);
	ft_printf("%%%%%%%%");
	ft_printf("\n%%%%%%%%\n");
	ft_printf("%%%%%%%%\n");
*/
}
