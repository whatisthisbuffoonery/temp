#include "Harl.hpp"

int	main(int c, char **v)
{
	if (c != 2)
		return (1);
	Harl	h;
	h.complain(std::string(v[1]));
}
