#include "Vende++.h"


VendeMaisMais::VendeMaisMais(string shop, string ClientsFile, string ProductsFile, string TransactionsFile)
{
	this->shop = shop;
	this->ClientsFile = ClientsFile;
	this->ProductsFile = ProductsFile;
	this->TransactionsFile = TransactionsFile;

	read_clients_file(ClientsFile, vector_clients, vector_num_items);
	read_products_file(ProductsFile, vector_products, vector_num_items);
	read_trans_file(TransactionsFile, vector_clients, vector_products, vector_transactions, vector_advertising, vector_num_items);
	
	totalSpent();
	MaxId();
}

/*********************************
* Personalize Advertising
********************************/

void VendeMaisMais::createVectorAdvertising()
{
	vector <int> clients_indexes = GiveIDsIndexes("cl", vector_clients, vector_transactions, vector_advertising);
	string d1(DEFAULT_DATE);


	for (size_t i = 0; i < clients_indexes.size(); i++)
	{
		vector<string> new_products;

		for (size_t j = 0; j < vector_transactions.size(); j++)
		{
			if (vector_transactions.at(j).getIdClient() == clients_indexes.at(i))
			{
				if (searchPosInteger(clients_indexes.at(i), GiveIDsIndexes("adv", vector_clients, vector_transactions, vector_advertising)) == -1)
				{
					
					Transaction t1(clients_indexes.at(i), d1, vector_transactions.at(j).getProducts());

					new_products = vector_transactions.at(j).getProducts();
					vector_advertising.push_back(t1);
				}
				else
				{
					for (size_t k = 0; k < vector_transactions.at(j).getProducts().size(); k++)
					{
						if (searchPosString(vector_advertising.at(i).getProducts(), vector_transactions.at(j).getProducts().at(k)) == -1)
						{
							new_products.push_back(vector_transactions.at(j).getProducts().at(k));

						}
					}

					Transaction t1(clients_indexes.at(i), d1, new_products);
					vector_advertising.at(i) = t1;
				}
			}
		}
	}
}

void VendeMaisMais::fillMatrix( int lin, int col)
{
	for (size_t i = 0; i < lin; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			matrix.at(i).at(j) = false;
		}
	}
}

void VendeMaisMais::refreshMatrix()
{
	size_t id_client;
	size_t prod_pos;
	vector<string>vector_products = give_products();
	for (size_t i = 0; i < vector_advertising.size(); i++)
	{
		id_client = i;

		for (size_t j = 0; j < vector_advertising.at(i).getProducts().size(); j++)
		{
			prod_pos = searchPosString(vector_products, truncate_strings(vector_advertising.at(i).getProducts().at(j)));
			matrix.at(id_client).at(prod_pos) = true;
		}

	}

}

int VendeMaisMais::equalProducts(size_t target_ID, size_t i, const vector< vector<bool>> matrix)
{
	int counter = 0;

	for (size_t j = 0; j < matrix.at(i).size(); j++)
	{
		if ((matrix.at(target_ID).at(j) == true) && (matrix.at(i).at(j) == true))
		{
			counter++;
		}
	}

	return counter;
}

int VendeMaisMais::getNumberOfProducts(vector<bool > v1)
{
	int counter = 0;

	for (size_t i = 0; i < v1.size(); i++)
	{
		if (v1.at(i) == true)
		{
			counter++;
		}
	}
	return counter;
}

void VendeMaisMais::getBuyersOfTargetProducts(size_t target_ID, int lines, int columns, vector <int> &ids_clients)
{
	size_t number_of_products_equal_to_targets_ones = 0;
	int aux, num_prods_target, num_prods_client;

	for (size_t i = 0; i < lines; i++)
	{
		num_prods_target = getNumberOfProducts(matrix.at(target_ID));

		if (i != target_ID)
		{
			aux = equalProducts(target_ID, i, matrix);
			num_prods_client = getNumberOfProducts(matrix.at(i));

			if ((aux > number_of_products_equal_to_targets_ones) && (num_prods_client > num_prods_target))
			{
				number_of_products_equal_to_targets_ones = aux;
				ids_clients.clear();
				ids_clients.push_back(i);
			}
			else
			{
				if ((aux == number_of_products_equal_to_targets_ones) && (num_prods_client > num_prods_target))
				{
					ids_clients.push_back(i);
				}
			}

		}
	}

	return;
}

