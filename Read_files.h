#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Vende++.h"
#include "defs.h"
#include "utils.h"

using namespace std;

//Ask file names and check if they are valid
void ask_fileNames(string & ClientsFile, string & ProductsFile, string & TransactionsFile);

//Check files (verify if data in files are correct)
bool check_clients_files(string fileName, vector<Client> &vector_clients);
bool check_products_files(string fileName, vector<Product> &vector_products);
bool check_trans_files(string fileName, vector<Client> &vector_clients, vector<Product> &vector_products, vector<Transaction> &vector_transactions, vector<Transaction> &vector_advertising);

//Read files and copy data for a certain type of vector
void read_clients_file(string fileName, vector<Client> &vector_clients, vector <int> &vector_num_items);
void read_products_file(string fileName, vector<Product> &vector_products, vector <int> &vector_num_items);
void read_trans_file(string fileName, vector<Client> &vector_clients, vector<Product> &vector_products, vector<Transaction> &vector_transactions, vector<Transaction> &vector_advertising, vector <int> &vector_num_items);

//Extract products of a transaction
vector <string> give_products(vector<Product>vector_products);

//Create a vector with existing's id's in choose_vec("cl", "adv", "tr")
vector <int> GiveIDsIndexes(string which_vec, vector<Client> &vector_clients, vector<Transaction> &vector_transactions, vector<Transaction> &vector_advertising);
