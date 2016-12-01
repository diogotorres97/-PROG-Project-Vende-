#include "Read_files.h"

void ask_fileNames(string & ClientsFile, string & ProductsFile, string & TransactionsFile)
{
	cout << "Insert files names: " << endl;
	do
	{
		cout << "Clients File ? ";
		cin >> ClientsFile;
	} while (!fileExists(ClientsFile));

	do
	{
		cout << "Products File ? ";
		cin >> ProductsFile;
	} while (!fileExists(ProductsFile));

	do
	{
		cout << "Transactions File ? ";
		cin >> TransactionsFile;
	} while (!fileExists(TransactionsFile));

}

bool check_clients_files(string fileName, vector<Client> &vector_clients)
{
	ifstream f;
	string line;
	f.open(fileName);
	int aux_number_items;
	if (f.peek() == ifstream::traits_type::eof())
	{
		return false;
	}
	getline(f, line);
	aux_number_items = stoi(line);
	while (getline(f, line)) {

		vector <string> elems;
		istringstream is;
		string aux_date, aux_id, aux_amount, aux_name;


		char h1;
		is.str(line);
		is >> aux_id >> h1;
		elems.push_back(aux_id);
		getline(is, aux_name, ';');
		elems.push_back(truncate_strings(aux_name));
		getline(is, aux_date, ';');
		elems.push_back(truncate_strings(aux_date));
		is >> aux_amount;

		elems.push_back(aux_amount);
		if (check_has_letters(elems.at(0)) || !is_valid_date(elems.at(2)) || check_has_letters(elems.at(3)))
		{
			return false;
		}

	}
	return true;
}

bool check_products_files(string fileName, vector<Product> &vector_products)
{
	ifstream f;
	string line;
	f.open(fileName);
	int aux_number_items;

	if (f.peek() == ifstream::traits_type::eof())
	{
		return false;
	}
	getline(f, line);
	aux_number_items = stoi(line);
	while (getline(f, line)) {
		vector <string> elems;
		istringstream is;
		string aux_name;
		string value;

		is.str(line);
		getline(is, aux_name, ';');

		is >> value;
		if (check_has_letters(value))
		{
			return false;
		}
	}
	return true;
}

bool check_trans_files(string fileName, vector<Client> &vector_clients, vector<Product> &vector_products, vector<Transaction> &vector_transactions, vector<Transaction> &vector_advertising)
{
	ifstream f;
	string line;
	f.open(fileName);
	vector <string> aux_prod;
	int aux_number_items;

	if (f.peek() == ifstream::traits_type::eof())
	{
		return false;
	}
	getline(f, line);
	aux_number_items = stoi(line);
	vector<int> ids = GiveIDsIndexes("cl", vector_clients, vector_transactions, vector_advertising);
	vector<string> products = give_products(vector_products);
	while (getline(f, line))
	{
		vector <string> elems;
		istringstream is;
		string aux_date;
		string aux_id;

		is.str(line);
		getline(is, aux_id, ';');
		DeleteWhitespace(aux_id);
		elems.push_back(aux_id);
		getline(is, aux_date, ';');
		DeleteWhitespace(aux_date);
		elems.push_back(aux_date);


		if (check_has_letters(elems.at(0)) || !is_valid_date(elems.at(1)))
		{
			return false;
		}
		else
		{
			if (searchPosInteger(stoi(elems.at(0)), ids) == -1)
			{
				return false;
			}
			while (getline(is, line, ','))
			{
				aux_prod.push_back(truncate_strings(line));
			}

			for (size_t i = 0; i < aux_prod.size(); i++)
			{
				if (searchPosString(products, aux_prod.at(i)) == -1)
				{
					cout << i << endl;
					return false;
				}
			}
		}
	}
	return true;
}

void read_clients_file(string fileName, vector<Client> &vector_clients, vector <int> &vector_num_items)
{
	ifstream f;
	string line;

	if (check_clients_files(fileName, vector_clients) == false)
	{
		cerr << "Clients file has invalid values!!! Please correct them." << endl;
		system("pause");
		exit(1);
	}

	f.open(fileName);
	int numberProducts;

	getline(f, line);
	istringstream is;
	is.str(line);
	is >> numberProducts;
	vector_num_items.push_back(numberProducts);


	while (getline(f, line))
	{
		Client c1(line);
		vector_clients.push_back(c1);
	}
	f.close();
}

void read_products_file(string fileName, vector<Product> &vector_products, vector <int> &vector_num_items)
{
	ifstream f;
	string line;

	if (!check_products_files(fileName, vector_products))
	{
		cerr << "Products file has invalid values!!! Please correct them." << endl;
		system("pause");
		exit(1);
	}

	f.open(fileName);

	int numberProducts;

	getline(f, line);
	istringstream is;
	is.str(line);
	is >> numberProducts;
	vector_num_items.push_back(numberProducts);


	while (getline(f, line))
	{
		Product p1(line);
		vector_products.push_back(p1);
	}

	f.close();

}

void read_trans_file(string fileName, vector<Client> &vector_clients, vector<Product> &vector_products, vector<Transaction> &vector_transactions, vector<Transaction> &vector_advertising, vector <int> &vector_num_items)
{

	if (check_trans_files(fileName, vector_clients, vector_products, vector_transactions, vector_advertising) == false)
	{
		cerr << "Transactions file has invalid values!!! Please correct them." << endl;
		system("pause");
		exit(1);
	}

	ifstream f;
	f.open(fileName);
	string line2;
	getline(f, line2);
	istringstream is;
	is.str(line2);
	int numberProducts;
	is >> numberProducts;
	vector_num_items.push_back(numberProducts);

	while (getline(f, line2))
	{
		Transaction t1(line2);
		vector_transactions.push_back(t1);
	}
	f.close();
}

vector <string> give_products(vector<Product>vector_products)
{
	vector <string> v1;
	for (size_t i = 0; i < vector_products.size(); i++)
	{
		v1.push_back(vector_products.at(i).getName());
	}
	return v1;
}

vector <int> GiveIDsIndexes(string which_vec, vector<Client> &vector_clients, vector<Transaction> &vector_transactions, vector<Transaction> &vector_advertising)
{
	vector <int> ids; //vector that takes the clients id's from the given vector and associates them with the indexes they have in a vector

	if (which_vec == "adv")
	{
		for (size_t i = 0; i < vector_advertising.size(); i++)
		{
			ids.push_back(vector_advertising.at(i).getIdClient());
		}
	}
	if (which_vec == "cl")
	{
		for (size_t i = 0; i < vector_clients.size(); i++)
		{
			ids.push_back(vector_clients.at(i).getId());
		}
	}

	if (which_vec == "tr")
	{
		for (size_t i = 0; i < vector_transactions.size(); i++)
		{
			ids.push_back(vector_transactions.at(i).getIdClient());
		}
	}



	return ids;


}
