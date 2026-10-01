#ifndef CLAPTRAP
# define CLAPTRAP

# include <iostream>
# include <string>

class ClapTrap
{
private:
	std::string	Name;
	int			HitPoints;
	int			EnergyPoints;
	int			AttackDamage;
public:
	ClapTrap(void);
	ClapTrap(const ClapTrap& src);
	ClapTrap&	operator=(const ClapTrap& src);
	~ClapTrap(void);

	std::string	getname(void) const;
	int			gethp(void) const;
	int			getenergy(void) const;
	int			getattack(void) const;

	void	attack(const std::string& target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
};

#endif
