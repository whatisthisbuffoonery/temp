#include "Point.hpp"

bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed	ax = a.getx();
	Fixed	ay = a.gety();
	Fixed	bx = b.getx();
	Fixed	by = b.gety();
	Fixed	cx = c.getx();
	Fixed	cy = c.gety();
	Fixed	px = point.getx();
	Fixed	py = point.gety();

	Fixed	d1 = ((px - bx) * (ay - by)) - ((ax - bx) * (py - by));
	Fixed	d2 = ((px - cx) * (by - cy)) - ((bx - cx) * (py - cy));
	Fixed	d3 = ((px - ax) * (cy - ay)) - ((cx - ax) * (py - ay));

	int		cond[3] = {(d1.getRawBits() > INT_MAX), (d2.getRawBits() > INT_MAX), (d3.getRawBits() > INT_MAX)};
	return (cond[0] == cond[1] && cond[1] == cond[2]);
}
