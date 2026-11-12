#ifndef CLAPTRAP
# define CLAPTRAP

# include <iostream>
# include <string>

class ClapTrap
{
protected:
	std::string	Name;
	int			HitPoints;
	int			EnergyPoints;
	int			AttackDamage;

	ClapTrap(const std::string& srcname, const int& hp, const int& ep, const int& atk);
public:
	ClapTrap(void);
	ClapTrap(const ClapTrap& src);
	ClapTrap&	operator=(const ClapTrap& src);
	~ClapTrap(void);

	ClapTrap(const std::string& name);

	const std::string&	getname(void) const;
	int					gethp(void) const;
	int					getenergy(void) const;
	int					getattack(void) const;

	void	attack(const std::string& target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
};

#endif
