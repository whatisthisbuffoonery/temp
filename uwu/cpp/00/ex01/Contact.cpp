#include "Contact.hpp"

Contact::Contact(void) {}

Contact::Contact(const Contact& src)
	: FirstName(src.FirstName),
	  LastName(src.LastName),
	  Nickname(src.Nickname),
	  PhoneNumber(src.PhoneNumber),
	  DarkestSecret(src.DarkestSecret) {}

Contact&	Contact::operator=(const Contact& src)
{
	if (this != &src)
	{
		FirstName = src.FirstName;
		LastName = src.LastName;
		Nickname = src.Nickname;
		PhoneNumber = src.PhoneNumber;
		DarkestSecret = src.DarkestSecret;
	}
	return (*this);
}

//std::string frees itself
Contact::~Contact(void) {}

//no number enforcement on phone number
int	init(void)
{
	if (string_init(FirstName)
		|| string_init(LastName)
		|| string_init(Nickname)
		|| string_init(PhoneNumber)
		|| string_init(DarkestSecret))
		return (1);
	return (0);
}
