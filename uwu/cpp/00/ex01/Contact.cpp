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

void	phonebook_eof(void)
{
	std::cout << "std::cin is deceased now (ctrl-D), bailing!!!" << std::endl;
}

static int	string_init(std::string& dst, const std::string& prompt)
{
	std::cout << "input " << prompt << std::endl;
	while (1)
	{
		if (!std::getline(std::cin, dst))
			return ((phonebook_eof()), 0);
		else if (dst.size() > 0)
			break ;
	}
	return (1);
}

//no number enforcement on phone number
int	Contact::init(void)
{
	if (!string_init(FirstName, "first name")
		|| !string_init(LastName, "last name")
		|| !string_init(Nickname, "nickname")
		|| !string_init(PhoneNumber, "phone number")
		|| !string_init(DarkestSecret, "darkest secret"))
		return (0);
	std::cout << "contact added" << std::endl;
	return (1);
}

static char	*contact_format(char *dst, std::string& src, int width)
{
	int	len = src.size();
	int	flag = (len > width);

	if (flag)
		len = width;
	dst[src.copy(dst, len, 0)] = '\0';
	if (flag)
		dst[width - 1] = '.';
	return (dst);
}

void	Contact::display_contact_table(std::ostringstream& oss, char *str, int width, int line)
{
	oss << std::right << std::setw(width) << std::setfill(' ') << line + 1 << "|";
	oss << std::right << std::setw(width) << std::setfill(' ') << contact_format(str, FirstName, width) << "|";
	oss << std::right << std::setw(width) << std::setfill(' ') << contact_format(str, LastName, width) << "|";
	oss << std::right << std::setw(width) << std::setfill(' ') << contact_format(str, Nickname, width) << "\n";
}

void	Contact::display_contact_full(void)
{
	std::cout << "first name: " << FirstName << std::endl;
	std::cout << "last name: " << LastName << std::endl;
	std::cout << "nickname: " << Nickname << std::endl;
	std::cout << "phone number: " << PhoneNumber << std::endl;
	std::cout << "darkest secret: " << DarkestSecret << std::endl;
	std::cout << std::endl;
}
