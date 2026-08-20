#include "Zombie.hpp"
#include <iostream>

int	main(void)
{
	Zombie	*heap = newZombie("Bert");
	Zombie	stack("Andy");
	int		size = 2;
	Zombie	*horde = zombieHorde(size, "ma name Jeff");
	int		i = 0;

	delete heap;
	while (i < size)
		horde[i++].announce();
	delete[] horde;
	std::cout << "main exit" << std::endl;
}
