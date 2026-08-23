#ifndef HUMANA_HPP
# define HUMANA_HPP

# include "Weapon.hpp"

class HumanA
{
public:
	HumanA(void);
	HumanA(const HumanA& src);
	HumanA&	operator=(const HumanA& src);
	~HumanA(void);

	HumanA(const std::string& srcname, const Weapon& srcweap);

	void	attack(void);

	const std::string&	getName(void) const;
	const Weapon&		getWeapon(void) const;
	void				setWeapon(const Weapon& src);
private:
	std::string			name;
	Weapon				spare;
	const Weapon		*stick;
};

#endif
