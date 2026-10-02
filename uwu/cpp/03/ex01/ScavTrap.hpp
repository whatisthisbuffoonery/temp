#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include "ClapTrap.hpp"

class ScavTrap : class ClapTrap
{
public:
	ScavTrap(void);
	ScavTrap(const ScavTrap& src);
	ScavTrap&	operator=(const ScavTrap& src);
	~ScavTrap(void);

	ScavTrap(const std::string& name);

	void	guardGate(void);

	void	attack(const std::string& target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
};
