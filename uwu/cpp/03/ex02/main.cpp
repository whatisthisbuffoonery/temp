#include "ScavTrap.hpp"
#include "FragTrap.hpp"

//omfg remember to put a main file in ex00
//plss put energy exhaustion in both
int	main(void)
{
	FragTrap	bert("bert");

	while (bert.getenergy())
		bert.attack("the wall");
	bert.attack("the wall");

	std::cout << "=======" << std::endl;

	ScavTrap	bob("bob");

	bob.guardGate();
	bob.attack("the wall");
	bob.takeDamage(10);

	std::cout << "=======" << std::endl;

	bert.highFivesGuys();
}
