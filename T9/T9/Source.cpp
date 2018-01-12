#include "Trie.h"
#include <list>

// TODO: IMPLEMENT SEARCHING FOR ALL WORDS - NOT ONLY FOR THE FIRST ONE
// SOLUTION: LIST

class word
{

private:
	string value;

public:
	word()
	{
		value = "";
	}
	word(const string & val)
	{
		value = val;
	}
	~word() {};
};

class Text : public word
{
	protected:
		list<word> listOfWords;
	public: 
		Text() {};
		~Text() {};
		void insertWordIntoText(const word & w);
};

int main()
{

	Trie T("");

	ifstream file("words.txt");
	string s;

	int n = 0;
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	while (getline(file, s))
	{
		n++;
		T.insert(s);
		transform(s.begin(), s.end(), s.begin(), ::tolower);
	}

	vector<string> r = T.load_all_words("F");
	for (vector<string>::iterator it = r.begin(); it != r.end(); it++) {
		cout << *it << endl;
	}

	string word = "";
	string text  = "";
	char c;
	while (1)
	{
		c = _getch();
			if (c == ' ')
			{
				if (text != "")
				{
					text += " ";
				}
				text += word;
				word = "";

				system("cls");

				cout << text << endl;

				continue;
			}
			else if (c == 8)
			{
				if (word.length() > 0)
				{
					word.pop_back();
				}
				else {
					word = "";
				}
			} else {
				word += c;
			}
			system("cls");
			cout << text << " " << word;

			vector<string> r = T.load_all_words(word);
			for (vector<string>::iterator it = r.begin(); it != r.end(); it++) {
				cout.width(60);
				cout << right << *it << endl;
			}
			if (c == 27)
			{
				cout << endl;
				break;
			}
		
	}
		
		



	system("pause");
	return 0;
}