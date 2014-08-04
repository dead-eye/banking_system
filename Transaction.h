//specification file for the Transaction class

#ifndef TRANSACTION_H
#define TRANSACTION_H

using namespace std;

class Transaction
{
protected:
	int transactionId;
	double transactionAmt;
	char transactionCode;

public:
	//constructors
	Transaction();
	Transaction(int id, double amt, char code);

	//destructor
	~Transaction();
	
	//getters
	int getTransId();
	double getTransAmt();
	char getTransCode();
	
	//setters
	void setTransId(int id);
	void setTransAmt(double amt);
	void setTransCode(char code);
};

#endif