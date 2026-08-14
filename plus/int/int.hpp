#ifndef INT_HPP
# define INT_HPP

# include <iostream>

class muh_int {
public:
	muh_int(int src);
	muh_int(void);
	~muh_int(void);

	void	print_muh_int(void);
	muh_int operator+ (muh_int);
//	muh_int operator- (muh_int);
//	muh_int operator* (muh_int);
//	muh_int operator/ (muh_int);
//	muh_int operator% (muh_int);

	void operator= (muh_int);

//	muh_int operator+ (void);
//	muh_int operator- (void);

//	muh_int operator== (muh_int);
//	muh_int operator!= (muh_int);

	int operator() (void);
private:
	int	n;
};

#endif
