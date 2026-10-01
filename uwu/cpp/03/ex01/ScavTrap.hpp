#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include "ClapTrap.hpp"

class ScavTrap
{
private:
//	std::string	Name;
	int			HitPoints;
	int			EnergyPoints;
	int			AttackDamage;
public:
	ScavTrap(void);
	ScavTrap(const ScavTrap& src);
	ScavTrap&	operator=(const ScavTrap& src);
	~ScavTrap(void);

/*	std::string	getname(void) const;
	int			gethp(void) const;
	int			getenergy(void) const;
	int			getattack(void) const;

	void	attack(const std::string& target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);*/
};
