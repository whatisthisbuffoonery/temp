#include "PhoneBook.hpp"

int	getcmd(std::string& dst, int& flag)
{
	std::cout << "input command: " << std::endl;
	flag = (bool) (std::getline(std::cin, dst));
	if (!flag)
		phonebook_eof();
	return (flag);
}

int	main(void)
{
	PhoneBook	book;
	std::string	cmd;
	int			flag = 1;

	std::cout << "I am a phonebook" << std::endl;
	while (flag && getcmd(cmd, flag))
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
