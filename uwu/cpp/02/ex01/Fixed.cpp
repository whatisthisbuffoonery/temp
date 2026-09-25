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
	if (sign)
		u = 0u - u;
	value = (sign << ((sizeof(unsigned int) * CHAR_BIT) - 1)) | ((u & (UINT_MAX >> (frac + 1))) << frac);
	std::cout << "Int constructor called" << std::endl;
}

static int	find_shift(int *shift, int exp, int local_exp, int frac)
{
	*shift = exp + (-127) + local_exp + frac;
	int	tol_U = (sizeof(unsigned int) * CHAR_BIT);
	return (0 <= *shift && *shift < tol_U - 1);//-8 < n < 2^(32 - 8) //thats the sign bit aaaaa
}

Fixed::Fixed(const float src)
{
	std::cout << "Float constructor called" << std::endl;
	if (!src)
	{
		value = 0;
		return ;
	}
	unsigned int	sign = (src < 0);
	unsigned int	u;
	int				man_bits = (sizeof(unsigned int) * CHAR_BIT) - (8 + 1);
	unsigned int	curr_bit = 1;

	std::memcpy(&u, &src, sizeof(unsigned int));
	unsigned int exp = (u & (UINT_MAX >> 1)) >> man_bits;
	unsigned int mantissa = u & (UINT_MAX >> (8 + 1));
	int	i = 0;
	unsigned int t = 0;
	int	shift = 0;
	int	round_up = 0;
	while (i <= man_bits)
	{
		if ((mantissa & curr_bit || i == man_bits)
			&& find_shift(&shift, exp, i - man_bits, frac))
			t |= 1 << shift;
		else if (shift == -1)
			round_up = 1;
		i ++;
		curr_bit *= 2;
	}
	t |= (sign << ((sizeof(unsigned int) * CHAR_BIT) - 1));
	value = t + round_up;
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

float	Fixed::toFloat(void) const
{
	int				size_bits = sizeof(unsigned int) * CHAR_BIT;
	int				i = 1 + 1;

	int				sign = (value > INT_MAX);
	while (i <= size_bits)
	{
		if (value & (1 << (size_bits - i)))
			break ;
		i ++;
	}
	if (i > size_bits)
		return (0.0f);
	int 			exp = 127 + size_bits + (-frac)/*8*/ + (-i)/*size_bits*/;
	unsigned int	mantissa = 0;
	i ++;
	int				mantissa_size = size_bits - (1 + frac);
	int				mantissa_bit = mantissa_size - 1;
	while (i <= size_bits && mantissa_bit >= 0)
	{
		if (value & (1 << (size_bits - i)))
			mantissa |= 1 << mantissa_bit;
		i ++;
		mantissa_bit --;
	}
	unsigned int	bits = (sign << (size_bits - 1)) | (exp << mantissa_size) | mantissa;
	float			ret;
	std::memcpy(&ret, &bits, sizeof(float));
	return (ret);
}

int	Fixed::toInt(void) const
{
	int				sign = (value > INT_MAX);
	unsigned int	bits = 0;
	unsigned int	u = value & (UINT_MAX >> 1);

	bits |= (u >> frac);
	if (sign)
		bits = 0u - bits;
	int				ret;
	std::memcpy(&ret, &bits, sizeof(int));
	return (ret);
}

std::ostream&	operator<<(std::ostream& out, const Fixed& src)
{
	out << src.toFloat();
	return (out);
}
