#ifndef HARL_HPP
# define HARL_HPP

# include <iostream>
# include <string>

class Harl
{
public:
	Harl(void);
	Harl(const Harl& src);
	Harl& operator=(const Harl& src);
	~Harl(void);

	void	complain(std::string level);
private:
	void	debug(void);
	void	info(void);
	void	warning(void);
	void	error(void);
	void	(Harl::*func[4])(void);
};

#endif
