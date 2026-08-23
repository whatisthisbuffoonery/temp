#include "HumanA.hpp"
#include <iostream>

/*normal*/
HumanA::HumanA(void) : name("Jeff"), spare("twig"), stick(&spare) {}

HumanA::HumanA(const HumanA& src) : name(src.getName()), stick(&src.getWeapon()) {}

HumanA&	HumanA::operator=(const HumanA& src)
{
	if (this != &src)
	{
		name = src.getName();
		setWeapon(src.getWeapon());
	}
	return (*this);
}

HumanA::~HumanA(void) {}

/*custom*/
HumanA::HumanA(const std::string& srcname, const Weapon& srcweap) : name(srcname), stick(&srcweap){}

/*methods*/
void	HumanA::attack(void)
{
	std::cout << name << " attacks with their " << stick->getType() << std::endl;
}

const std::string&	HumanA::getName(void) const
{
	return (name);
}

const Weapon&	HumanA::getWeapon(void) const
{
	return (*stick);
}

void	HumanA::setWeapon(const Weapon& src)
{
	stick = &src;
}
