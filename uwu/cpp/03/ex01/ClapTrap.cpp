#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void) : Name("who"), HitPoints(10), EnergyPoints(10), AttackDamage(0)
{std::cout << "default constructor" << std::endl;}

ClapTrap::ClapTrap(const ClapTrap& src) : Name(src.getname()), HitPoints(src.gethp()), EnergyPoints(src.getenergy()), AttackDamage(src.getattack())
{std::cout << "copy constructor" << std::endl;}

ClapTrap& ClapTrap::operator=(const ClapTrap& src)
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

ClapTrap::~ClapTrap(void) {std::cout << "destructor" << std::endl;}

std::string&	ClapTrap::getname(void) {return (name);}
int				ClapTrap::gethp(void) {return (HitPoint);}
int				ClapTrap::getenergy(void) {return (EnergyPoint);}
int				ClapTrap::getattack(void) {return (AttackDamage);}

void	ClapTrap::attack(const std::string& target)
{
	std::cout << "ClapTrap " << Name << " attacks " << target << ", causing " << AttackDamage << " points of damage!" << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << "ClapTrap " << Name << " took " << amount << " damage!" << std::endl;
	hp -= amount;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	std::cout << "ClapTrap " << Name << " repaired " << amount << " hit points!" << std::endl;
	hp += amount;
}
