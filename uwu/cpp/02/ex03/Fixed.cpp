#include "Fixed.hpp"

const int	Fixed::frac = 8;

const int	size_bits = sizeof(unsigned int) * CHAR_BIT;

static void	set_sign_magnitude(unsigned int *sign, unsigned int *bits_a, unsigned int *bits_b)
{
	*sign = ((*bits_a > INT_MAX) != (*bits_b > INT_MAX));
	*bits_a &= (UINT_MAX >> 1);
	*bits_b &= (UINT_MAX >> 1);
}

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
	value = (sign << (size_bits - 1)) | ((u & (UINT_MAX >> (frac + 1))) << frac);
	std::cout << "Int constructor called" << std::endl;
}

static int	find_shift(int *shift, int exp, int local_exp, int frac)
{
	*shift = exp + (-127) + local_exp + frac;
	return (0 <= *shift && *shift < size_bits - 1);//-8 < n < 2^(32 - 8) //thats the sign bit aaaaa
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
	int				man_bits = size_bits - (8 + 1);
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
	t |= (sign << (size_bits - 1));
	value = t + round_up;
}

Fixed::~Fixed(void) {std::cout << "Destructor called" << std::endl;}

unsigned int	Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (value);
}

void	Fixed::setRawBits(unsigned int const raw)
{
	std::cout << "setRawBits member function called" << std::endl;
	value = raw;
}

