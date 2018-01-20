#include "include\curses.h"

class ConsoleManager
{

private:
	int x, y, i;
	// windows here
public:
	ConsoleManager() {};
	ConsoleManager(int parent_x, int parent_y);
	~ConsoleManager() {};

	void draw_borders(WINDOW *screen);
	void load_main_console(vector <WINDOW*> wins, vector<string> wins_titles);

};
