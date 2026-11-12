#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include "ClapTrap.hpp"

class FragTrap : ClapTrap
{
public:
	FragTrap(void);
	FragTrap(const FragTrap& src);
	FragTrap&	operator=(const FragTrap& src);
	~FragTrap(void);

	ClapTrap(const std::string& name);

	void	attack(const std::string& target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);

	void	highFivesGuys(void);
};

#endif
