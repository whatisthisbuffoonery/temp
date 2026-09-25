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

	int		getRawBits(void) const;//promises not to modify class obj remember
	void	setRawBits(int const raw);

	float	toFloat(void) const;
	int		toInt(void) const;

};

std::ostream& operator<<(std::ostream& out, const Fixed& src);

#endif
