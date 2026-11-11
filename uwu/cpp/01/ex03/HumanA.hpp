#ifndef HUMANA_HPP
# define HUMANA_HPP

# include "Weapon.hpp"

class HumanA
{
public:
	~HumanA(void);

	HumanA(const std::string& srcname, const Weapon& srcweap);

	void	attack(void);
private:
	std::string			name;
	const Weapon		&stick;
};

#endif