string VendeMaisMais::productAdvertising(size_t target_ID, int lines, int columns, vector <int> ids_clients)
{
	vector <int> product_ids_that_target_chose;
	int flag1 = 0, aux, pos;

	vector <int> quantities_of_products;
	vector <string> keys_of_the_map;
	vector<string> vector_products = give_products();
	map<string, int> map_of_products_not_target; //map of products that the target client has not bought yet

	for (size_t i = 0; i < columns; i++)
	{
		if (matrix.at(target_ID).at(i) == true)
		{
			product_ids_that_target_chose.push_back(i);
		}
	}

	for (size_t i = 0; i < ids_clients.size(); i++)
	{
		pos = ids_clients.at(i);

		for (size_t j = 0; j < vector_advertising.at(pos).getProducts().size(); j++)
		{
			aux = searchPosString(vector_products, truncate_strings(vector_advertising.at(pos).getProducts().at(j)));
			flag1 = searchPosInteger(aux, product_ids_that_target_chose);

			if (flag1 == -1)
			{
				if (matrix.at(pos).at(aux) == true)
				{
					if (map_of_products_not_target.count(vector_products.at(aux)) == 0)
					{
						map_of_products_not_target.insert(pair<string, int>(vector_products.at(aux), 1));
					}
					else
					{
						map_of_products_not_target.at(vector_products.at(aux))++;
					}
				}

			}

		}

	}
	for (size_t i = 0; i < columns; i++)
	{
		if (map_of_products_not_target.count(vector_products.at(i)) == 1)
		{
			keys_of_the_map.push_back(vector_products.at(i));
		}
	}
	for (size_t i = 0; i < map_of_products_not_target.size(); i++)
	{
		quantities_of_products.push_back(map_of_products_not_target.at(keys_of_the_map.at(i)));
	}

	return keys_of_the_map.at(getMax(quantities_of_products));

}

void VendeMaisMais::doAdvertising()
{
	createVectorAdvertising();

	size_t id_target, lines, columns, target_ID;
	int flag = 0, pos;
	matrix.resize(vector_advertising.size(), vector<bool>(vector_products.size()));  //VERIFICARRRRRRRRRRRRRRRRRRRR
	vector <int> ids_clients; //vector with the indexes of clients that have bought the most number of products equal to target ones

	lines = vector_advertising.size();
	columns = vector_products.size();
	fillMatrix(lines, columns);
	

	refreshMatrix();

	do
	{

		if (flag >= 1)
		{
			cerr << "Error, please indicate an ID that already did transactions!" << endl;
		}
		
		id_target =read_int("Target client's id ? ");
		pos = searchPosInteger(id_target, GiveIDsIndexes("adv", vector_clients, vector_transactions, vector_advertising));
		flag++;
	} while (pos == -1);

	
	target_ID = searchPosInteger(id_target, GiveIDsIndexes("adv", vector_clients, vector_transactions, vector_advertising));
	getBuyersOfTargetProducts(target_ID, lines, columns, ids_clients);

	if (ids_clients.size() == 0)
	{
		cout <<endl<< TAB << "There is no other client that has products that would suit you!" << endl<<endl;
	}
	else
	{
		cout <<endl<< TAB << "You should buy " << productAdvertising(target_ID, lines, columns, ids_clients) << endl<<endl;
	}
	vector_advertising.clear();
	system("pause");
}

/*********************************
* BOTOM10 Advertising
********************************/

void VendeMaisMais::giveIdBottom10()
{
	
	sort(vector_clients.begin(), vector_clients.end(), sortAmount);
	vector<Client>::reverse_iterator p;

	for (p = vector_clients.rbegin(); p != vector_clients.rbegin() + 10; p++)
	{
		bottom10.push_back(p->getId());
	}
	
	
}


