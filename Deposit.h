//specification file for the Deposit class

#ifndef DEPOSIT_H
#define DEPOSIT_H
#include "Transaction.h"
#include "Account.h"

using namespace std;

class Deposit : public Transaction
{
private:
	double depositAmt;

	// Validation function for deposit amount
	void validateDepositAmt();

public:
	// Exception Classes
	class InvalidAmount
	{};

	//constructor
	Deposit();
	Deposit(double amt);
	
	//setter
	void makeDeposit(double amt);
	void setTransId();
	void setTransAmt(double amt);
	void setTransCode();

	//getter
	double getDepositAmt();

};
#endif