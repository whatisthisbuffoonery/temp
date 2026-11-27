#include "FragTrap.hpp"

FragTrap::FragTrap(void) : ClapTrap("A nobody", 100, 100, 30) {std::cout << "Frag default constructor" << std::endl;}
FragTrap::FragTrap(const FragTrap& src) : ClapTrap(src) {std::cout << "Frag copy constructor" << std::endl;}
FragTrap::~FragTrap(void) {std::cout << "Frag destructor" << std::endl;}
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

FragTrap::FragTrap(const std::string& name) : ClapTrap(name, 100, 50, 20) {std::cout << "string scav constructor" << std::endl;}

void	FragTrap::attack(const std::string& target)
{
	if (this->exhausted())
		return ;
	std::cout << "FragTrap " << Name << " attacks " << target << ", causing " << AttackDamage << " points of damage!" << std::endl;
	EnergyPoints -= 1;
}

void	FragTrap::takeDamage(unsigned int amount)
{
	std::cout << "FragTrap " << Name << " took " << amount << " damage!" << std::endl;
	HitPoints -= amount;
}

void	FragTrap::beRepaired(unsigned int amount)
{
	if (this->exhausted())
		return ;
	std::cout << "FragTrap " << Name << " repaired " << amount << " hit points!" << std::endl;
	HitPoints += amount;
	EnergyPoints -= 1;
}

void	FragTrap::highFivesGuys(void) {std::cout << "FragTrap " << Name << " high five'd itself" << std::endl;}
