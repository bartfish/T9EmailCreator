#include "libraries.h"
#include "myConsoleManager.h"

void myConsoleManager::generate_windows()
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
	
																													 // number of windows must be equal to number of titles
	vector<WINDOW*> wins = { title_window, contact_window, topic_window, message_window, vocabulary_window };
	vector<string> wins_titles = { "TypeOfMessageTitle", "Contact", "Topic", "Message", "Vocabulary" };
	//this->load_main_console(wins, wins_titles);

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