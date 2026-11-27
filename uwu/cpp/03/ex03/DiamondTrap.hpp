#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap
{
private:
	std::string name;
	/*
	ClapTrap::name;
	FragTrap::hp;
	FragTrap::atk;
	ScavTrap::ep;
	ScavTrap::attack();
	*/

	static int const	fraghp = 100;
	static int const	fragatk = 30;
	static int const	scavep = 50;
	//static char const	*suffix = "_clap_name";//can't do that apparently
public:
	DiamondTrap(void);
	DiamondTrap(const DiamondTrap& src);
	DiamondTrap&	operator=(const DiamondTrap& src);
	~DiamondTrap(void);
	DiamondTrap(const std::string& name);

	const std::string&	getDerivedName(void) const;

	void	attack(const std::string& target);
	void	whoAmI(void);
};

#endif
