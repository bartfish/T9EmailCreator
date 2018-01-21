#pragma once
#include "libraries.h"
class Trie {
public:
	map<char, Trie> children;
	string value;
	bool flag;

	Trie(const string &);
	void add(char);
	//string find(const string &); // overloading classic function
	void insert(const string &);

	vector<string> all_prefixes();
	vector<string> load_all_words(const string &);
};