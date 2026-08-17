#ifndef INT_HPP
# define INT_HPP

# include <iostream>

class muh_int {
public:
	muh_int(int src);
	muh_int(void);
	muh_int(const muh_int &src);
	~muh_int(void);

	void	print_muh_int(void);
//	muh_int operator+ (const muh_int &);
//	muh_int operator+ (int);
//	muh_int operator- (muh_int);
//	muh_int operator* (muh_int);
//	muh_int operator/ (muh_int);
//	muh_int operator% (muh_int);

	muh_int &operator= (const muh_int &);
	// assign from integer
	muh_int &operator= (int v);

//	muh_int operator+ (void);
//	muh_int operator- (void);

//	muh_int operator== (muh_int);
//	muh_int operator!= (muh_int);

	int operator() (void) const;
private:
	int	n;
};

muh_int	operator+(const muh_int &a, int b);
muh_int	operator+(const muh_int &a, const muh_int &b);
muh_int	operator+(int a, const muh_int &b);

#endif
