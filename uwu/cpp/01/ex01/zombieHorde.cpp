#include "Zombie.hpp"

Zombie	*zombieHorde(int N, std::string name)
{
	Zombie	*ret;
	int		i = 0;

	if (N < 1)
		return (NULL);
	ret = new Zombie[N];
	while (i < N)
		ret[i++] = Zombie(name);
	return (ret);
}
