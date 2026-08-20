#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(void) {}

Zombie::Zombie(const Zombie& src) : name(src.name) {}

Zombie	Zombie::operator=(const Zombie& src)
{
	if (this != &src)
		name = src.name;
	return (*this);
}

Zombie::~Zombie(void)
{
	std::cout << "[" << name << "] rotted too much" << std::endl;
}

//look up param/member shadowing
Zombie::Zombie(const std::string& name) : name(name) {}

void	Zombie::announce(void)
{
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

Zombie	*newZombie(std::string name)
{
	return (new Zombie(name));
}

void	randomChump(std::string name)
{
	Zombie	chump(name);
	chump.announce();
}
