#include "libraries.h"
#include "myConsoleManager.h"

void myConsoleManager::generate_message_windows()
{
	system("cls");

	// number of windows must be equal to number of titles
	vector<WINDOW*> wins = { title_window, contact_window, topic_window, message_window, vocabulary_window, error_window };
	vector<string> wins_titles = { navigation_bar_informations, "Contact", "Topic", "Message", "Vocabulary", "Error window for valdation messages" };
	myConsoleManager::load_main_console(wins, wins_titles);

}
void myConsoleManager::draw_borders(WINDOW *screen)
{

	getmaxyx(screen, y, x); // 4 corners 
	mvwprintw(screen, 0, 0, "+");
	mvwprintw(screen, y - 1, 0, "+");
	mvwprintw(screen, 0, x - 1, "+");
	mvwprintw(screen, y - 1, x - 1, "+"); // sides 
	for (i = 1; i < (y - 1); i++)
	{
		mvwprintw(screen, i, 0, "|");
		mvwprintw(screen, i, x - 1, "|");
	}
	// top and bottom 
	for (i = 1; i < (x - 1); i++)
	{
		mvwprintw(screen, 0, i, "-");
		mvwprintw(screen, y - 1, i, "-");
	}
}
void myConsoleManager::load_main_console(vector <WINDOW*> wins, vector<string> wins_titles)
{

	// draw borders		
	vector<string>::iterator it = wins_titles.begin();
	vector<WINDOW*>::iterator itw = wins.begin();
	while (it != wins_titles.end())
	{
		mvwprintw(*itw, 1, 1, (*it).c_str());
		it++;
		itw++;
	}

	itw = wins.begin();
	while (itw != wins.end())
	{
		draw_borders(*itw);
		itw++;
	}


	itw = wins.begin();
	while (itw != wins.end())
	{
		wrefresh(*itw);
		itw++;
	}

}
void myConsoleManager::backspace_clicked(string &s, int cursor_position_x, WINDOW *the_window)
{
	s.pop_back();
	string a = s;
	werase(the_window);
	mvwprintw(the_window, 1, 1, s.c_str());
	wrefresh(the_window);
	myConsoleManager::draw_borders(the_window);
}
void myConsoleManager::set_default_title_window()
{
	werase(title_window);
	mvwprintw(title_window, 1, 1, navigation_bar_informations.c_str());
	myConsoleManager::draw_borders(title_window);
	wrefresh(title_window);

}
void myConsoleManager::close_windows()
{
	delwin(title_window);
	delwin(contact_window);
	delwin(topic_window);
	delwin(message_window);
	delwin(vocabulary_window);
	delwin(error_window);
}

int myConsoleManager::generate_navigation_bar()
{
	initscr();
	noecho();
	curs_set(0); // get our maximum window dimensions 
	getmaxyx(stdscr, parent_y, parent_x); // set up initial windows 

	system("cls");
	
	cout << "/////// EMAIL & SMS CREATOR //////" << endl;
	cout << "Choose: " << endl;
	cout << "1 to create an email" << endl;
	cout << "2 to create a SMS" << endl;

	cout << endl << "Your choice: (enter number and the program will continue)";
	int choice = _getch();

	int c = choice;
	return c;
}

void myConsoleManager::reset_message_vars(string & word, string &text, string &str, bool &can_exit_while, 
	int &cursor_position_x, 
	int &cursor_position_y)
{
	word = "";
	text = "";
	str = "";
	can_exit_while = false;
	cursor_position_x = 1;
}

void myConsoleManager::update_window_content(WINDOW * u_vocabulary_window, const string &str, int x, int y)
{
	werase(u_vocabulary_window);
	wrefresh(u_vocabulary_window);

	draw_borders(u_vocabulary_window);

	mvwprintw(u_vocabulary_window, x, y, str.c_str());
	wrefresh(u_vocabulary_window);

}
void myConsoleManager::clean_window_content(WINDOW * u_window)
{
	werase(u_window);
	myConsoleManager::draw_borders(u_window);
	wrefresh(u_window);
}
string myConsoleManager::load_vocabulary_content(vector<string> words_arr)
{
	string words = "";
	for (vector<string>::iterator it = words_arr.begin(); it != words_arr.end(); it++)
	{
		words += *it + ", ";
	}
	return words;
}