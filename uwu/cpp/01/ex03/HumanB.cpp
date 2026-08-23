#include "HumanB.hpp"
#include <iostream>

/*normal*/
HumanB::HumanB(void) : name("Jeff"), stick(NULL) {}

HumanB::HumanB(const HumanB& src) : name(src.getName()), stick(&src.getWeapon()) {}

HumanB&	HumanB::operator=(const HumanB& src)
{
	if (this != &src)
	{
		name = src.getName();
		stick.setType(src.getWeapon().getType());
	}
	return (*this);
}

HumanB::~HumanB(void) {}

/*custom*/
HumanB::HumanB(const std::string& srcname) : name(srcname) {}

/*methods*/
void	HumanB::attack(void)
{
	std::cout << name << " attacks with their " << stick.getType() << std::endl;
}

const std::string&	HumanB::getName(void) const
{
	return (name);
}

const Weapon&	HumanB::getWeapon(void) const
{
	return (stick);
}

void	HumanB::setWeapon(const Weapon& src)
{
	stick = src;
}
