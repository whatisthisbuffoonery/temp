#include "Animal.cpp"

Animal::Animal(void) : type("empty")
{std::cout << "animal default constructor" << std::endl;}

Animal::Animal(const Animal& src) : type(src.gettype())
{std::cout << "animal copy constructor" << std::endl;}

Animal& Animal::operator=(const Animal& src)
{
	std::cout << "animal copy assignment operator" << std::endl;
	if (this != &src)
		type = src.gettype();
	return (*this);
}

Animal::~Animal(void) {std::cout << "animal destructor" << std::endl;}

void	Animal::makeSound(void) const {std::cout << "bruh" << std::endl};

const std::string&	Animal::gettype(void) const {return (type);}
