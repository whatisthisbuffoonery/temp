#ifndef HUMANB_HPP
# define HUMANB_HPP

# include "Weapon.hpp"

class HumanB
{
public:
	~HumanB(void);

	HumanB(const std::string& srcname);

	void	attack(void);
	void	setWeapon(const Weapon& src);
private:
	std::string			name;
	const Weapon		*stick;
};

#endif