float	Fixed::toFloat(void) const
{
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

Fixed&	Fixed::min(Fixed& a, Fixed& b)
{
	if (a < b)
		return (a);
	return (b);
}

Fixed&	Fixed::max(Fixed& a, Fixed& b)
{
	if (a > b)
		return (a);
	return (b);
}

const Fixed&	Fixed::min(const Fixed& a, const Fixed& b)
{
	if (a < b)
		return (a);
	return (b);
}

const Fixed&	Fixed::max(const Fixed& a, const Fixed& b)
{
	if (a > b)
		return (a);
	return (b);
}

Fixed&	Fixed::operator++(void)
{
	value += 1;
	return (*this);
}

Fixed&	Fixed::operator--(void)
{
	value -= 1;
	return (*this);
}

Fixed	Fixed::operator++(int bruh)
{
	(void) bruh;
	Fixed	ret = *this;
	value += 1;
	return (ret);
}

Fixed	Fixed::operator--(int bruh)
{
	(void) bruh;
	Fixed	ret = *this;
	value -= 1;
	return (ret);
}

std::ostream&	operator<<(std::ostream& out, const Fixed& src)
{
	out << src.toFloat();
	return (out);
}

Fixed	operator-(const Fixed& src)
{
	unsigned int	bits;

	bits = src.getRawBits() ^ (1 << (size_bits - 1));
	Fixed	ret;
	ret.setRawBits(bits);
	return (ret);
}

Fixed	operator+(const Fixed& src) {return (src);}

Fixed	operator+(const Fixed& a, const Fixed& b)
{
	int				carry = 0;
	int				i = 0;
	unsigned int	bits = 0;
	unsigned int	bits_a = a.getRawBits();
	unsigned int	bits_b = b.getRawBits();
	int				sum;

	if ((bits_a >> (size_bits - 1)) != (bits_b >> (size_bits - 1)))
	{
		Fixed	temp = -b;
		return (a - temp);//I would otherwise have 4 of plus and minus each
	}
	while (i < size_bits - 1)//sign bit
	{
		sum = ((bits_a >> i) & 1u) + ((bits_b >> i) & 1u) + carry;
		if (sum & 1u)//no more modulo
			bits |= 1 << i;
		carry = (sum >= 2);
		i ++;
	}
	bits |= bits_a & (1u << (size_bits - 1));
	Fixed	ret;
	ret.setRawBits(bits);
	return (ret);
}

// + +: subtract
// + -: pass -b to add
// - +: pass -b to add
// - -: subtract

//subtract underflow: flip sign and use leftover
Fixed	operator-(const Fixed& a, const Fixed& b)
{
	unsigned int	bits_a = a.getRawBits();
	unsigned int	bits_b = b.getRawBits();
	unsigned int	bits = 0;
	int				i = 0;
	int				diff;
	int				borrow = 0;

	if ((bits_a >> (size_bits - 1)) != (bits_b >> (size_bits - 1)))
	{
		Fixed	temp = -b;
		return (a + temp);
	}
	int	flag = ((bits_a & (UINT_MAX >> 1)) < (bits_b & (UINT_MAX >> 1)));
	if (flag)
	{
		bits = bits_b - bits_a;
		bits_a ^= 1u << (size_bits - 1);
	}
	while (!flag && i < size_bits - 1)
	{
		diff = static_cast<int>((bits_a >> i) & 1u)
				- static_cast<int>((bits_b >> i) & 1u)
				- borrow;
		borrow = (diff < 0);
		if (borrow)
			diff += 2;
		if (diff)
			bits |= 1u << i;
		i ++;
	}
	bits |= bits_a & (1u << (size_bits - 1));
	Fixed	ret;
	ret.setRawBits(bits);
	return (ret);
}

Fixed	operator*(const Fixed& a, const Fixed& b)
{
	unsigned int	sign;
	unsigned int	bits_a = a.getRawBits();
	unsigned int	bits_b = b.getRawBits();

	set_sign_magnitude(&sign, &bits_a, &bits_b);
	Fixed	ret;
	ret.setRawBits(((bits_a * bits_b) >> 8) | (sign << (size_bits - 1)));
	return (ret);
}

Fixed	operator/(const Fixed& a, const Fixed& b)
{
	unsigned int	sign;
	unsigned int	bits_a = a.getRawBits();
	unsigned int	bits_b = b.getRawBits();
	unsigned int	bits = 0;
	unsigned int	t = 0;
	int				i = 0 + 1;
	int				lim = size_bits - 1;

	set_sign_magnitude(&sign, &bits_a, &bits_b);
	while (i <= lim + 8)
	{
		t = (t << 1) + ((lim + (8 - i) >= 0) && ((bits_a >> (lim - i)) & 1u));
		if (t >= bits_b)
		{
			t -= bits_b;
			if (lim + (8 - i) >= 0 && lim + (8 - i) < size_bits)
			bits |= 1u << (lim + (8 - i));
		}
		i ++;
	}
	Fixed	ret;
	ret.setRawBits((bits + (t >= bits_b - t)) | (sign << (size_bits - 1)));
	return (ret);
}

int	operator==(const Fixed& a, const Fixed& b)
{
	unsigned int	bits_a = a.getRawBits();
	unsigned int	bits_b = b.getRawBits();
	return (bits_a == bits_b
		|| ((bits_a & (UINT_MAX >> 1)) == (bits_b & (UINT_MAX >> 1))
			&& !(bits_a & (UINT_MAX >> 1))));
}

int	operator!=(const Fixed& a, const Fixed& b)
{
	unsigned int	bits_a = a.getRawBits();
	unsigned int	bits_b = b.getRawBits();
	if ((bits_a & (UINT_MAX >> 1)) == (bits_b & (UINT_MAX >> 1))
			&& !(bits_a & (UINT_MAX >> 1)))
		return (0);
	return (bits_a != bits_b);
}

int	operator>(const Fixed& a, const Fixed& b)
{
	int	sign_a;
	int	sign_b;
	unsigned int	bits_a;
	unsigned int	bits_b;

	bits_a = a.getRawBits();
	bits_b = b.getRawBits();
	sign_a = (bits_a > INT_MAX);
	sign_b = (bits_b > INT_MAX);
	if ((bits_a & (UINT_MAX >> 1)) == (bits_b & (UINT_MAX >> 1))
		&& !(bits_a & (UINT_MAX >> 1)))//-ve 0 and +ve 0 are the same
		return (0);
	else if (sign_a != sign_b)
		return (sign_a < sign_b);
	else if (sign_a)
		return (bits_a < bits_b);
	return (bits_a > bits_b);
}

int	operator>=(const Fixed& a, const Fixed& b)
{
	int	sign_a;
	int	sign_b;
	unsigned int	bits_a;
	unsigned int	bits_b;

	bits_a = a.getRawBits();
	bits_b = b.getRawBits();
	sign_a = (bits_a > INT_MAX);
	sign_b = (bits_b > INT_MAX);
	if ((bits_a & (UINT_MAX >> 1)) == (bits_b & (UINT_MAX >> 1))
		&& !(bits_a & (UINT_MAX >> 1)))
		return (1);
	else if (sign_a != sign_b)
		return (sign_a < sign_b);
	else if (sign_a)
		return (bits_a <= bits_b);
	return (bits_a >= bits_b);
}

int	operator<(const Fixed& a, const Fixed& b)
{
	int	sign_a;
	int	sign_b;
	unsigned int	bits_a;
	unsigned int	bits_b;

	bits_a = a.getRawBits();
	bits_b = b.getRawBits();
	sign_a = (bits_a > INT_MAX);
	sign_b = (bits_b > INT_MAX);
	if ((bits_a & (UINT_MAX >> 1)) == (bits_b & (UINT_MAX >> 1))
		&& !(bits_a & (UINT_MAX >> 1)))
		return (0);
	else if (sign_a != sign_b)
		return (sign_a > sign_b);
	else if (sign_a)
		return (bits_a > bits_b);
	return (bits_a < bits_b);
}

int	operator<=(const Fixed& a, const Fixed& b)
{
	int	sign_a;
	int	sign_b;
	unsigned int	bits_a;
	unsigned int	bits_b;

	bits_a = a.getRawBits();
	bits_b = b.getRawBits();
	sign_a = (bits_a > INT_MAX);
	sign_b = (bits_b > INT_MAX);
	if ((bits_a & (UINT_MAX >> 1)) == (bits_b & (UINT_MAX >> 1))
		&& !(bits_a & (UINT_MAX >> 1)))
		return (1);
	else if (sign_a != sign_b)
		return (sign_a > sign_b);
	else if (sign_a)
		return (bits_a >= bits_b);
	return (bits_a <= bits_b);
}
