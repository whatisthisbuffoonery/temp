#include "FragTrap.hpp"

//?????
FragTrap::FragTrap(void) : ClapTrap("A nobody", 100, 100, 30);
{std::cout << "Frag default constructor" << std::endl;}
FragTrap::FragTrap(const FragTrap& src) : ClapTrap(src.getname(), src.gethp(), src.getenergy(), src.getattack());
{std::cout << "Frag copy constructor" << std::endl;}
FragTrap::~FragTrap(void) {}
FragTrap&	FragTrap::operator=(const FragTrap& src)
{
	std::cout << "Frag copy assignment operator" << std::endl;
	if (this != &src)
	{
		Name = src.getname();
		HitPoints = src.gethp();
		EnergyPoints = src.getenergy();
		AttackDamage = src.getattack();
	}
	return (*this);
}
