#include "Harl.hpp"

Harl::Harl(void)
{
	func[0] = &Harl::debug;
	func[1] = &Harl::info;
	func[2] = &Harl::warning;
	func[3] = &Harl::error;
}

Harl::Harl(const Harl& src)
{
	(void) src;
	func[0] = &Harl::debug;
	func[1] = &Harl::info;
	func[2] = &Harl::warning;
	func[3] = &Harl::error;
}

Harl&	Harl::operator=(const Harl& src)
{
	(void) src;
	func[0] = &Harl::debug;
	func[1] = &Harl::info;
	func[2] = &Harl::warning;
	func[3] = &Harl::error;
	return (*this);
}

Harl::~Harl(void) {}

void	Harl::debug(void)
{
	std::cout << "debug isn't too bad" << std::endl;
}

void	Harl::info(void)
{
	std::cout << "the info in this documentation sucks" << std::endl;
}

void	Harl::warning(void)
{
	std::cout << "cpp warnings are so useless" << std::endl;
}

void	Harl::error(void)
{
	std::cout << "where in the error did this segfault" << std::endl;
}

void	Harl::complain(std::string level)
{
	int	a;

	a = ((level == "debug") + 2 * (level == "info") + 3 * (level == "warning") + 4 * (level == "error")) - 1;
	if (a < 0)
		return ;
	std::cout << "func index " << a << std::endl;
	(this->*func[a])();
}
