#include "ClapTrap.hpp"

ClapTrap::ClapTrap(const std::string& srcname, const int& hp, const int& ep, const int& atk) : name(srcname), HitPoints(hp), EnergyPoints(ep), AttackDamage(atk)
{std::cout << "inherited constructor" << std::endl;}

ClapTrap::ClapTrap(void) : name("who"), HitPoints(10), EnergyPoints(10), AttackDamage(0)
{std::cout << "default constructor" << std::endl;}

ClapTrap::ClapTrap(const ClapTrap& src) : name(src.getname()), HitPoints(src.gethp()), EnergyPoints(src.getenergy()), AttackDamage(src.getattack())
{std::cout << "copy constructor" << std::endl;}

ClapTrap& ClapTrap::operator=(const ClapTrap& src)
{
	std::cout << "copy assignment operator" << std::endl;
	if (this != &src)
	{
		name = src.getname();
		HitPoints = src.gethp();
		EnergyPoints = src.getenergy();
		AttackDamage = src.getattack();
	}
	return (*this);
}

ClapTrap::~ClapTrap(void) {std::cout << "destructor" << std::endl;}

ClapTrap::ClapTrap(const std::string& name) : name(name), HitPoints(10), EnergyPoints(10), AttackDamage(0)
{std::cout << "string constructor" << std::endl;}

const std::string&	ClapTrap::getname(void) const {return (name);}
int					ClapTrap::gethp(void) const {return (HitPoints);}
int					ClapTrap::getenergy(void) const {return (EnergyPoints);}
int					ClapTrap::getattack(void) const {return (AttackDamage);}

int			ClapTrap::exhausted(void) const
{
	if (EnergyPoints > 0)
		return (0);
	std::cout << name << " is exhausted!" << std::endl;
	return (1);
}

void	ClapTrap::attack(const std::string& target)
{
	if (this->exhausted())
		return ;
	std::cout << "ClapTrap " << name << " attacks " << target << ", causing " << AttackDamage << " points of damage!" << std::endl;
	EnergyPoints -= 1;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << "ClapTrap " << name << " took " << amount << " damage!" << std::endl;
	HitPoints -= amount;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (this->exhausted())
		return ;
	std::cout << "ClapTrap " << name << " repaired " << amount << " hit points!" << std::endl;
	HitPoints += amount;
	EnergyPoints -= 1;
}
