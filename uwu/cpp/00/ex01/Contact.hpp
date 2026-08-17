#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>

class Contact
{
public:
	Contact(void);
	Contact(const Contact& src);
	Contact& operator=(const Contact& src);
	~Contact(void);

	int	init(void);
private:
	std::string FirstName;
	std::string LastName;
	std::string Nickname;
	std::string PhoneNumber;
	std::string DarkestSecret;
};

int	string_init(std::string& dst);

#endif
