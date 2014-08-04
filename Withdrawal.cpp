//implementation file for the Withdrawal class

#include "Withdrawal.h"

// Validation function for Shift Number
void Withdrawal::validateWithdrawalAmt()
{
	if (withdrawalAmt < 0)
		throw InvalidAmount();
}

//constructor
Withdrawal::Withdrawal() : Transaction()
{
	withdrawalAmt = 0.0;
}

Withdrawal::Withdrawal(double amt, double bal)
{
	if (amt < 0.01)
	{
		throw InvalidAmount();
	}
	else if (amt > bal)
	{
		throw InsufficientFunds();
	}
	else
	{
		withdrawalAmt = amt;
		setTransAmt(amt);
		setTransCode();
	}
}

//setter
void Withdrawal::makeWithdrawal(double amt)
{
	if (amt >= .01)
		withdrawalAmt = amt;
	else
		throw InvalidAmount();
}


void Withdrawal::setTransId()
{
	transactionId = transactionId + 1;
}

void Withdrawal::setTransAmt(double amt)
{
	transactionAmt = amt;
}

void Withdrawal::setTransCode()
{
	transactionCode = 'W';
}

//getter
double Withdrawal::getWithdrawalAmt()
{
	return withdrawalAmt;
}