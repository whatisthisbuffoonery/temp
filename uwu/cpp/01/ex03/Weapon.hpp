#ifndef WEAPON_HPP
# define WEAPON_HPP

# include <string>

/*
   const string	func(void);
   //caller can't modify the value after

   string	func(void) const;
   //only compiles if it is a class member func
   //promise to not modify own object

   first one is because setType takes const
   second const is because... the compiler wants the extra promise to go with the first const
*/

class Weapon
{
public:
	Weapon(void);
	Weapon(const Weapon& src);
	Weapon&	operator=(const Weapon& src);
	~Weapon(void);

	Weapon(const std::string& src);

	const std::string&		getType(void) const;
	void					setType(const std::string& src);
private:
	std::string	type;
};

#endif
