#pragma once
#include "libraries.h"
class Trie {
public:
	map<char, Trie> children;
	string value;
	bool is_end_of_word; // for loading words from trie (load when the bool is true)

	Trie(const string &);
	void add(char c);
	//string find(const string &); // overloading classic function
	void insert(const string & word);

	vector<string> all_prefixes();
	vector<string> load_all_words(const string & s);
};