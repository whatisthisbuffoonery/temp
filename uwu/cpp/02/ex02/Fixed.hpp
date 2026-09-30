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

	static Fixed&		min(Fixed& a, Fixed& b);
	static Fixed&		max(Fixed& a, Fixed& b);
	static const Fixed&	min(const Fixed& a, const Fixed& b);
	static const Fixed&	max(const Fixed& a, const Fixed& b);

	Fixed&	operator++(void);
	Fixed&	operator--(void);
	Fixed	operator++(int bruh);
	Fixed	operator--(int bruh);
};

std::ostream& operator<<(std::ostream& out, const Fixed& src);

Fixed	operator+(const Fixed& a, const Fixed& b);
Fixed	operator-(const Fixed& a, const Fixed& b);
Fixed	operator*(const Fixed& a, const Fixed& b);
Fixed	operator/(const Fixed& a, const Fixed& b);

Fixed	operator-(const Fixed& src);//eval would be painful without
Fixed	operator+(const Fixed& src);

int	operator>(const Fixed& a, const Fixed& b);
int	operator<(const Fixed& a, const Fixed& b);
int	operator==(const Fixed& a, const Fixed& b);
int	operator!=(const Fixed& a, const Fixed& b);
int	operator>=(const Fixed& a, const Fixed& b);
int	operator<=(const Fixed& a, const Fixed& b);

#endif