void VendeMaisMais::allProductsOfBottom10()
{
	

	for (size_t i = 0; i < bottom10.size(); i++)
	{
		vector<int> pos = searchPosIdT(bottom10.at(i), vector_transactions);
		for (size_t j = 0; j < pos.size(); j++)
		{
			vector<string> products = vector_transactions.at(j).getProducts();

			for (size_t k = 0; k < products.size(); k++)

				allProducts.push_back(products.at(k));
		}
	}

	//take out duplicated products
	sort(allProducts.begin(), allProducts.end());
	vector<string>::iterator p;

	for (size_t z = 0; z < allProducts.size(); z++)
	{
		int index = 0;

		while (allProducts.at(index) == allProducts.at(index + 1))
		{
			allProducts.erase(allProducts.begin() + index);
		}
	}
}

void VendeMaisMais::create_vec_with_and_without_Bot10()
{
	for (size_t i = 0; i < vector_advertising.size(); i++)
	{
		if (searchPosInteger(vector_advertising.at(i).getIdClient(), bottom10) == -1)
		{
			vect_adv_without_bottom10.push_back(vector_advertising.at(i));
		}
		else
		{
			vect_adv_bottom10.push_back(vector_advertising.at(i));
		}
	}

}

void VendeMaisMais::giveBuyersOfBottom10()
{
	size_t number_of_products_equal_to_targets_ones = 0;

	//Condition: bought all their products and at least 1 that they haven't bought

	for (size_t i = 0; i < vect_adv_without_bottom10.size(); i++)
	{
		for (size_t j = 0; j < allProducts.size(); j++)
		{
			if (searchString(vect_adv_without_bottom10.at(i).getProducts(), allProducts.at(j)))
			{
				number_of_products_equal_to_targets_ones++;
			}

			if (number_of_products_equal_to_targets_ones == allProducts.size() && vect_adv_without_bottom10.at(i).getProducts().size()>allProducts.size())
			{
				vect_BuyersOfBottom10mais1.push_back(vect_adv_without_bottom10.at(i).getIdClient());
			}
		}
	}
	
}

bool VendeMaisMais::check_bot10_all_bought(string prod)
{
	//checks if all the bottom10 bought this product
	for (size_t i = 0; i < bottom10.size(); i++)
	{
		if (searchString(vector_advertising.at(searchPosInteger(bottom10.at(i), GiveIDsIndexes("adv", vector_clients, vector_transactions, vector_advertising))).getProducts(), prod)==false)
		{
			return false;
		}
	}
	return true;
}

void VendeMaisMais::create_histogram()
{
	vector <string> vector_products = give_products();
	string aux_prod;

	//creating interesting clients histogram

	for (size_t i = 0; i < vect_adv_without_bottom10.size(); i++)
	{
		for (size_t j = 0; j < vect_adv_without_bottom10.at(i).getProducts().size(); j++)
		{
			aux_prod = vect_adv_without_bottom10.at(i).getProducts().at(j);
			if (check_bot10_all_bought(aux_prod)==false)
			{

					if (histogram_interesting.count(aux_prod) == 0)
					{
						histogram_interesting.insert(pair<string, int>(aux_prod, 1));
					}
					else
					{
						histogram_interesting.at(aux_prod)++;
					}
				
			}
			
		}
	}

	//creating bottom10 clientes histogram

	for (size_t i = 0; i < vect_adv_bottom10.size(); i++)
	{
		for (size_t j = 0; j < vect_adv_bottom10.at(i).getProducts().size(); j++)
		{
			aux_prod = vect_adv_bottom10.at(i).getProducts().at(j);
			if (check_bot10_all_bought(aux_prod) == false)
			{

				if (histogram_bottom10.count(aux_prod) == 0)
				{
					histogram_bottom10.insert(pair<string, int>(aux_prod, 1));
				}
				else
				{
					histogram_bottom10.at(aux_prod)++;
				}

			}

		}
	}
}

