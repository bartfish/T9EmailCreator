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
	M.create_message();

	// load options
		// save message

	delwin(contact_window);
	delwin(topic_window);
	delwin(message_window);
	delwin(vocabulary_window);
	endwin();

	system("pause");
	return 0;
}