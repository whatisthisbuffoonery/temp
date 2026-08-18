#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <limits>
# include "Contact.hpp"

class PhoneBook
{
public:
	PhoneBook(void);
	PhoneBook(const PhoneBook& src);
	PhoneBook& operator=(const PhoneBook& src);
	~PhoneBook(void);

	int		add(void);
	int		search(void);
private:
	int		size;
	Contact arr[8];
	void	display_phonebook_contents(void);
	void	print_index(int line);
};

void	phonebook_eof(void);

#endif
