#include "ScavTrap.hpp"

//omfg remember to put a main file in ex00
//plss put energy exhaustion in both
int	main(void)
{
	ScavTrap	bob("bob");

	while (bob.getenergy())
		bob.attack("the wall");
	bob.attack("the wall");

	std::cout << "======" << std::endl;

	bob.guardGate();
	bob.takeDamage(10);
	ScavTrap	tmp;
	tmp = bob;
}
