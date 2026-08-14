#include "int.hpp"

int	main(void)
{
	muh_int	a;
	muh_int	b(1);
	muh_int	c(2);
	muh_int d = c + b;

	a.print_muh_int();
	b.muh_int::print_muh_int(); //no diff
	d.print_muh_int();

	muh_int e;
	e = d;
	e.print_muh_int();
}