template <typename A, typename B>
multimap<B, A> VendeMaisMais::flip_map(const map<A, B> & src) {

	multimap<B, A> dst;

	for (map<A, B>::const_iterator it = src.begin(); it != src.end(); ++it)
		dst.insert(pair<B, A>(it->second, it->first));

	return dst;
}

int VendeMaisMais::check_prod_interesting_exists_bot10(string prod, multimap<int, string> sorted_histogram_bottom10)
{
	for (multimap<int, string>::const_iterator it = sorted_histogram_interesting.begin(); it != sorted_histogram_interesting.end(); ++it)
	{
		if (prod == it->second)
		{
			return it->first;
		}
	}
	return -1;
}

string VendeMaisMais::find_prod_to_make_publicity(multimap<int, string> sorted_histogram_interesting, multimap<int, string> sorted_histogram_bottom10)
{
	bool flag_found_product = false;
	int aux_qtd_bot10;
	
	multimap<int, string> combined_quantities;

	for (multimap<int, string>::const_reverse_iterator it = sorted_histogram_interesting.rbegin(); it != sorted_histogram_interesting.rend(); ++it)
	{
		if (searchString(allProducts, it->second)==false) //hasn't been bought by one of Bottom10
		{
			return it->second;
		}
	}

	for (multimap<int, string>::const_reverse_iterator it = sorted_histogram_interesting.rbegin(); it != sorted_histogram_interesting.rend(); ++it)
	{
		aux_qtd_bot10 = check_prod_interesting_exists_bot10(it->second, sorted_histogram_bottom10);
		if (aux_qtd_bot10 !=-1) //has been bought by one of Bottom10
		{
			combined_quantities.insert(pair<int, string>(it->first + aux_qtd_bot10, it->second));
		}
		else
		{
			combined_quantities.insert(pair<int, string>(it->first, it->second));

		}
	}
	
	for (multimap<int, string>::const_reverse_iterator it = combined_quantities.rbegin(); it != combined_quantities.rend(); ++it)
	{
		return it->second;
	}

	return "";
}

void VendeMaisMais::make_bottom10_advertising()
{
	string product;

	createVectorAdvertising();
	giveIdBottom10();
	allProductsOfBottom10();
	create_vec_with_and_without_Bot10();
	giveBuyersOfBottom10();
	create_histogram();

	sorted_histogram_interesting = flip_map(histogram_interesting); // sorted_histogram is now sorted by quantities of products
	sorted_histogram_bottom10 = flip_map(histogram_bottom10); // sorted_histogram is now sorted by quantities of products

	product = find_prod_to_make_publicity(sorted_histogram_interesting, sorted_histogram_bottom10);

	cout <<endl<< TAB << "Bottom10 should buy " << product << endl<<endl;

	vector_advertising.clear();
	vect_adv_bottom10.clear();
	vect_adv_without_bottom10.clear();
	vect_BuyersOfBottom10mais1.clear();
	allProducts.clear();
	bottom10.clear();

	system("pause");
}

/*********************************
* Clients Manager
********************************/

bool VendeMaisMais::checkID(int id, vector<Client>vector_clients)
{
	for (size_t i = 0; i < vector_clients.size(); i++)
	{
		if (id == vector_clients.at(i).getId())
			return true;
	}
	return false;
}

bool VendeMaisMais::checkName(string _name, vector<Client>vector_clients)
{
	for (size_t i = 0; i < vector_clients.size(); i++)
	{
		if (_name == vector_clients.at(i).getName())
			return true;
	}
	return false;
}

int VendeMaisMais::searchPosId(int id, vector<Client>vector_clients)
{
	for (size_t i = 0; i < vector_clients.size(); i++)
	{
		if (id == vector_clients.at(i).getId())
			return i;
	}
	return -1;
}

int VendeMaisMais::searchPosName(string _name, vector<Client>vector_clients)
{
	for (size_t i = 0; i < vector_clients.size(); i++)
	{
		if (_name == vector_clients.at(i).getName())
			return i;
	}
	return -1;
}

