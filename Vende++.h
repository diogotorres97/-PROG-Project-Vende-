#pragma once

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <set>
#include <iterator>

#include "defs.h"
#include "Date.h"
#include "Client.h"
#include "Transaction.h"
#include "Product.h"
#include "Read_files.h"
#include "utils.h"


using namespace std;

class VendeMaisMais {
private:
	string shop;
	string ClientsFile, ProductsFile, TransactionsFile; 
	bool changedTransactions = false; // flag which is true if you have to save at the end of the transactions
	bool changedClients = false; // flag which is true if you have to save at the end of the clients
	int maxClientsId; // Id client max existent
	double totalSpentSum;
	vector <int> vector_num_items;
	vector<Client> vector_clients; // vector that saves information from existing clients
	vector<Product> vector_products; // vector that saves information from available products
	vector<Transaction> vector_transactions; // vector that saves information from transactions made
	vector<Transaction> vector_advertising; // vector compact from vector_transactions
	vector <Transaction> vect_adv_without_bottom10; //vector of clients that doesn't contain the bottom10
	vector<string> allProducts; //vector that contains the products transactioned by the bottom10
	vector<vector<bool>> matrix;
	vector <int> vect_BuyersOfBottom10mais1; //vector of clients that bought the bottom10 products plus 1
	vector <int> bottom10; //vector of ids of bottom10
	vector <Transaction> vect_adv_bottom10; //vector containing the bottom10 clients
	map <string, int> histogram_interesting; //map that is the histogram of the interesting clients
	multimap<int, string> sorted_histogram_interesting; //histogram sorted by quantities
	map <string, int> histogram_bottom10; //map that is the histogram of the bottom10
	multimap<int, string> sorted_histogram_bottom10; //histogram sorted by quantities

public:
	VendeMaisMais(string shop, string ClientsFile, string ProductsFile, string TransactionsFile);
	void createVectorAdvertising(); //Create a vector with a relation of positions with ID's in vector_transactions
	void saveChanges() const;

	//Advertising
	void fillMatrix( int lin, int col); //Fill the matrix with falses
	void refreshMatrix();	//Update matrix to true if certain product in certain ID exist
	int equalProducts(size_t target_ID, size_t i, const vector< vector<bool>> matrix); //Return how many equal products exists between target ID and another ID in vector
	int getNumberOfProducts(vector<bool > v1); //Return number of products bought by a certain ID
	void getBuyersOfTargetProducts(size_t target_ID, int lines, int columns, vector <int> &ids_clients); //Check which clients bought the same products than target ID
	string productAdvertising(size_t target_ID, int lines, int columns, vector <int> ids_clients);//Check which clients bought the same products than target ID
	//Choose a product to make advertising serving two conditions :
	//  -Bought the largest number of products purchased by the target client;
	//  -Bought at least one product not purchased by the target client.
	void doAdvertising(); //Menu for advertising

	//BOTOM10 Advertising
	void giveIdBottom10(); //give 10 id's that are the 10 worst clients
	void allProductsOfBottom10(); //give all products bought by bottom10
	void giveBuyersOfBottom10(); // give buyers that  bought all their(bottom10) products and at least 1 that they haven't bought
	void create_vec_with_and_without_Bot10(); //create two vectors, one without bottom10 and another only with bottom10
	void make_bottom10_advertising();
	void create_histogram(); //creating interesting clients histogram and bottom10 clientes histogram, basically creates two maps with products and number of purchases this products
	template<typename A, typename B>
	multimap<B, A> flip_map(const map<A, B> &src);
	bool check_bot10_all_bought(string prod); //checks if all the bottom10 bought this product
	string find_prod_to_make_publicity(multimap<int, string> sorted_histogram_interesting, multimap<int, string> sorted_histogram_bottom10);
	int check_prod_interesting_exists_bot10(string prod,multimap<int, string> sorted_histogram_bottom10); //checks if an interesting product was bought by bottom10

	// Clients management
	bool checkID(int id, vector<Client>vector_clients); //Check if ID exists in vector_clients
	bool checkName(string _name, vector<Client>vector_clients); //Check if name exists in vector_clients
	int searchPosId(int id, vector<Client>vector_clients); //Return position of certain ID in vector_clients
	int searchPosName(string _name, vector<Client>vector_clients); //Return position of certain name in vector_clients
	void MaxId(); //Update id max

	void showClientsAlphabetic(); //View clients in alphabetic order
	void showClientByName(); //View one client by name
	void showClientById(); //View one client by id

	void createClient(); //Create a Client
	void editClient(); //Edit a Client
	void removeClient(); //Remove a Client
	void totalSpent(); //Calc total spent by all clients

	// Products management
	int searchPosProduct(string prod_name, vector<Product>vector_products); //return a position of a product in vector_products
	void showProducts(); //View all of products in alphabetic order
	vector <string> give_products();

	// Transactions management
	bool checkIDT(int id, vector<Transaction>vector_transactions); //Check if ID exists in vector_transactions
	vector<int> searchPosIdT(int id, vector <Transaction> vector_transactions);	//Return a vector of position's of certain ID in vector_transactions
	vector<int> searchPosDateT(string date, vector <Transaction> vector_transactions); //Return a vector of position's of certain date in vector_transactions
	bool checkDate(string date, vector <Transaction> vector_transactions); //Verify if certain date exists in vector_transactions

	void showTransactionsByName(); //View transactions by one client name
	void showTransactionsByID(); //View transactions by one client id
	void showTransactionsByDay(); //View transactions by one day
	void showTransactionsBetweenDates(); //View transactions between two dates
	void showTransactions(); //View all transactions

	void makeTransaction(); // Do transactions

	friend ostream& operator<<(ostream& out, const VendeMaisMais & supermarket);
};
