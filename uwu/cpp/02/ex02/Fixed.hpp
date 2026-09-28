#ifndef FIXED_H
# define FIXED_H

# include <iostream>
# include <cstring>
# include <climits>

class Fixed
{
private:
	unsigned int		value;
	static const int	frac;
public:
	Fixed(void);
	Fixed(const Fixed& src);
	Fixed&	operator=(const Fixed& src);

	Fixed(const int src);
	Fixed(const float src);

	~Fixed(void);

	unsigned int	getRawBits(void) const;//promises not to modify class obj remember
	void			setRawBits(unsigned int const raw);

	float	toFloat(void) const;
	int		toInt(void) const;

};

std::ostream& operator<<(std::ostream& out, const Fixed& src);

Fixed	operator+(const Fixed& a, const Fixed& b);
Fixed	operator-(const Fixed& a, const Fixed& b);
Fixed	operator*(const Fixed& a, const Fixed& b);
Fixed	operator/(const Fixed& a, const Fixed& b);

Fixed	operator-(const Fixed& src);//eval would be painful without

int	operator>(const Fixed& a, const Fixed& b);
int	operator<(const Fixed& a, const Fixed& b);
int	operator==(const Fixed& a, const Fixed& b);
int	operator!=(const Fixed& a, const Fixed& b);
int	operator>=(const Fixed& a, const Fixed& b);
int	operator<=(const Fixed& a, const Fixed& b);

#endif
