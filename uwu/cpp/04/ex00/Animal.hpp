#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <string>
# include <iostream>

class Animal
{
protected:
	std::string	type;
public:
	Animal(void);
	Animal(const Animal& src);
	Animal&	operator=(const Animal& src);
	virtual ~Animal(void);

	virtual makeSound(void) const;
	const std::string&	Animal::gettype(void) const;
};