void VendeMaisMais::MaxId()
{
	maxClientsId = vector_clients.at(0).getId();
	for (size_t i = 1; i < vector_clients.size(); i++)
	{
		if (vector_clients.at(i).getId()>maxClientsId)
		{
			maxClientsId = vector_clients.at(i).getId();
		}
	}

}

void VendeMaisMais::showClientsAlphabetic()
{
	sort(vector_clients.begin(), vector_clients.end());
	clearScreen();

	cout << TAB << "###############       CLIENTS(" << vector_num_items.at(0) << ")       ###############" << endl;
	cout <<endl<< TAB << "ID             NAME                DATE        AMOUNT" << endl;
	cout << TAB << "--     --------------------     ----------    --------\n";
	for (size_t i = 0; i < vector_clients.size(); i++)
	{
		cout << TAB << vector_clients.at(i) << endl;
	}

	system("pause");
}

void VendeMaisMais::showClientByName()
{

	string name;
	cin.ignore();
	do
	{
		cout  <<endl<<TAB << "Client's name? ";
		getline(cin, name);
		if (!checkName(name, vector_clients))
			cout << TAB << "Error, this name doesn't exist.\n" <<TAB << "Please try again!" << endl;
	} while (!checkName(name, vector_clients));

	cout <<endl<<TAB<< "ID             NAME                DATE        AMOUNT" << endl;
	cout  <<TAB<< "--     --------------------     ----------    --------\n";
	for (size_t i = 0; i < vector_clients.size(); i++)
	{
		if (vector_clients.at(i).getName() == name)
		{
			cout << TAB << vector_clients.at(i) << endl;
		}
	}
	system("pause");
}

void VendeMaisMais::showClientById() 
{

	int id, pos;

	do
	{
		
		id=read_int("Client's id? ");
		if (!checkID(id, vector_clients))
			cout << TAB << "Error, this id doesn't exist."<<endl << TAB <<" Please try again!" << endl;
	} while (!checkID(id, vector_clients));
	pos = searchPosInteger(id, GiveIDsIndexes("cl", vector_clients, vector_transactions, vector_advertising));
	cout << endl <<TAB << "ID             NAME                DATE        AMOUNT" << endl;
	cout << TAB << "--     --------------------     ----------    --------\n";
	cout << TAB << vector_clients.at(pos) << endl;
		
	
	system("pause");
}

void VendeMaisMais::createClient()
{
	Client c1;
	string aux_name;
	Date new_date;



	c1.setId(++maxClientsId);
	cout <<endl<< TAB << "Name of the client ? ";
	cin.ignore();
	getline(cin, aux_name);
	c1.setName(aux_name);

	c1.setDate(new_date.getDate());
	c1.setAmount(read_double("Total amount of transactions ? "));
	vector_clients.push_back(c1);

	vector_num_items.at(0)++;

	cout <<endl << TAB << "Client successfully created!" << endl;
	changedClients = true;
	system("pause");
}

void VendeMaisMais::editClient()
{
	int pos, id;
	Client c1;
	string aux_name, aux_date;
	do
	{
		id = read_int("Client's id? ");
		if (!checkID(id, vector_clients))
			cout <<endl<< TAB << "Error, this ID doesn't exist.\n Please try again!" << endl;
	} while (!checkID(id, vector_clients));
	pos = searchPosId(id, vector_clients);

	int option2;
	cout << "1 - Change Name" << endl;
	cout << "2 - Change Amount" << endl;
	cout << "3 - Change Name and Amount" << endl;
	cout << "0 - Return to menu." << endl;
	option2 = read_op(0, 3);

	switch (option2)
	{
	case 1:
	{
		cout <<endl<< TAB << "Old name: " << vector_clients.at(pos).getName() << endl << "New name ? ";
		cin.ignore();
		getline(cin, aux_name);
		vector_clients.at(pos).setName(aux_name);
		break;
	}
	case 2:
	{
		cout << endl << TAB << "Old amount: " << vector_clients.at(pos).getAmount() << endl;
		vector_clients.at(pos).setAmount(read_double("New amount ? "));
		break;
	}
	case 3:
	{
		cout << endl << TAB << "Old name: " << vector_clients.at(pos).getName() << endl << "New name ? ";
		cin.ignore();
		getline(cin, aux_name);
		vector_clients.at(pos).setName(aux_name);
		cout << endl << TAB << "Old amount: " << vector_clients.at(pos).getAmount() << endl;
		vector_clients.at(pos).setAmount(read_double("New amount ? "));
		break;
	}
	}

	cout <<endl<< TAB << "Client successfully altered!" << endl;
	changedClients = true;
	system("pause");
}

