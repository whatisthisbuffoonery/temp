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

void	PhoneBook::add(void)
{
	Contact	newest;

	if (!newest.init())
	{
		if (size == 8)
		{
			for (i = 1; i < 8; i ++)
				arr[i - 1] = arr[i];
			arr[7] = newest;
		}
		else
		{
			arr[size] = newest;
			size += 1;
		}
	}
}

void	PhoneBook::search(void) {}//buh
