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

muh_int::muh_int(void) : n(0) {std::cout << "default constructor" << std::endl;}

muh_int::muh_int(int src) : n(src) {std::cout << "int constructor" << std::endl;}



//can see its own object
void	muh_int::print_muh_int(void)
{
	std::cout << "My value is: " << n << std::endl;
}

int	muh_int::operator() (void) const
{
	return (n);
}

muh_int::muh_int(const muh_int &src) : n(src()) {std::cout << "copy constructor" << std::endl;}

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

muh_int	operator+(int a, const muh_int &b)
{
	std::cout << "adding " << a << " to " << b() << std::endl;
	return (muh_int(a + b()));
}

//this is a ptr, &b is a ptr to the param object
muh_int	&muh_int::operator=(const muh_int &b)
{
	std::cout << "copy assignment" << std::endl;
	if (this != &b)
		std::cout << "free attempt" << std::endl;
	n = b();
	return (*this);
}

muh_int	&muh_int::operator=(int b)
{
	std::cout << "copying an int" << std::endl;
	n = b;
	return (*this);
}

/*
void	muh_int::operator=(const muh_int &b)
{
	n = b();
	std::cout << "operator= called" << std::endl;
}
*/
muh_int::~muh_int(void)
{
	std::cout << "me go away now: " << n << std::endl;
}
