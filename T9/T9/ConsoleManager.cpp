#include "libraries.h"
#include "myConsoleManager.h"

void myConsoleManager::generate_message_windows()
{
	initscr();
	noecho();
	curs_set(0); // get our maximum window dimensions 
	getmaxyx(stdscr, parent_y, parent_x); // set up initial windows 
	
	title_window = newwin(title_size, parent_x, 0, 0);
	contact_window = newwin(contact_size, parent_x, title_size, 0);
	topic_window = newwin(topic_size, parent_x, contact_size + title_size, 0); // draw to our windows 
	message_window = newwin(message_size, parent_x, contact_size + topic_size + title_size, 0); // draw to our windows 
	vocabulary_window = newwin(vocabulary_size, parent_x, contact_size + topic_size + message_size + title_size, 0); // draw to our windows 
	error_window = newwin(error_size, parent_x, contact_size + topic_size + message_size + title_size + vocabulary_size, 0); // draw to our windows 
	
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
	while (itw != wins.end())
	{
		draw_borders(*itw);
		itw++;
	}

	itw = wins.begin();
	while (it != wins_titles.end())
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

void myConsoleManager::backspace_clicked(string &s, int cursor_position_x, WINDOW *the_window)
{
	s.pop_back();
	werase(the_window);
	mvwprintw(the_window, 1, cursor_position_x - 1, s.c_str());
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

void myConsoleManager::clear_screen_from_message_windows()
{
	werase(title_window);
	werase(contact_window);
	werase(topic_window);
	werase(message_window);
	werase(vocabulary_window);
	werase(error_window);

	wrefresh(title_window);
	wrefresh(contact_window);
	wrefresh(topic_window);
	wrefresh(message_window);
	wrefresh(vocabulary_window);
	wrefresh(error_window);
}

void myConsoleManager::generate_navigation_bar()
{
	initscr();
	noecho();
	curs_set(0); // get our maximum window dimensions 
	getmaxyx(stdscr, parent_y, parent_x); // set up initial windows 

	clear_screen_from_message_windows();

	nav_window = newwin(nav_size, parent_x, 0, 0);
	mvwprintw(nav_window, 1, 1, "Navigation bar");
	draw_borders(nav_window);
	wrefresh(nav_window);
}