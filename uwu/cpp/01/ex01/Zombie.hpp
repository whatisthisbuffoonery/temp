#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>

class Zombie
{
public:
	Zombie(void);
	Zombie(const Zombie& src);
	Zombie&	operator=(const Zombie& src);//stack ig
	~Zombie(void);
	Zombie(const std::string& name);

	void	announce(void);
private:
	std::string	name;
};

Zombie	*newZombie(std::string name);//no ref?
void	randomChump(std::string name);//cant reach the new zombie

Zombie	*zombieHorde(int N, std::string name);

#endif