void VendeMaisMais::removeClient()
{
	int id;
	Client c1;
	do
	{
		id = read_int("Client's id? ");
		if (!checkID(id, vector_clients))
			cout << TAB << "Error, this ID doesn't exist.\n" << TAB << "Please try again!" << endl;
	} while (!checkID(id, vector_clients));

	vector_clients.erase(vector_clients.begin() + searchPosId(id, vector_clients));
	vector_num_items.at(0)--;

	cout << TAB << "Client successfully deleted!" << endl;
	changedClients = true;
	system("pause");
}

void VendeMaisMais::totalSpent()
{
	totalSpentSum = 0;
	for (size_t i = 0; i < vector_clients.size(); i++)
	{
		totalSpentSum += vector_clients.at(i).getAmount();
	}
	

}

/*********************************
* Products Manager
********************************/

int VendeMaisMais::searchPosProduct(string prod_name, vector<Product>vector_products)
{
	for (size_t i = 0; i < vector_products.size(); i++)
	{
		if (prod_name == vector_products.at(i).getName())
		{
			return i;
		}
	}
	return -1;
}

void VendeMaisMais::showProducts() {

	sort(vector_products.begin(), vector_products.end());
	clearScreen();
	cout << TAB << "##########       PRODUCTS(" << vector_num_items.at(1) << ")       ##########" << endl;
	cout <<endl <<TAB<< "     NAME          CUST " << endl;
	cout << TAB << "-------------     -------\n";
	for (size_t i = 0; i < vector_products.size(); i++)
	{
		cout << TAB << vector_products.at(i);
	}

	system("pause");
}

vector <string> VendeMaisMais::give_products()
{
	vector <string> v1;
	for (size_t i = 0; i < vector_products.size(); i++)
	{
		v1.push_back(vector_products.at(i).getName());
	}
	return v1;
}

/*********************************
* Transactions Manager
********************************/

bool VendeMaisMais::checkIDT(int id, vector<Transaction>vector_transactions)
{
	for (size_t i = 0; i < vector_transactions.size(); i++)
	{
		if (id == vector_transactions.at(i).getIdClient())
			return true;
	}
	return false;
}

vector<int> VendeMaisMais::searchPosIdT(int id, vector <Transaction> vector_transactions)
{
	vector<int> id_pos;

	for (size_t i = 0; i < vector_transactions.size(); i++)
	{
		if (id == vector_transactions.at(i).getIdClient())
			id_pos.push_back(i);
	}

	return id_pos;
}

bool VendeMaisMais::checkDate(string date, vector <Transaction> vector_transactions)
{
	for (size_t i = 0; i < vector_transactions.size(); i++)
	{
		if (date == vector_transactions.at(i).getDate())
			return true;
	}
	return false;
}

vector<int> VendeMaisMais::searchPosDateT(string date, vector <Transaction> vector_transactions)
{
	vector<int> date_pos;

	for (size_t i = 0; i < vector_transactions.size(); i++)
	{
		if (date == vector_transactions.at(i).getDate())
			date_pos.push_back(i);
	}
	return date_pos;
}

