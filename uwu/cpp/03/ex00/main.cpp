#include "ClapTrap.hpp"

int	main(void)
{
	ClapTrap	Harl = ClapTrap();

	while (Harl.getenergy() > 0)
		Harl.attack("the wall");
	Harl.attack("the wall");
}
