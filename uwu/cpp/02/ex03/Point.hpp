#ifndef POINT_HPP
# define POINT_HPP

# include "Fixed.hpp"

class Point
{
private:
	Fixed const	x;
	Fixed const	y;
public:
	Point(void);
	Point(const Point& src);
	Point&	operator=(const Point& src);
	~Point(void);

	Point(const float& srcx, const float& srcy);

	Fixed	getx(void) const;
	Fixed	gety(void) const;
};

#endif
