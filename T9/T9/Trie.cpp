#include "Trie.h"

Trie::Trie(const string &val="") : value(val), is_end_of_word(false) {}

void Trie::add(char c) {

	string s;
	stringstream ss;
	ss << c;
	ss >> s;

	if (value == "")
	{
		children[c] = Trie(s);
	}
	else
	{
		children[c] = Trie(value + c);
	}
}

void Trie::insert(const string &word) {
	Trie * node = this;
	for (int i = 0; i < word.length(); i++) {
		const char c = word[i];
		if (node->children.find(c) == node->children.end())
			node->add(c);
		node = &node->children[c];
	}
	node->is_end_of_word = true;
}

vector<string> Trie::all_prefixes() {
	vector<string> words_list;
	if (is_end_of_word)
		words_list.push_back(value);

	if (children.size()) {
		map<char, Trie>::iterator iter;
		vector<string>::iterator node;
		for (iter = children.begin(); iter != children.end(); iter++) {
			vector<string> nodes = iter->second.all_prefixes();
			words_list.insert(words_list.end(), nodes.begin(), nodes.end());
		}
	}
	return words_list;
}

vector<string> Trie::load_all_words(const string &prefix) {
	Trie * node = this;
	vector<string> words_list;
	for (int i = 0; i < prefix.length(); i++) {
		const char c = prefix[i];
		if (node->children.find(c) == node->children.end())
			return words_list;
		else
			node = &node->children[c];
	}
	return node->all_prefixes();
}