#include "include\curses.h"

class myConsoleManager
{

	private:
		int x, y, i;

		// windows variables here
		WINDOW * title_window, *contact_window, *topic_window, *message_window, *vocabulary_window;
		int parent_x, parent_y,
			title_size, // contact loader 
			contact_size, // contact loader 
			topic_size, // topic loader 
			message_size, // message loader
			vocabulary_size; // vocabulary loader

public:
	myConsoleManager() {
		
		parent_x = 1000, 
		parent_y = 500, 
		title_size = 3, // contact loader 
		contact_size = 6, // contact loader 
		topic_size = 6, // topic loader 
		message_size = 15, // message loader
		vocabulary_size = 10; // vocabulary loader

	}
	~myConsoleManager() {};

	void generate_message_windows();
	void draw_borders(WINDOW *screen);
	void load_main_console(vector <WINDOW*> wins, vector<string> wins_titles);

	inline WINDOW * get_title_window() { return title_window; }
	inline WINDOW * get_contact_window() { return contact_window; }
	inline WINDOW * get_topic_window() { return topic_window; }
	inline WINDOW * get_message_window() { return message_window; }
	inline WINDOW * get_vocabulary_window() { return vocabulary_window; }

	inline int get_parent_x() { return parent_x; }
	inline int get_parent_y() { return parent_y; }
};
