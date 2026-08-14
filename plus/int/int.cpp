#include "int.hpp"

//muh_int::muh_int(void) : n{} //cpp11 shorthand notation

/*
   //if any of the class members were themselves classes,
   this runs the 0 argument constructor for each one
   before the first line hits (n = src).
   calling memory allocation that way can be undesirable

muh_int::muh_int(int src)
{
	n = src;
}
*/

muh_int::muh_int(void) : n(0) {std::cout << "no arg\n";}

muh_int::muh_int(int src) : n(src) {std::cout << "one arg\n";}

//can see its own object
void	muh_int::print_muh_int(void)
{
	std::cout << "My value is: " << n << "\n";
}

int	muh_int::operator() (void)
{
	return (n);
}

//belongs to a in a + b
muh_int	muh_int::operator+ (muh_int b)
{
	muh_int	ret(n + b());
	std::cout << "adding " << n << " to " << b() << "\n";
	return (ret);
}

void	muh_int::operator= (muh_int b)
{
	n = b();
	std::cout << "operator= called\n";
}

muh_int::~muh_int(void)
{
	std::cout << "me go away now: " << n << "\n";
}