void VendeMaisMais::showTransactionsByName()
{
	string name;
	int id, pos;
	cin.ignore();
	vector <int> aux_dates;
	map <int, int> ids_dates;
	do
	{
		cout <<endl<< TAB << "Client's name? ";
		getline(cin, name);
		if (!checkName(name, vector_clients))
			cout <<endl<< TAB << "Error, this name doesn't exist.\n"<<TAB <<"Please try again!" << endl;
	} while (!checkName(name, vector_clients));

	pos = searchPosName(name, vector_clients);
	id = vector_clients.at(pos).getId();
	vector<int>id_pos = searchPosIdT(id, vector_transactions);

	for (size_t i = 0; i < id_pos.size(); i++)
	{
		Date d1(vector_transactions.at(id_pos.at(i)).getDate());
		aux_dates.push_back(d1.getCompDate());
	}
	for (size_t i = 0; i < id_pos.size(); i++)
	{
		ids_dates.insert(pair<int, int>(aux_dates.at(i), id_pos.at(i)));
	}


	cout <<endl << TAB <<  "ID        DATE                      PRODUCTS" << endl;
	cout << TAB << "--     ----------   ---------------------------------------\n";

	for (map<int, int>::iterator it = ids_dates.begin(); it != ids_dates.end(); ++it)
	{
		cout << TAB << vector_transactions.at(it->second);
	}
	system("pause");

}

void VendeMaisMais::showTransactionsByID()
{
	int id;
	cin.ignore();
	vector <int> aux_dates;
	map <int, int> ids_dates;

	do
	{

		id = read_int("Client's id? ");
		if (!checkID(id, vector_clients))
			cout <<endl<< TAB << "Error, this id doesn't exist.\n"<<TAB<<"Please try again!" << endl;
	} while (!checkID(id, vector_clients));

	vector<int>id_pos = searchPosIdT(id, vector_transactions);

	for (size_t i = 0; i < id_pos.size(); i++)
	{
		Date d1(vector_transactions.at(id_pos.at(i)).getDate());
		aux_dates.push_back(d1.getCompDate());
	}
	for (size_t i = 0; i < id_pos.size(); i++)
	{
		ids_dates.insert(pair<int, int>(aux_dates.at(i), id_pos.at(i)));
	}


	cout << endl << TAB << "ID        DATE                      PRODUCTS" << endl;
	cout << TAB << "--     ----------   ---------------------------------------\n";

	for (map<int, int>::iterator it = ids_dates.begin(); it != ids_dates.end(); ++it)
	{
		cout << TAB << vector_transactions.at(it->second)<<endl;
	}
	system("pause");

}

void VendeMaisMais::showTransactionsByDay()
{
	string date;


	do
	{
		cout <<endl<< TAB << "Insert date(dd/mm/yyyy): ";
		cin >> date;
		if (!checkDate(date, vector_transactions))
			cout <<endl << TAB << "Error, this date doesn't exist.\n"<<TAB<<"Please try again!" << endl;
	} while (!checkDate(date, vector_transactions));

	
	vector<int>date_pos = searchPosDateT(date, vector_transactions);

	cout << endl << TAB  << "ID        DATE                      PRODUCTS" << endl;
	cout << TAB << "--     ----------   ---------------------------------------\n";

	for (size_t i = 0; i < date_pos.size(); i++)
	{
		cout << TAB << vector_transactions.at(date_pos.at(i))<<endl;
	}
	system("pause");
}

void VendeMaisMais::showTransactionsBetweenDates()
{
	int flag = 0, flag_date_exists = 0, flag1 = 0;
	string date_beg, date_end, date_new;
	do
	{
		if (flag1 >= 1)
		{
			cerr << endl << TAB << "Error, please indicate the last date greater then the first!" << endl;

		}

		do
		{
			if (flag >= 1)
			{
				cerr <<endl<<TAB<< "Error, please indicate valid date (dd/mm/yyyy)!" << endl;

			}
			cout <<endl << TAB << "First date (dd/mm/yyyy): ";
			cin >> date_beg;
			flag++;
		} while (is_valid_date(date_beg) == false);
		flag = 0;
		do
		{
			if (flag >= 1)
			{
				cerr <<endl<<TAB<< "Error, please indicate valid date (dd/mm/yyyy)!" << endl;

			}
			cout <<endl<< TAB << "Last date (dd/mm/yyyy): ";
			cin >> date_end;
			flag++;
		} while (is_valid_date(date_end) == false);

		
		flag = 0;
		flag1++;

	} while (verify_dates_end_gr_beg(date_beg, date_end) == false);

	cout << endl <<TAB  << "ID        DATE                      PRODUCTS" << endl;
	cout << TAB << "--     ----------   ---------------------------------------\n";
	for (size_t i = 0; i < vector_transactions.size(); i++)
	{
		if (verify_date_between(vector_transactions.at(i).getDate(), date_beg, date_end))
		{
			cout << TAB << vector_transactions.at(i)<<endl;
			flag_date_exists++;
		}

	}
	if (flag_date_exists == 0)
	{
		cout <<endl<< TAB << "There is no existing date between those two!" << endl;
	}
	system("pause");
}

