#include "Point.hpp"

bool	bsp(Point const a, Point const b, Point const c, Point const point);

int	main(void)
{
	Point	a(1.0f, 1.0f);
	Point	b(3.0f, 3.0f);
	Point	c(1.0f, 3.0f);

	std::cout << "result: " << bsp(a, b, c, Point(1.5f, 1.5f)) << std::endl;
	return 0;
}
