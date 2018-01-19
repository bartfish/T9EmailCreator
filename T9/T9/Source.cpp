#include "Trie.h"
#include "Messages.h"
#include <list>
#include <stdexcept>
#include "include\curses.h"

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
void load_main_console(vector <WINDOW*> wins, vector<string> wins_titles)
{

	// draw borders		
	vector<string>::iterator it = wins_titles.begin();
	vector<WINDOW*>::iterator itw = wins.begin();
	while (itw != wins.end())
	{
		draw_borders(*itw);
		itw++;
	}

	itw = wins.begin();
	while(it != wins_titles.end())
	{
		mvwprintw(*itw, 1, 1, (*it).c_str());
		it++;
		itw++;
	}

	itw = wins.begin();
	while (itw != wins.end())
	{
		wrefresh(*itw);
		itw++;
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
	initscr();
	noecho();

	// load menu
	/*cout << "/////// EMAIL & SMS CREATOR //////" << endl;
	cout << "Choose: " << endl; 
	cout << "1 to create an email" << endl;
	cout << "2 to create a SMS" << endl;
	char choice;
	switch (choice)
	{
	case 1:
		break;
	case 2:
		break;
	}*/

	curs_set(0); // get our maximum window dimensions 
	getmaxyx(stdscr, parent_y, parent_x); // set up initial windows 

	// staticly define windows needed for visual representation
	WINDOW *contact_window = newwin(contact_size, parent_x, 0, 0);
	WINDOW *topic_window = newwin(topic_size, parent_x, contact_size, 0); // draw to our windows 
	WINDOW *message_window = newwin(message_size, parent_x, contact_size + topic_size, 0); // draw to our windows 
	WINDOW *vocabulary_window = newwin(vocabulary_size, parent_x, contact_size + topic_size + message_size, 0); // draw to our windows 

	// number of windows must be equal to number of titles
	vector<WINDOW*> wins = { contact_window, topic_window, message_window, vocabulary_window };
	vector<string> wins_titles = { "Contact", "Topic", "Message", "Vocabulary" };
	load_main_console(wins, wins_titles);

	Trie Emails("");
	//Trie Words("");
	//Trie Phones("");

	//ifstream file("words.txt");
	//ifstream emails("emails.txt");
	//ifstream phones("phones.txt");
	string s;

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
			cursor_position_x = text.length()+2; // word end + space
			wrefresh(contact_window);

			continue;
		}
		else if (c == KEY_BACKSPACE)
		{
			if (word.length() > 0)
			{
				word.pop_back();

				mvwprintw(contact_window, 1, cursor_position_x-1, word.c_str());
				wrefresh(contact_window);
			}
			else {
				word = "";
			}
		}
		else {
			word += c;
		}

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


		mvwprintw(vocabulary_window, 1, 1, str.c_str());
		wrefresh(vocabulary_window);

		if (c == 27)
		{
			break;
		}
	}

	// contact
	// ->tab
	// topic
	// ->tab
	// message


	delwin(contact_window);
	delwin(topic_window);
	delwin(message_window);
	delwin(vocabulary_window);
	endwin();

	system("pause");
	return 0;
}