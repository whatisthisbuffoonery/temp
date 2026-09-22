#include "Harl.hpp"

int	main(int c, char **v)
{
	if (c != 2)
		return (1);
	Harl	h;
	std::string	filter(v[1]);
	int		cond;
	cond = (filter == "DEBUG") +
		2 * (filter == "INFO") +
		3 * (filter == "WARNING") +
		4 * (filter == "ERROR") -
		5 * (filter == "SWITCH");
	switch (cond)
	{
		case 1:
			std::cout << "[ " << filter << " ]" << std::endl;
			h.complain("debug");
			std::cout << std::endl;
			std::cout << "[ " << "INFO" << " ]" << std::endl;
			h.complain("info");
			std::cout << std::endl;
			std::cout << "[ " << "WARNING" << " ]" << std::endl;
			h.complain("warning");
			std::cout << std::endl;
			std::cout << "[ " << "ERROR" << " ]" << std::endl;
			h.complain("error");
			std::cout << std::endl;
			break ;
		case 2:
			std::cout << "[ " << filter << " ]" << std::endl;
			h.complain("info");
			std::cout << std::endl;
			std::cout << "[ " << "WARNING" << " ]" << std::endl;
			h.complain("warning");
			std::cout << std::endl;
			std::cout << "[ " << "ERROR" << " ]" << std::endl;
			h.complain("error");
			std::cout << std::endl;
			break ;
		case 3:
			std::cout << "[ " << filter << " ]" << std::endl;
			h.complain("warning");
			std::cout << std::endl;
			std::cout << "[ " << "ERROR" << " ]" << std::endl;
			h.complain("error");
			std::cout << std::endl;
			break ;
		case 4:
			std::cout << "[ " << filter << " ]" << std::endl;
			h.complain("error");
			std::cout << std::endl;
			break ;
		case 0:
			std::cout << "Harl rambles in the corner" << std::endl;
			break ;
		default:
			std::cout << "Harl has been SWITCHed off" << std::endl;
	}
}
