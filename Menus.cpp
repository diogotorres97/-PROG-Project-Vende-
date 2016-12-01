#include "Menus.h"

bool infoInicial(string & shop, string & ClientsFile, string & ProductsFile, string & TransactionsFile)
{
	cout << "Insert shop's name: ";
	getline(cin, shop);

	ask_fileNames(ClientsFile, ProductsFile, TransactionsFile);

	return true;

}

/******************************************
 * Clients Manager
 ******************************************/
unsigned short int menuClients() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "Clients Manager Menu" << endl;
	cout << endl;
	cout << TAB << "1 - List Clients" << endl;
	cout << TAB << "2 - View information for Client by name" << endl;
	cout << TAB << "3 - View information for Client by id" << endl;
	cout << TAB << "4 - Create Client" << endl;
	cout << TAB << "5 - Edit Client" << endl;
	cout << TAB << "6 - Remove Client" << endl;
	cout << TAB << "0 - Return to menu." << endl << endl;
	cout << TAB << "Enter your option: ";
	option = read_op(0, 6);

	if (option == 0)
		return 0;

	return option;

}


void optionsClients(VendeMaisMais & supermarket) {
	unsigned int option;


	while ((option = menuClients()))
		switch (option) {
		case 1: supermarket.showClientsAlphabetic();
			break;
		case 2:
			supermarket.showClientByName();
			break;
		case 3:
			supermarket.showClientById();
			break;
		case 4:
			supermarket.createClient();
			break;
		case 5:
			supermarket.editClient();
			break;
		case 6:
			supermarket.removeClient();
			break;
		}
}

/******************************************
 * Transactions Manager
 ******************************************/
unsigned short int menuTransactions() {

	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "Transactions Manager Menu" << endl;
	cout << endl;
	cout << TAB << "1 - List transactions of one client by name(chronologically)" << endl;
	cout << TAB << "2 - List transactions of one client by id(chronologically)" << endl;
	cout << TAB << "3 - List transations of one day" << endl;
	cout << TAB << "4 - List transactions between 2 dates" << endl;
	cout << TAB << "5 - List all transactions" << endl;
	cout << TAB << "6 - Make transaction" << endl;
	cout << TAB << "0 - Return to menu." << endl << endl;
	cout << TAB << "Enter your option: ";
	option = read_op(0, 6);

	if (option == 7)
		return 0;

	return option;
}

void optionsTransactions(VendeMaisMais & supermarket)
{
	unsigned int option;

	while ((option = menuTransactions()))
		switch (option) {
		case 1:
			supermarket.showTransactionsByName();
			break;
		case 2:
			supermarket.showTransactionsByID();
			break;
		case 3:
			supermarket.showTransactionsByDay();
			break;
		case 4:
			supermarket.showTransactionsBetweenDates();
			break;
		case 5:
			supermarket.showTransactions();
			break;
		case 6:
			supermarket.makeTransaction();
			break;
		}
}

/******************************************
 * Advertising Manager
 ******************************************/
unsigned int menuAdvertising() {

	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "Advertising Manager Menu" << endl;
	cout << endl;
	cout << TAB << "1 - To one client" << endl;
	cout << TAB << "2 - To the bottom10 clients" << endl;
	cout << TAB << "0 - Return to menu." << endl << endl;
	cout << TAB << "Enter your option: ";
	option = read_op(0, 2);

	if (option == 0)
		return 0;

	return option;
}

void optionsAdvertising(VendeMaisMais & supermarket) {
	unsigned int option;

	while ((option = menuAdvertising()))
		switch (option) {
		case 1:
			supermarket.doAdvertising();
			break;
		case 2:
			supermarket.make_bottom10_advertising();
			break;
		}

}

/******************************************
* Start Menu
******************************************/

unsigned short int startMenu() {
	unsigned short int option;

	clearScreen();

	cout <<endl<< TAB_BIG << "MENU" << endl;
	cout << endl;
	cout << TAB << "1 - Clients Manager" << endl;
	cout << TAB << "2 - List of Products Available" << endl;
	cout << TAB << "3 - Transactions Manager" << endl;
	cout << TAB << "4 - Personalize Advertising" << endl;
	cout << TAB << "0 - Exit." << endl << endl;
	cout << TAB << "Enter your option: ";
	option = read_op(0, 4);

	if (option == 0)
		return 0;

	return option;
}

void startOptions(VendeMaisMais & supermarket) 
{
	unsigned int option;

	while ((option = startMenu()))
		switch (option) {
		case 1: optionsClients(supermarket);
			break;
		case 2: supermarket.showProducts();
			break;
		case 3: optionsTransactions(supermarket);
			break;
		case 4: optionsAdvertising(supermarket);
			break;
		}

	supermarket.saveChanges();
}
