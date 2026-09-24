#ifndef FIXED_H
# define FIXED_H

# include <iostream>
//# include <string>

class Fixed
{
private:
	int					value;
	static const int	frac;
public:
	Fixed(void);
	Fixed(const Fixed& src);
	Fixed&	operator=(const Fixed& src);
	~Fixed(void);

	int		getRawBits(void) const;//promises not to modify class obj remember
	void	setRawBits(int const raw);
};

#endif
