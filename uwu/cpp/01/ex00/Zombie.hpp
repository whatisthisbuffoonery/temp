#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

class Zombie
{
public:
	Zombie(void);
	Zombie(Zombie& src);
	Zombie	operator=(Zombie& src);//stack ig
	~Zombie(void);

	void	announce(void);
	Zombie	*newZombie(std::string name);//no ref?
	void	randomChump(std::string name);//cant reach the new zombie
private:
	std::string	name;
};
