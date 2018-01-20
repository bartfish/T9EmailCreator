#include "Trie.h"
#include "Messages.h"
#include <list>
#include <stdexcept>
#include "ConsoleManager.h"

int main()
{
	// choose between Email and sms
	int parent_x = 1000, parent_y = 500, new_x, new_y;
	int title_size = 3; // contact loader 
	int contact_size = 6; // contact loader 
	int topic_size = 6; // topic loader 
	int message_size = 15; // message loader
	int vocabulary_size = 10; // vocabulary loader
	
	initscr();
	noecho();

	ConsoleManager Con;

	curs_set(0); // get our maximum window dimensions 
	getmaxyx(stdscr, parent_y, parent_x); // set up initial windows 

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

	// defined windows needed for visual representation
	WINDOW *title_window = newwin(title_size, parent_x, 0, 0);
	WINDOW *contact_window = newwin(contact_size, parent_x, title_size, 0);
	WINDOW *topic_window = newwin(topic_size, parent_x, contact_size + title_size, 0); // draw to our windows 
	WINDOW *message_window = newwin(message_size, parent_x, contact_size + topic_size + title_size, 0); // draw to our windows 
	WINDOW *vocabulary_window = newwin(vocabulary_size, parent_x, contact_size + topic_size + message_size + title_size, 0); // draw to our windows 
	
	// number of windows must be equal to number of titles
	vector<WINDOW*> wins = { title_window, contact_window, topic_window, message_window, vocabulary_window };
	vector<string> wins_titles = { "TypeOfMessageTitle", "Contact", "Topic", "Message", "Vocabulary" };
	Con.load_main_console(wins, wins_titles);

	Email M;
	M.load_vocabulary("words.txt");
	M.load_contacts();
	M.assign_message_content("message");

	string word = "";
	string text = "";
	string str = "";

	char c;
	int cursor_position_x = 1;
	werase(contact_window);
	Con.draw_borders(contact_window);

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
		else if (c == 8)
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
		vector<string> r = M.load_all_words_from_contacts(word);
		for (vector<string>::iterator it = r.begin(); it != r.end(); it++) 
		{
			str += *it + ", ";
		}
		
		werase(vocabulary_window);
		wrefresh(vocabulary_window);

		Con.draw_borders(contact_window);
		Con.draw_borders(topic_window); // simulate the game loop 
		Con.draw_borders(message_window); // simulate the game loop 
		Con.draw_borders(vocabulary_window); // simulate the game loop 


		mvwprintw(vocabulary_window, 1, 1, str.c_str());
		wrefresh(vocabulary_window);

		if (c == 27 || c == 9)
		{
			break;
		}
	}

	word = "";
	text = "";
	str = "";
	cursor_position_x = 1;
	werase(topic_window);
	Con.draw_borders(topic_window);


	while (1)
	{
		wrefresh(topic_window);
		c = mvwgetch(topic_window, 1, 1);

		if (c == ' ')
		{
			if (text != "")
			{
				text += " ";
			}
			text += word;
			word = "";

			mvwprintw(topic_window, 1, 1, text.c_str());
			cursor_position_x = text.length() + 2; // word end + space
			wrefresh(topic_window);

			continue;
		}
		else if (c == 8)
		{
			if (word.length() > 0)
			{
				word.pop_back();

				mvwprintw(topic_window, 1, cursor_position_x - 1, word.c_str());
				wrefresh(topic_window);
			}
			else {
				word = "";
			}
		}
		else {
			word += c;
		}

		mvwprintw(topic_window, 1, cursor_position_x, word.c_str());
		wrefresh(topic_window);

		str = "";
		vector<string> r = M.load_all_words_from_voc(word);
		for (vector<string>::iterator it = r.begin(); it != r.end(); it++)
		{
			str += *it + ", ";
		}

		werase(vocabulary_window);
		wrefresh(vocabulary_window);

		Con.draw_borders(contact_window);
		Con.draw_borders(topic_window); // simulate the game loop 
		Con.draw_borders(message_window); // simulate the game loop 
		Con.draw_borders(vocabulary_window); // simulate the game loop 

		mvwprintw(vocabulary_window, 1, 1, str.c_str());
		wrefresh(vocabulary_window);

		if (c == 27 || c == 9)
		{
			break;
		}
	}


	word = "";
	text = "";
	str = "";
	cursor_position_x = 1;
	werase(message_window);
	Con.draw_borders(message_window);
	while (1)
	{
		wrefresh(message_window);
		c = mvwgetch(message_window, 1, 1);

		if (c == ' ')
		{
			if (text != "")
			{
				text += " ";
			}
			text += word;
			word = "";

			mvwprintw(message_window, 1, 1, text.c_str());
			cursor_position_x = text.length() + 2; // word end + space
			wrefresh(message_window);

			continue;
		}
		else if (c == 8)
		{
			if (word.length() > 0)
			{
				word.pop_back();

				mvwprintw(message_window, 1, cursor_position_x - 1, word.c_str());
				wrefresh(message_window);
			}
			else {
				word = "";
			}
		}
		else {
			word += c;
		}

		mvwprintw(message_window, 1, cursor_position_x, word.c_str());
		wrefresh(message_window);

		str = "";
		vector<string> r = M.load_all_words_from_voc(word);
		for (vector<string>::iterator it = r.begin(); it != r.end(); it++)
		{
			str += *it + ", ";
		}

		werase(vocabulary_window);
		wrefresh(vocabulary_window);

		Con.draw_borders(contact_window);
		Con.draw_borders(topic_window); // simulate the game loop 
		Con.draw_borders(message_window); // simulate the game loop 
		Con.draw_borders(vocabulary_window); // simulate the game loop 

		mvwprintw(vocabulary_window, 1, 1, str.c_str());
		wrefresh(vocabulary_window);

		if (c == 27 || c == 9)
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