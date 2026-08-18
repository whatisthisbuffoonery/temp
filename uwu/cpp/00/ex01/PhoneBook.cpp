#include "PhoneBook.hpp"

/*std::copy tries to use your copy assignment if available*/

PhoneBook::PhoneBook(void) : size(0) {}

PhoneBook::PhoneBook(const PhoneBook& src) : size(src.size)
{
	if (src.size > 0)
		std::copy(src.arr, src.arr + src.size, arr);
}

PhoneBook&	PhoneBook::operator=(const PhoneBook& src)
{
	if (this != &src)
	{
		size = src.size;
		if (size > 0)
			std::copy(src.arr, src.arr + src.size, arr);
	}
	return (*this);
}

PhoneBook::~PhoneBook(void) {}

int	PhoneBook::add(void)
{
	Contact	newest;

	if (newest.init())
	{
		if (size == 8)
		{
			for (int i = 1; i < 8; i ++)
				arr[i - 1] = arr[i];
			arr[7] = newest;
			std::cout << "note: oldest contact replaced by new entry" << std::endl;
		}
		else
		{
			arr[size] = newest;
			size += 1;
		}
		std::cout << std::endl;
		return (1);
	}
	return (0);
}

void	PhoneBook::display_phonebook_contents(void)
{
	int					width = 10;
	int					line = 0;
	char				str[11];
	std::ostringstream	oss;

	str[10] = '\0';
	std::cout << "     index" << "|" << "first name" << "|" << " last name" << "|" << "  nickname" << std::endl;
	while (line < size)
	{
		arr[line].display_contact_table(oss, str, width, line);
		line ++;
	}
	std::cout << oss.str() << std::endl;
}

int	PhoneBook::search(void)
{
	int	line = 0;

	if (size < 1)
	{
		std::cout << "no contacts currently stored, returning to main menu" << std::endl;
		return (1);
	}
	this->display_phonebook_contents();
	std::cout << "Enter entry index, or type 0 to go back:" << std::endl;
	while (!(bool)(std::cin >> line))
	{
		if (std::cin.eof())
			return ((phonebook_eof()), 0);
		std::cout << "not an integer, try again:" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if (line > 0 && line <= size)
		return ((arr[line - 1].display_contact_full()), 1);
	else if (line != 0)
		std::cout << "invalid index, ";
	std::cout << "returning to main menu" << std::endl;
	return (1);
}
