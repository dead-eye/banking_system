//specification file for the Withdrawal class

#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H
#include "Transaction.h"

class Withdrawal : public Transaction
{
private:
	double withdrawalAmt;

	// Validation function for deposit amount
	void validateWithdrawalAmt();

public:
	// Exception Classes
	class InvalidAmount
	{};

	class InsufficientFunds
	{};

	//constructor
	Withdrawal();
	Withdrawal(double amt, double bal);
	
	//setter
	void makeWithdrawal(double amt);
	void setTransId();
	void setTransAmt(double amt);
	void setTransCode();

	//getter
	double getWithdrawalAmt();

};
#endif