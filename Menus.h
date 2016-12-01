#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "defs.h"
#include "utils.h"
#include "Read_files.h"
#include "Vende++.h"

using namespace std;

bool infoInicial(string & shop, string & ClientsFile, string & ProductsFile, string & TransactionsFile);

void startOptions(VendeMaisMais & supermarket);

void optionsClients(VendeMaisMais & supermarket);

void optionsTransactions(VendeMaisMais & supermarket);

void optionsAdvertising(VendeMaisMais & supermarket);

