#include "DiamondTrap.hpp"

static const std::string	suffix = "_clap_name";

const int	DiamondTrap::fraghp;
const int	DiamondTrap::fragatk;
const int	DiamondTrap::scavep;

DiamondTrap::DiamondTrap(void) : ClapTrap("default" + suffix, fraghp, scavep, fragatk), name("default")
{std::cout << "diamond default constructor" << std::endl;}

DiamondTrap::DiamondTrap(const std::string& name) : ClapTrap(name + suffix, fraghp, scavep, fragatk), name(name)
{std::cout << "diamond string constructor" << std::endl;}

DiamondTrap::DiamondTrap(const DiamondTrap& src) : ClapTrap(src), ScavTrap(src), FragTrap(src), name(src.getDerivedName())
{
	std::cout << "diamond copy constructor" << std::endl;
}

DiamondTrap::~DiamondTrap(void)
{std::cout << "diamond destructor" << std::endl;}

const std::string&	DiamondTrap::getDerivedName(void) const {return (name);}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& src)
{
	std::cout << "copy assignment operator" << std::endl;
	if (this != &src)
	{
		ClapTrap::name = src.getname();
		HitPoints = src.gethp();
		EnergyPoints = src.getenergy();
		AttackDamage = src.getattack();
		name = src.getDerivedName();
	}
	return (*this);
}

void	DiamondTrap::attack(const std::string& target) {ScavTrap::attack(target);}

void	DiamondTrap::whoAmI(void)
{
	std::cout << "Diamond " << name << " of ClapTrap " << ClapTrap::name << " here" << std::endl;
	std::cout << "hp: " << HitPoints << ", ep: " << EnergyPoints << ", atk: " << AttackDamage << std::endl;
}
