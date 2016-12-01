#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <windows.h>

#include "defs.h"
#include "Date.h"

using namespace std;

// Clear command line
void clearScreen();

// Open the file; exit program if the file couldn't be opened
bool fileExists(string fileName);

//Delete whitespace in a string
void DeleteWhitespace(string &s);

//Delete whitespace in a string but return a string
string truncate_strings(string word);

//Check if date is valid( more than 31 days and so on...)
bool is_valid_date(string date);

//Check if year is leap year
bool bissextile(int &ano);

//Check if a string has only letters
bool check_has_letters(string str);

//Check if a string has only digits
bool check_has_digits(string str);

//Check if a string(double) has only digits
double read_double(string msg);

//Check if a string(integer) has only digits
int read_int(string msg);

//Check if operator has valid
unsigned int read_op(int min, int max);

//Return index of position of item(integer) in certain vector
int searchPosInteger(int elem, vector <int> v1);

//Return index of position of item(string) in certain vector
int searchPosString(vector <string> v1, string str);

//Check if item(string) exists in certain vector
bool searchString(vector <string> v1, string str);

//Check if range of dates is correct
bool verify_dates_end_gr_beg(string date_beg, string date_end);

//Splits a string until a specific char
vector <string> split(string line, char delim);

//Checks if a date is between a certain range
bool verify_date_between(string date_new, string date_beg, string date_end);

//Write a string with products
string write_vector_products_name(vector <string> vec);

//Get a maximum value of a vector of integers
int getMax(vector <int> v1);

//Turns all string's letters, into upper
string toupper_string(string s);

