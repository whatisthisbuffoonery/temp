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

muh_int::muh_int(void) : n(0) {std::cout << "no arg" << std::endl;}

muh_int::muh_int(int src) : n(src) {std::cout << "one arg" << std::endl;}

//can see its own object
void	muh_int::print_muh_int(void)
{
	std::cout << "My value is: " << n << std::endl;
}

int	muh_int::operator() (void) const
{
	return (n);
}

//belongs to a in a + b
/*
//spawns an extra copy for b, not gud
muh_int	muh_int::operator+ (muh_int b)
{
	muh_int	ret(n + b());
	std::cout << "adding " << n << " to " << b() << "\n";
	return (ret);
}
*/

muh_int	operator+(const muh_int &a, const muh_int &b)
{
	std::cout << "adding " << a() << " to " << b() << std::endl;
	return (muh_int(a() + b()));
}

muh_int	operator+(const muh_int &a, int b)
{
	std::cout << "adding " << a() << " to " << b << std::endl;
	return (muh_int(a() + b));
}

void	muh_int::operator=(muh_int b)
{
	n = b();
	std::cout << "operator= called" << std::endl;
}

muh_int::~muh_int(void)
{
	std::cout << "me go away now: " << n << std::endl;
}
