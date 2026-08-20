#include "Zombie.hpp"
#include <iostream>

int	main(void)
{
	Zombie	*heap = newZombie("Bert");
	Zombie	stack("Andy");

	delete heap;
	std::cout << "main exit" << std::endl;
}
