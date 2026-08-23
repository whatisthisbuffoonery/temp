#include "Weapon.hpp"

/*normal*/
Weapon::Weapon(void) {}

Weapon::Weapon(const Weapon& src) : type(src.getType()) {}

Weapon&	Weapon::operator=(const Weapon& src)
{
	if (this != &src)
		this->setType(src.getType());
	return (*this);
}

Weapon::~Weapon(void) {}

/*custom*/
Weapon::Weapon(const std::string& src) : type(src) {}

/*methods*/
const std::string&	Weapon::getType(void) const
{
	return (type);
}

void	Weapon::setType(const std::string& src)
{
	type = src;
}
