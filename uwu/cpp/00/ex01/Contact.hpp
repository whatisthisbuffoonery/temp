#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>
# include <iostream>
# include <sstream>
# include <iomanip>

class Contact
{
public:
	Contact(void);
	Contact(const Contact& src);
	Contact& operator=(const Contact& src);
	~Contact(void);

	int		init(void);
	void	display_contact_table(std::ostringstream& oss, char *str, int width, int line);
	void	display_contact_full(void);
private:
	std::string FirstName;
	std::string LastName;
	std::string Nickname;
	std::string PhoneNumber;
	std::string DarkestSecret;
};

#endif
