#include "Account.hpp"
#include <iostream>

Account::Account(int initial_deposit) : _accountIndex(_nbAccounts), _amount(initial_deposit), _nbDeposits(0), _nbWithdrawals(0)
{
	_nbAccounts += 1;
	_totalAmount += _amount;
}

Account::~Account(void)
{
	_nbAccounts -= 1;
	_totalAmount -= _amount;
	//maybe modify deposit/withdraw count
}

static int	Account::getNbAccounts(void)
{
	return (_nbAccounts);
}

static int	Account::getTotalAmount(void)
{
	return (_totalAmount);
}

static int	Account::getNbDeposits(void)
{
	return (_totalNbDeposits);
}

static int	Account::getNbWithdrawals(void)
{
	return (_totalNbWithdrawals);
}
