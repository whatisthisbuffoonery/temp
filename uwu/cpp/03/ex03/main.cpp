#include "DiamondTrap.hpp"

//omfg remember to put a main file in ex00
//plss put energy exhaustion in both
int	main(void)
{
	DiamondTrap	david("david");

	while (david.getenergy())
		david.attack("the wall");
	david.attack("the wall");

	std::cout << "=======" << std::endl;

	ScavTrap	bob("bob");

	bob.guardGate();
	bob.attack("the wall");
	bob.takeDamage(10);

	std::cout << "=======" << std::endl;

	FragTrap	bert("bert");

	bert.highFivesGuys();

	std::cout << "=======" << std::endl;

	david.whoAmI();
	DiamondTrap	dave = david;
	dave.whoAmI();
}
