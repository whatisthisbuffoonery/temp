#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void) : Name("who"), HitPoints(100), EnergyPoints(50), AttackDamage(20)
{std::cout << "default constructor" << std::endl;}

ScavTrap::ScavTrap(const ScavTrap& src) : Name(src.getname()), HitPoints(src.gethp()), EnergyPoints(src.getenergy()), AttackDamage(src.getattack())
{std::cout << "copy constructor" << std::endl;}

ScavTrap& ScavTrap::operator=(const ScavTrap& src)
{
	std::cout << "copy assignment operator" << std::endl;
	if (this != &src)
	{
		Name = src.getname();
		HitPoints = src.gethp();
		EnergyPoints = src.getenergy();
		AttackDamage = src.getattack();
	}
	return (*this);
}

ScavTrap::~ScavTrap(void) {std::cout << "destructor" << std::endl;}

ScavTrap::ScavTrap(const std::string& name) : Name(name), HitPoints(10), EnergyPoints(10), AttackDamage(0)
{std::cout << "string constructor" << std::endl;}

void	ScavTrap::guardGate(void) {std::cout << "ScavTrap " << Name << " is guarding a gate" << std::endl;}

void	ScavTrap::attack(const std::string& target)
{
	std::cout << "ScavTrap " << Name << " attacks " << target << ", causing " << AttackDamage << " points of damage!" << std::endl;
	EnergyPoints -= 1;
}

void	ScavTrap::takeDamage(unsigned int amount)
{
	std::cout << "ScavTrap " << Name << " took " << amount << " damage!" << std::endl;
	HitPoints -= amount;
}

void	ScavTrap::beRepaired(unsigned int amount)
{
	std::cout << "ScavTrap " << Name << " repaired " << amount << " hit points!" << std::endl;
	HitPoints += amount;
	EnergyPoints -= 1;
}
