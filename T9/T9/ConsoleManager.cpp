#include "libraries.h"
#include "ConsoleManager.h"

ConsoleManager::ConsoleManager(int parent_x, int parent_y)
{
	
}

void ConsoleManager::draw_borders(WINDOW *screen)
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

void ConsoleManager::load_main_console(vector <WINDOW*> wins, vector<string> wins_titles)
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