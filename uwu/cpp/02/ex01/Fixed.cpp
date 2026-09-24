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

Fixed::Fixed(const int src)
{
	unsigned int	sign = (src < 0);
	unsigned int	u = (unsigned int) src;
	value = (sign << ((sizeof(unsigned int) * CHAR_BIT) - 1)) | ((u & (UINT_MAX >> (8 + 1))) << 8);
	std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float src)
{
	unsigned int	sign = (src < 0);
	unsigned int	u;
	int				b = (sizeof(unsigned int) * CHAR_BIT) - (8 + 1);

	std::memcpy(&u, &src, sizeof(unsigned int));
	unsigned int exp = (u & ((UINT_MAX >> 1) & ((UINT_MAX >> man_bits) << (man_bits + 1))

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


