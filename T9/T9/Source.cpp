#include "Trie.h"
#include "Messages.h"
#include <list>
#include <stdexcept>

// TODO: IMPLEMENT SEARCHING FOR ALL WORDS - NOT ONLY FOR THE FIRST ONE
// SOLUTION: LIST


// implement class which will represemt the list of contacts


int main()
{

	Trie Emails("");
	Trie Words("");
	Trie Phones("");

	ifstream file("words.txt");
	ifstream emails("emails.txt");
	ifstream phones("phones.txt");
	string s;

	int n = 0;
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	while (getline(file, s))
	{
		n++;
		Words.insert(s);
		transform(s.begin(), s.end(), s.begin(), ::tolower);
	}

	n = 0;
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	while (getline(emails, s))
	{
		n++;
		Emails.insert(s);
		transform(s.begin(), s.end(), s.begin(), ::tolower);
	}

	n = 0;
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	while (getline(phones, s))
	{
		n++;
		Phones.insert(s);
		transform(s.begin(), s.end(), s.begin(), ::tolower);
	}

	// ERROR EXTERNAL SYMBOL
	Email M;
	M.load_vocabulary("emails.txt");
	M.assign_message_content("message");

	vector <string> EmailVoc = M.load_all_words_from_voc("b");

	vector<string> r = EmailVoc;// .load_all_words("f");
	for (vector<string>::iterator it = r.begin(); it != r.end(); it++) {
		cout << *it << "\n";
	}


 	string word = "";
	string text  = "";
	string str = "";
	
	char c;
	while (1)
	{
		str = "start \"Help\" cmd /C \"echo off &";
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

				cout << text << "\n";

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

			vector<string> r = Words.load_all_words(word);
			for (vector<string>::iterator it = r.begin(); it != r.end(); it++) {
				
				cout.width(60);
				cout << right << *it << endl;
				str += " echo ";
				str += *it;
				str += " & ";

			}
			str += " pause \"";
			const char * c_s = str.c_str();
			// option for showing characters on separate cmds
			system(c_s);
			//system("start \"Help\" cmd /C \"echo off & echo Help text 1 & echo Help text 2 & echo Help text 3 & pause\"");
			if (c == 27)
			{
				break;
			}
		
	}
		
		
	//system("start \"Help\" cmd /C \"echo off & echo Help text 1 & echo Help text 2 & echo Help text 3 & pause\"");


	system("pause");
	return 0;
}