#ifndef HUMANB_HPP
# define HUMANB_HPP

# include "Weapon.hpp"

class HumanB
{
public:
	HumanB(void);
	HumanB(const HumanB& src);
	HumanB&	operator=(const HumanB& src);
	~HumanB(void);

	HumanB(const std::string& srcname);

	void	attack(void);

	const std::string&	getName(void) const;
	const Weapon&		getWeapon(void) const;
	void				setWeapon(const Weapon& src);
private:
	std::string			name;
	const Weapon		*stick;
};

#endif
