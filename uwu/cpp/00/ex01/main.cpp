#include "PhoneBook.hpp"

int	string_init(std::string& dst, const std::string& prompt)
{
	std::cout << "input " << prompt << std::endl;
	while (1)
	{
		if (!std::getline(std::cin, dst))
		{
			std::cout << "std::cin is deceased now, bailing!!!" << std::endl;
		/*	std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');*/
			return (0);
		}
		else if (dst.size() > 0)
			break ;
	}
	return (1);
}

bool	getcmd(std::string& dst)
{
	std::cout << "input command: " << std::endl;
	return ((bool)std::getline(std::cin, dst));
}

int	main(void)
{
	PhoneBook	book;
	std::string	cmd;
	int			flag = 1;

	while (flag && getcmd(cmd))
	{
		if (cmd == "ADD")
			flag = book.add();
		else if (cmd == "SEARCH")
			flag = book.search();
		else if (cmd == "EXIT")
			break ;
	}
	if (flag)
		std::cout << "exiting now" << std::endl;
}
