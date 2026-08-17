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
int	Contact::init(void)
{
	if (!string_init(FirstName, "first name")
		|| !string_init(LastName, "last name")
		|| !string_init(Nickname, "nickname")
		|| !string_init(PhoneNumber, "phone number")
		|| !string_init(DarkestSecret, "darkest secret"))
		return (0);
	return (1);
}
