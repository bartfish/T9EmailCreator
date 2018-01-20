#include "Messages.h"

void Message::load_vocabulary(const string & file_name)
{
	string s;
	ifstream words_file(file_name);

	int n = 0;
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	while (getline(words_file, s))
	{
		n++;
		Vocabulary.insert(s);
		transform(s.begin(), s.end(), s.begin(), ::tolower);
	}
}
vector<string> Message::load_all_words_from_voc(const string & s)
{
	return Vocabulary.load_all_words(s);
}