void VendeMaisMais::showTransactions() {

	sort(vector_transactions.begin(), vector_transactions.end());
	clearScreen();

	cout << TAB << "##########       TRANSACTIONS(" << vector_num_items.at(2) << ")       ##########" << endl;
	cout <<endl << TAB << "ID        DATE                      PRODUCTS" << endl;
	cout << TAB << "--     ----------    ---------------------------------------\n";
	for (size_t i = 0; i < vector_transactions.size(); i++)
	{
		cout << TAB << vector_transactions.at(i)<<endl ;
	}

	system("pause");
}

void VendeMaisMais::makeTransaction()
{
	Date date;
	ofstream out;
	int id;
	string  do_not_belong = "";
	vector<string>products;
	string product;
	double price_to_add;
	Transaction t1;

	do
	{
		id = read_int("Client's id? ");
		if (!checkIDT(id, vector_transactions))
			cout <<endl<< TAB << "ID not found, please insert a valid ID." << endl;
	} while (!checkIDT(id, vector_transactions));
	cin.ignore(INT_MAX, '\n'); //Because getline is used right next

	showProducts();
	cout << endl << TAB << "Client's id = " << id << endl; //because listarProducts() clears the screen
	cout <<endl<< TAB << "Insert products and press Enter after each product (To end insert 0): ";


	do
	{
		getline(cin, product);
		if ((searchPosProduct(product, vector_products) != -1) && product != "0") // se existir adiciona
		{
			products.push_back(product);
		}

	} while (product != "0");
	t1 = Transaction(id, date.getDate(), products);
	vector_transactions.push_back(t1);

	price_to_add = vector_clients.at(searchPosId(id, vector_clients)).getAmount();
	for (size_t i = 0; i < products.size(); i++)
	{
		price_to_add += vector_products.at(searchPosProduct(products.at(i), vector_products)).getCust();
	}

	vector_clients.at(searchPosId(id, vector_clients)).setAmount(price_to_add);

	changedTransactions = true;
	changedClients = true;
	system("pause");
}


/*********************************
 * Save Information
 ********************************/

 // only saves the information of Clients and/or fo Transactions that has been changed

void VendeMaisMais::saveChanges() const {

	ofstream fout;

	if (changedClients)
	{

		fout.open(ClientsFile);
		fout << vector_num_items.at(0) << endl;
		for (size_t i = 0; i < vector_clients.size(); i++)
		{
			vector_clients.at(i).save(fout);

		}
		fout.close();
	}


	if (changedTransactions)
	{

		fout.open(TransactionsFile);
		fout << vector_num_items.at(2) << endl;
		for (size_t i = 0; i < vector_transactions.size(); i++)
		{
			vector_transactions.at(i).save(fout);

		}
		fout.close();
	}

}


/*********************************
 * Show Shop
 ********************************/

 // shows shop content

ostream& operator<<(ostream& out, const VendeMaisMais & supermarket) {

	out << "###########        STATISTICS        ###########" << endl << endl << "Number of clients: " << supermarket.vector_num_items.at(0) << endl << "Number of products: " << supermarket.vector_num_items.at(1) << endl << "Number of transactions: " << supermarket.vector_num_items.at(2) << endl << "Total spent in this store: " << supermarket.totalSpentSum << endl;
	system("pause");
	return out;
	
}
