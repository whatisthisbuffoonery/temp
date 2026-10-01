#include "Point.hpp"

Point::Point(void) : x(0), y(0) {}
Point::Point(const Point& src) : x(src.getx()), y(src.gety()) {}
Point&	Point::operator=(const Point& src)
{
	(void) src;
	std::cout << "what are we doin here" << std::endl;
	return (*this);
}
Point::~Point(void) {}

Point::Point(const float& srcx, const float& srcy) : x(srcx), y(srcy) {}

Fixed	Point::getx(void) const {return (x);}
Fixed	Point::gety(void) const {return (y);}
