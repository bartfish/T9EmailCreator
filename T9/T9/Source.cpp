#include "Trie.h"
#include "Messages.h"
#include <list>
#include <stdexcept>
#include "include\curses.h"

// TODO: IMPLEMENT SEARCHING FOR ALL WORDS - NOT ONLY FOR THE FIRST ONE
// SOLUTION: LIST


// implement class which will represemt the list of contacts

void draw_borders(WINDOW *screen)
{
	int x, y, i;
	getmaxyx(screen, y, x); // 4 corners 
	mvwprintw(screen, 0, 0, "+");
	mvwprintw(screen, y - 1, 0, "+");
	mvwprintw(screen, 0, x - 1, "+");
	mvwprintw(screen, y - 1, x - 1, "+"); // sides 
	for (i = 1; i < (y - 1); i++)
	{
		mvwprintw(screen, i, 0, "|");
		mvwprintw(screen, i, x - 1, "|");
	} // top and bottom 
	for (i = 1; i < (x - 1); i++)
	{
		mvwprintw(screen, 0, i, "-");
		mvwprintw(screen, y - 1, i, "-");
	}
}

int main()
{

	// choose between Email and sms

	

	int parent_x = 1000, parent_y = 500, new_x, new_y;
	int contact_size = 6; // contact loader 
	int topic_size = 6; // topic loader 
	int message_size = 15; // message loader
	int vocabulary_size = 10; // vocabulary loader
	int fifth_size = 4; // *vocabulary loader
	// sixth window defined for navigation bar
	initscr();
	noecho();

	curs_set(0); // get our maximum window dimensions 
	getmaxyx(stdscr, parent_y, parent_x); // set up initial windows 

	WINDOW *contact_window = newwin(contact_size, parent_x, 0, 0);
	WINDOW *topic_window = newwin(topic_size, parent_x, contact_size, 0); // draw to our windows 
	WINDOW *message_window = newwin(message_size, parent_x, contact_size + topic_size, 0); // draw to our windows 
	WINDOW *vocabulary_window = newwin(vocabulary_size, parent_x, contact_size + topic_size + message_size, 0); // draw to our windows 
	//WINDOW *fifth = newwin(fifth_size, parent_x, contact_size + topic_size + message_size + vocabulary_size, 0); // draw to our windows 

	// draw borders																											 // draw our borders 
	draw_borders(contact_window);
	draw_borders(topic_window); // simulate the game loop 
	draw_borders(message_window); // simulate the game loop 
	draw_borders(vocabulary_window); // simulate the game loop 
	//draw_borders(fifth); // simulate the game loop 
	
	// draw to our windows 
	mvwprintw(contact_window, 1, 1, "contact_window");
	mvwprintw(topic_window, 1, 1, "topic_window"); // refresh each window 
	mvwprintw(message_window, 1, 1, "message_window"); // refresh each window 
	mvwprintw(vocabulary_window, 1, 1, "vocabulary_window"); // refresh each window 
//	mvwprintw(fifth, 1, 1, "fifth"); // refresh each window 
	wrefresh(contact_window);
	wrefresh(topic_window);
	wrefresh(message_window);
	wrefresh(vocabulary_window);
	//wrefresh(fifth);

	//wsleep(5); // clean up 






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

	string word = "";
	string text = "";
	string str = "";

	char c;
	int cursor_position_x = 1;
	werase(contact_window);
	draw_borders(contact_window);

	while (1)
	{
		//mvwprintw(contact_window, text.length(), 1, text.c_str());
		wrefresh(contact_window);

		c = mvwgetch(contact_window, 1, 1);
		if (c == ' ')
		{
			if (text != "")
			{
				text += " ";
			}
			text += word;
			word = "";
			
			mvwprintw(contact_window, 1, 1, text.c_str());
			cursor_position_x = text.length()+2;
			wrefresh(contact_window);

			continue;
		}
		else if (c == 8)
		{
			if (word.length() > 0)
			{
				word.pop_back();
				//mvwprintw(contact_window, 1, 1, word.c_str());
				wrefresh(contact_window);
			}
			else {
				word = "";
			}
		}
		else {
			word += c;
		}
		//cout << text << " " << word;
		mvwprintw(contact_window, 1, cursor_position_x, word.c_str());
		wrefresh(contact_window);

		str = "";
		vector<string> r = M.load_all_words_from_voc(word);
		for (vector<string>::iterator it = r.begin(); it != r.end(); it++) 
		{
			str += *it + ", ";
		}
		
		werase(vocabulary_window);
		wrefresh(vocabulary_window);

		draw_borders(contact_window);
		draw_borders(topic_window); // simulate the game loop 
		draw_borders(message_window); // simulate the game loop 
		draw_borders(vocabulary_window); // simulate the game loop 
		//draw_borders(fifth); // simulate the game loop 


		mvwprintw(vocabulary_window, 1, 1, str.c_str());
		wrefresh(vocabulary_window);

		if (c == 27)
		{
			break;
		}
	}



	vector <string> EmailVoc = M.load_all_words_from_voc("b");

	string emails_str = "";
	vector<string> r = EmailVoc;// .load_all_words("f");
	int left = 0, top = 2;
	for (vector<string>::iterator it = r.begin(); it != r.end(); it++) {
		//cout << *it << "\n";
		emails_str += *it + ", ";
	}
	mvwprintw(vocabulary_window, left, top, emails_str.c_str());
	wrefresh(vocabulary_window);


 	word = "";
	text  = "";
	str = "";
	
	while (1)
	{
		//str = "start \"Help\" cmd /C \"echo off &";
		c = _getch();
			if (c == ' ')
			{
				if (text != "")
				{
					text += " ";
				}
				text += word;
				word = "";

				//system("cls");

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
			//system("cls");
			cout << text << " " << word;

			vector<string> r = Words.load_all_words(word);
			for (vector<string>::iterator it = r.begin(); it != r.end(); it++) {
				
				cout.width(60);
				cout << right << *it << endl;
				//str += " echo ";
				str += *it;
			//	str += " & ";

			}
			//str += " pause \"";
			//const char * c_s = str.c_str();
			// option for showing characters on separate cmds
			//system(c_s);
			//system("start \"Help\" cmd /C \"echo off & echo Help text 1 & echo Help text 2 & echo Help text 3 & pause\"");
			if (c == 27)
			{
				break;
			}
		
	}
		
	delwin(contact_window);
	delwin(topic_window);
	delwin(message_window);
	delwin(vocabulary_window);
	//delwin(fifth);
	endwin();

	system("pause");
	return 0;
}