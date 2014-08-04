/*Name: Matthew Stewart
  Class: CIST2362 - C++ II, Spring 2014
  Date: March 4, 2014
  Program: Midterm Project - Banking System
  Description:
    This program will simulate a banking system for a small bank.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "Account.h"
#include "Deposit.h"
#include "Withdrawal.h"
#include "Check.h"

using namespace std;

//function prototypes
Account * loadAccountArray(Account [], int &);
Account * enlargeAccountArray(Account [], int &, Account);
Account * addNewAccount(Account [], int &);
void showAllAccounts(Account [], int);
char showLoginMenu();
void saveAccountArray(Account [], int);
void loginAccount(Account [], int);
void accountValidated(Account [], int);
char showBankMenu();
void makeDeposit(double, Account [], int);
void makeWithdrawal(double, Account [], int);
void makeCheck(string, double, string, Account [], int);

int main()
{
	//declare local variables
	Account *accounts;		//the dynamically allocated array of accounts
	int size = 0;			//size of the accounts array, initiallized to zero
	Account data;			//holds data temporarily for insertion into the array
	char loginChoice;		//menu choice for the main menu

	//dynamically allocate an array for accounts
	accounts = new Account[size];

	//loading the file data into the accounts array
	accounts = loadAccountArray(accounts, size);

	//starting the main loop of the program
	cout << endl;
	loginChoice = showLoginMenu();

	while (loginChoice != 'D' && loginChoice != 'd')
	{
		switch (loginChoice)
		{
			case 'A':
			case 'a':
				loginAccount(accounts, size);
				system("cls");
				cout << endl;
				loginChoice = showLoginMenu();
				break;
			case 'B':
			case 'b':
				accounts = addNewAccount(accounts, size);
				system("cls");
				cout << endl;
				loginChoice = showLoginMenu();
				break;
			case 'C':
			case 'c':
				showAllAccounts(accounts, size);
				system("cls");
				cout << endl;
				loginChoice = showLoginMenu();
				break;
			default :
				system("cls");
				cout << "\n\t\t      You have entered an invalid choice.";
				loginChoice = showLoginMenu();
		}
	}
	
	// performing house keeping functions and exiting the system
	cout << "\n\nExiting System...\n\n";

	// write accounts array to file
	saveAccountArray(accounts, size);
	
	// delete accounts array
	delete [] accounts;
	accounts = 0;

	cout << endl << endl;
	return 0;
}


//function Account * loadAccountArray(Account accounts[], int & size)
// This function will open the allaccounts.txt file and read the data in the file into temporary variables,
//	which it will use to create an array of accounts.
Account * loadAccountArray(Account accounts[], int & size)
{
	//declare local variables
	int acctNum;						//account number
	string firstName;					//customer's first name
	string lastName;					//customer's last name
	string password;					//password on the account
	double balance;						//account balance

	//checking for allaccounts.txt file and creating if needed
	fstream acctsData;
	acctsData.open("allaccounts.txt", ios::in);
	if (acctsData.fail())				//file does not exist, so create it
	{
		acctsData.open("allaccounts.txt", ios::out);

		acctsData.close();				//close the file for now
	}

	//the file exists, so read the accounts into the accounts array
	else
	{
		//read first account into account array
		acctsData >> acctNum;										//retreive data from file
		acctsData >> firstName;
		acctsData >> lastName;
		acctsData >> password;
		acctsData >> balance;

		//create an account with the file data
		Account acctName(acctNum, firstName, lastName, password, balance);

		accounts = enlargeAccountArray(accounts, size, acctName);	//enlarging the array and add the data to the end

		//while more accounts exist in the userData file,
		//continue reading accounts into the account array
		while (acctsData >> acctNum)									//while more data exists in the file
		{
			acctsData >> firstName;										//retreive data from file
			acctsData >> lastName;
			acctsData >> password;
			acctsData >> balance;
		
			//create an account with the file data
			Account acctName(acctNum, firstName, lastName, password, balance);

			accounts = enlargeAccountArray(accounts, size, acctName);	//enlarging the array and add the data to the end
		}
		
		acctsData.close();				//close the file for now
	}

	//returning the pointer to the accounts array to the calling module
	return accounts;
}

//function Account * enlargeAccountArray(Account accounts[], int & size, int data)
// This function will create a temp array then copy all elements in the account array to the temp array.
//	The original array will then be deleted and the recreated with a size that is one element larger than
//	it was originally.  All of the data from the temp array will then be copied to the new larger array and
//	the new data will be added to the last element in the new larger array.  A pointer to the new larger
//	array will be returned to the module that called the function.
Account * enlargeAccountArray(Account accounts[], int & size, Account data)
{
	//declare temp array
	Account *tempAccounts;

	// create new temp array
	tempAccounts = new Account[size];
	
	// copy contents of account array to temp array
	for (int index = 0; index < size; index ++)
		tempAccounts[index] = accounts[index];

	// delete original accounts array
	delete [] accounts;
	accounts = 0;

	// increment array size
	size++;

	// create new larger accounts array
	accounts = new Account [size];

	// copy contents of temp array to new accounts array
	for (int index = 0; index < size - 1; index ++)
	accounts[index] = tempAccounts[index];

	// add contents to the new last element
	accounts[size - 1] = data;
			
	// delete the temp array
	delete [] tempAccounts;
	tempAccounts = 0;

	//return pointer to the new accounts array
	return accounts;
}


//function void displayArray(int [] arr, int size)
// This function displays the contents of the accounts array.
void showAllAccounts(Account arr[], int size)
{
	system("cls");
	cout << "\nAccount Num\tFirst Name\tLast Name\tPassword\tBalance\n";
	cout << "-------------------------------------------------------------------------\n";
	for (int index = 0; index < size; index++)
		cout << setw(10) << arr[index].getAcctNum() << "\t" << setw(10) << arr[index].getFirstName() << "\t" 
		<< setw(9) << arr[index].getLastName() << "\t" << setw(8) << arr[index].getPassword() << "\t"
		<< fixed << setprecision(2) << arr[index].getBalance() << endl;
	cout << endl;
	system("pause");
}


//function char showLoginMenu()
// This function displays the main Bank Login Menu and returns the mainChoice variable
char showLoginMenu()
{
	//declare local varaible
	char choice;					//main menu choice

	//display the login menu
	cout << "\n\n\t\t\t\tBANK LOGIN MENU\n\n";
	cout << "\t\t\t    A -- Log into an Account\n";
	cout << "\t\t\t    B -- Open a New Account\n";
	cout << "\t\t\t    C -- Show All Accounts\n";
	cout << "\t\t\t    D -- Exit System\n\n";
	cout << "\t\t\t      Enter A, B, C or D: ";

	//get choice from user
	cin >> choice;

	//return user's choice to main
	return choice;
}


//function Account * addNewAccount(Account accounts[], int & size)
// This function will ask the user to enter the information for a new account.  A new
//	entry will be created in the accounts array with this information.
Account * addNewAccount(Account accounts[], int & size)
{
	//declare local variables
	int acctNum;				//account number
	string firstName;			//customer's first name
	string lastName;			//customer's last name
	string password;			//password on the account
	double balance;				//account balance

	//create new account number
	acctNum = accounts[size - 1].getAcctNum();
	acctNum++;

	//display header
	system("cls");
	cout << "\n\n\t\t\t     OPEN A NEW ACCOUNT\n\n";

	//get remaining information from the user for the new account
	cout << "Please enter the following information for the new account.\n\n";
	cout << "Account Holder's first name: ";
	cin >> firstName;
	cout << "Account Holder's last name: ";
	cin >> lastName;
	cout << "Password for the account: ";
	cin >> password;
	cout << "Beginning balance: ";
	cin >> balance;

	
	//create an account with the data entered
	Account acctName(acctNum, firstName, lastName, password, balance);

	//enlarge the array and add the data to the end
	accounts = enlargeAccountArray(accounts, size, acctName);

	//returning the pointer to the accounts array to the calling module
	return accounts;
}


//function void saveAccountArray(Account accounts[], int size)
// This function will save the accounts array to the allaccounts.txt file for storage while the
//	program is offline.
void saveAccountArray(Account accounts[], int size)
{
	//declare local variables
	int acctNum;					//account number
	string firstName;				//customer's first name
	string lastName;				//customer's last name
	string password;				//password on the account
	double balance;					//account balance

	//opening allaccounts.txt for writing
	fstream acctsData;
	acctsData.open("allaccounts.txt", ios::out);


	//revtrieving the member variables from the accounts and saving each record to the file
	for (int index = 0; index < size; index++)
	{
		acctNum = accounts[index].getAcctNum();
		firstName = accounts[index].getFirstName();
		lastName = accounts[index].getLastName();
		password = accounts[index].getPassword();
		balance = accounts[index].getBalance();

		acctsData << acctNum << " " << firstName << " " << lastName << " "
			<< password << " " << balance << endl;
	}

	acctsData.close();				//close the file for now
}


//function void loginAccount(Account accounts[], int size)
// This function allows a user to log into an account and conduct transactions on the account.
void loginAccount(Account accounts[], int size)
{
	//declare local variables
	int acctNum;				//account number entered by the user
	string password;			//password entered by the user
	int index = 0;				//counter variable to step through the accounts array
	bool acctFound = false;		//flag indicating if the account number is in the accounts array

	//prompt user for account number
	system("cls");
	cout << "\nPlease enter your nine-digit Account number: ";
	cin >> acctNum;

	//search for account number in the accounts array
	while (!(acctFound) && index < size)
	{
		if (acctNum == accounts[index].getAcctNum())
		{
			//account found
			acctFound = true;

			//prompt for password
			cout << "Please enter your password: ";
			cin >> password;

			try
			{
				//validate password first try
				accounts[index].validatePassword(password);
				accountValidated(accounts, index);
			}

			catch (Account :: InvalidPassword)
			{
				//passwords didn't match
				cout << "\nInvalid password!";

				//prompt for password again
				cout << "\nPlease try again: ";
				cin >> password;

				try
				{
					//validate password second try
					accounts[index].validatePassword(password);
					accountValidated(accounts, index);
				}

				catch (Account :: InvalidPassword)
				{
					//passwords didn't match
					cout << "\nInvalid Password!";

					//prompt for password - last chance
					cout << "\nPlease try again: ";
					cin >> password;

					
					try
					{
						//validate password third try
						accounts[index].validatePassword(password);
						accountValidated(accounts, index);
					}

					catch (Account :: InvalidPassword)
					{
						//account could not be validated
						cout << "\nI'm sorry.  This account could not be validated.\n\n";
						system("pause");
					}
				}
			}
		}

		//increment index
		index++;
	}

	//account not found
	if (!acctFound)
	{
		cout << "\nI'm sorry.  That account number is invalid.\nPlease try again.\n\n";
		system("pause");
	}

}


//function void accountValidated(Account accounts[], int index)
// This function allows the user access to a specific account in the accounts array after
//	the account number and password have been validated.
void accountValidated(Account accounts[], int index)
{
	//declare local variables
	char bankChoice;				//menu choice for the bank menu
	double amount;					//variable to hold an amount of money for a transaction
	string payee;					//variable to hold a payee for a check transaction
	string memo;					//variable to hold a memo for a check

	//dynamically creating the transaction list arrays in the accounts object
	accounts[index].setTransList();

	//display welcome message
	system("cls");
	cout << "\nHello, " << accounts[index].getFirstName() << " " << accounts[index].getLastName();

	//starting the bank loop of the program
	bankChoice = showBankMenu();

	while (bankChoice != 'F' && bankChoice != 'f')
	{
		system("cls");

		switch (bankChoice)
		{
			case 'A':		//Show account balance
			case 'a':
				cout << "\nAccount Balance: $" << fixed << setprecision(2)
					<< accounts[index].getBalance();
				break;
			case 'B':		//Make a deposit
			case 'b':
				cout << "\nEnter the amount to deposit: $";		//prompt for deposit amount
				cin >> amount;
				makeDeposit(amount, accounts, index);			//go to the makeDeposit function
				system("cls");
				cout << endl;
				break;
			case 'C':		//Make a withdrawal
			case 'c':
				cout << "\nEnter the amount of the withdrawal: $";	//prompt for the withdrawal amount
				cin >> amount;
				makeWithdrawal(amount, accounts, index);			//go to the makeWithdrawal function
				system("cls");
				cout << endl;
				break;
			case 'D':		//Write a check
			case 'd':
				cout << "\nEnter the Payee: ";						//prompt for the payee
				cin.ignore();
				getline (cin, payee);
				cout << "Enter the amount of the check: $";			//prompt for the check amount
				cin >> amount;
				cout << "Enter a memo (optional): ";				//prompt for the memo
				cin.ignore();
				getline (cin, memo);

				//adjust size of the payee and memo to fit on the screen in the "show all transactions" screen
				if (payee.length() > 15)
					payee = payee.substr(0, 15);
				if (memo.length() > 15)
					memo = memo.substr(0, 15);
				makeCheck(payee, amount, memo, accounts, index);	//go to the makeCheck function
				system("cls");
				cout << endl;
				break;
			case 'E':		//Show all transactions
			case 'e':
				//display header
				cout << "\nShow All Transactions.\n\n";
				cout << "Total number of transactions for this session: " << accounts[index].getNumOfTrans() << endl << endl;
				cout << "ID\tCode\tAmount\t\tBalance\t\tPayee\t\tMemo\n";
				cout << "-----------------------------------------------------------------------------\n";

				//access the transList array in the account object and display entries
				for (int count = 0; count < accounts[index].getNumOfTrans(); count ++)
				{
					cout << count + 1 << "\t" << accounts[index].getTrans(count);
				}

				cout << endl << endl;
				system("pause");
				system("cls");
				cout << endl;
				break;
			default :		//display error for bad menu choice
				cout << "\n\t\t      You have entered an invalid choice.";
		}
				bankChoice = showBankMenu();
	}

	//log off account and save account information
	cout << "\n\nLogging off account...\n\n";

	//deleting the transaction list arrays
	accounts[index].setNumOfTrans(0);
	accounts[index].deleteTransList();
}


//function char showBankMenu()
// This function displays the Bank Menu and retruns the mainChoice variable
char showBankMenu()
{
	//declare local varaible
	char choice;

	//display the login menu
	cout << "\n\n\t\t\t\t   BANK MENU\n\n";
	cout << "\t\t\t    A -- Show Account Balance\n";
	cout << "\t\t\t    B -- Make a Deposit\n";
	cout << "\t\t\t    C -- Make a Withdrawal\n";
	cout << "\t\t\t    D -- Write a Check\n";
	cout << "\t\t\t    E -- Show All Transactions\n";
	cout << "\t\t\t    F -- Logoff Account\n\n";
	cout << "\t\t\t     Enter A, B, C, D, E or F: ";

	//get choice from user
	cin >> choice;

	//return user's choice to main
	return choice;
}


//function void makeDeposit(double amount, Account accounts[], int index)
// This function validates the amount entered for the deposit transactions and if validated,
//	adds to the balance for the account.
void makeDeposit(double amount, Account accounts[], int index)
{
	//start try/catch block
	try
	{
		//declare local variables
		double beginningBal = accounts[index].getBalance();		//beginning balance of the account
		int numTrans = accounts[index].getNumOfTrans();			//number of tranactions in the transList array
		string transEntry;										//this will be the entry for this tranaction in transList array
		Deposit dep(amount);									//create a deposit object with the amount

		//change the balance in the account, adding the deposit amount to the beginning balance
		accounts[index].setBalance(beginningBal + amount);

		//creating string fragments to be assembled for the transList entry
		string strAmt = to_string(amount),
			   strBal = to_string(accounts[index].getBalance());
		strAmt = strAmt.substr(0, (strAmt.length()-4));
		strBal = strBal.substr(0, (strBal.length()-4));

		//assembling the string for the transList entry
		transEntry = "DEP\t" + strAmt + "\t\t" + strBal + "\n";

		//saving the transList entry
		accounts[index].setTrans(transEntry);

		//displaying the details of the deposit on the screen
		cout << "\nBeginning Balance: $" << beginningBal << "\nTransaction Amount: $" <<  dep.getTransAmt()
			<< "\nCurrent Balance: $" << accounts[index].getBalance() << "\nTransaction Code: "<< dep.getTransCode() 
			<< endl << endl;
 		system("pause");
	}

	catch (Deposit :: InvalidAmount)		//error handler for invalid deposit amounts
	{
		cout << "\nInvalid amount entered.\nMinimum deposit is $0.01.\nTransaction cancelled.\n\n";
		system("pause");
	}
}


//function void makeWithdrawal(double amount, Accounts[], int index)
// This function validates the amount entered for the withdrawal transactions and if validated,
//	subtracts from the balance for the account.
void makeWithdrawal(double amount, Account accounts[], int index)
{
	//start try/catch block
	try
	{
		//declare local varaiables
		double beginningBal = accounts[index].getBalance();		//beginning balance of the account
		int numTrans = accounts[index].getNumOfTrans();			//number of transactions in the transList array
		string transEntry;										//this will be the entry for this transaction in the transList array
		Withdrawal wth(amount, beginningBal);					//create a withdrawal object with the amount

		//change the balance in the account, subtracting the withdrawal amount from the beginning balance
		accounts[index].setBalance(beginningBal - amount);

		//creating string fragments to be assembled for the transList entry
		string strAmt = to_string(amount),
			   strBal = to_string(accounts[index].getBalance());
		strAmt = strAmt.substr(0, (strAmt.length()-4));
		strBal = strBal.substr(0, (strBal.length()-4));

		//assembling the string for the transList entry
		transEntry = "WTH\t" + strAmt + "\t\t" + strBal + "\n";

		//saving the transList entry
		accounts[index].setTrans(transEntry);

		//displaying the details of the deposit on the screen
		cout << "\nBeginning Balance: $" << beginningBal << "\nTransaction Amount: $" <<  wth.getTransAmt()
			<< "\nCurrent Balance: $" << accounts[index].getBalance() << "\nTransaction Code: "<< wth.getTransCode() 
			<< endl << endl;
		system("pause");
	}

	catch (Withdrawal :: InvalidAmount)			//error handler for invalid deposit amounts
	{
		cout << "\nInvalid amount entered.\nMinimum withdrawal is $0.01.\nTransaction cancelled.\n\n";
		system("pause");
	}

	catch (Withdrawal :: InsufficientFunds)		//error handler for insufficient funds available
	{
		cout << "\nInsufficient funds are available for a withdrawal of this size.\nCurrent account balance: $"
			<< fixed << setprecision(2)<< accounts[index].getBalance() << "\nTransaction cancelled.\n\n";
		system("pause");
	}
}


//function void makeCheck(double amount, Account accounts[], int index)
// This function validates the amount entered for the check transactions and if validated,
//	subtracts from the balance for the account.
void makeCheck(string payee, double amount, string memo, Account accounts[], int index)
{
	//start try/catch block
	try
	{
		//declare local variables	
		double beginningBal = accounts[index].getBalance();		//beginning balance of the account
		int numTrans = accounts[index].getNumOfTrans();			//number of transactions in the transList array
		string transEntry;										//this will be the entry for this transaction in the transList array
		Check chk(payee, amount, memo, beginningBal);			//create a withdrawal object with the payee, amount and memo

		//change the balance in the account, subtracting the withdrawal amount from the beginning balance
		accounts[index].setBalance(beginningBal - amount);

		//creating string fragments to be assembled for the transList entry
		string strAmt = to_string(amount),
			   strBal = to_string(accounts[index].getBalance());
		strAmt = strAmt.substr(0, (strAmt.length()-4));
		strBal = strBal.substr(0, (strBal.length()-4));

		//assembling the string for the transList entry
		transEntry = "CHK\t" + strAmt + "\t\t" + strBal + "\t\t" +  payee + "\t" + memo + "\n";

		//saving the transList entry
		accounts[index].setTrans(transEntry);

		//displaying the details of the deposit on the screen
		cout << "\nBeginning Balance: $" << beginningBal << "\nTransaction Amount: $" <<  chk.getTransAmt()
			<< "\nCurrent Balance: $" << accounts[index].getBalance() << "\nTransaction Code: "<< chk.getTransCode() 
			<< endl << endl;
		system("pause");
	}

	catch (Check :: InvalidAmount)			//error handler for invalid deposit amounts
	{
		cout << "\nInvalid amount entered.\nMinimum amount is $0.01.\nTransaction cancelled.\n\n";
		system("pause");
	}

	catch (Check :: InsufficientFunds)		//error handler for insufficient funds available
	{
		cout << "\nInsufficient funds are available for a check of this size.\nCurrent account balance: $"
			<< fixed << setprecision(2)<< accounts[index].getBalance() << "\nTransaction cancelled.\n\n";
		system("pause");
	}

	catch (Check :: InvalidPayee)			//error handler for invalid payee
	{
		cout << "\nInvalid payee entered.\nYou must enter a payee to have a check issued.\nTransaction cancelled.\n\n";
		system("pause");
	}
}