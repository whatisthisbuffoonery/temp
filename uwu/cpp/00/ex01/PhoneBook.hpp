#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class PhoneBook
{
public:
	PhoneBook(void);
	PhoneBook(const PhoneBook& src);
	PhoneBook& operator=(const PhoneBook& src);
	~PhoneBook(void);

	//these funcs exit eof is encountered
	void	add(void);
	void	search(void);
private:
	int		size;
	Contact arr[8];
};

#endif
