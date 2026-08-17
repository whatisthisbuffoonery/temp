#include "PhoneBook.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>

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
		}
		else
		{
			arr[size] = newest;
			size += 1;
		}
		return (1);
	}
	return (0);
}

int	PhoneBook::search(void)
{
	int					line = 0;
	int					len;
	int					width = 10;
	char				str[11];
	std::ostringstream	oss;

	if (size < 1)
	{
		std::cout << "no contacts stored, returning to main menu" << std::endl;
		return (1);
	}
	std::cout << "     index" << "|" << "first name" << "|" << " last name" << "|" << "  nickname" << std::endl;
	str[10] = '\0';
	while (line < size)
	{
		oss << std::right << std::setw(width) << std::setfill(' ') << line + 1 << "|";
		oss << std::right << std::setw(width) << std::setfill(' ') << phonebook_format(str, arr[line].FirstName) << "|";
		oss << std::right << std::setw(width) << std::setfill(' ') << phonebook_format(str, arr[line].LastName) << "|";
		oss << std::right << std::setw(width) << std::setfill(' ') << phonebook_format(str, arr[line].Nickname) << "\n";
		line ++;
	}
	cout << oss.string() << "Enter entry index:" std::endl;
	while (!std::cin >> line)
	{
		if (std::cin.eof())
		{
			std::cout << "std::cin deceased, bailing now!!!" << std::endl;
			return (0);
		}
		if (std::cin.rdbuf->in_avail() > 0)
			std::cout << "invalid input, try again\n" << "Enter entry index:" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	if (line < 0 || line > size)
		std::cout << "invalid index, returning to main menu" << std::endl;
	else
		//huh;
	return (1);
}
