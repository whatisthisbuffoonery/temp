#include "Fixed.hpp"

int	main(void)
{
	Fixed	a;
	Fixed const	b(Fixed(5.05f) * Fixed(2));

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;

	std::cout << b << std::endl;

	std::cout << Fixed::max(a, b) << std::endl;

	Fixed	c(Fixed(1) / Fixed(2.1f));
	std::cout << c << std::endl;
	Fixed	d(Fixed(1.3f) * Fixed(2.1f));
	std::cout << d << std::endl;

	return 0;
}
