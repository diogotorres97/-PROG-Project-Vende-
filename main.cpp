#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "Vende++.h"
#include "Menus.h"
#include "utils.h"
#include "defs.h"


int main() {
	string shop, ClientsFile, ProductsFile, TransactionsFile;
	cout << setprecision(PRECISION);
	// pede a informacoo sobre o nome da loja e os 3 ficheiros com
	// informacoo de Clients, Products e transactions
	if (!infoInicial(shop, ClientsFile, ProductsFile, TransactionsFile))
		return(-1);

	// cria uma loja
	VendeMaisMais supermarket(shop, ClientsFile, ProductsFile, TransactionsFile);
	clearScreen();
	cout << "Information of shop " << shop << " from supermarket Vende++:" << endl << endl;
	cout << supermarket << endl;  // mostra estatisticas da shop

	startOptions(supermarket); // menu inicial com as grandes opcoes
				  // que implementam as funcioanlidades
				  // disonibilizadas

	return 0;
}
