#include "Fixed.hpp"

const int	Fixed::frac = 8;

Fixed::Fixed(void) : value(0) {std::cout << "Default constructor called" << std::endl;}
Fixed::Fixed(const Fixed& src) : value(src.getRawBits()) {std::cout << "Copy constructor called" << std::endl;}
Fixed&	Fixed::operator=(const Fixed& src)
{
	if (this != &src)
		value = src.getRawBits();
	std::cout << "Copy assignment operator called" << std::endl;
	return (*this);
}
Fixed::~Fixed(void) {std::cout << "Destructor called" << std::endl;}

int	Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (value);
}
void	Fixed::setRawBits(int const raw)
{
	std::cout << "setRawBits member function called" << std::endl;
	value = raw;
}
