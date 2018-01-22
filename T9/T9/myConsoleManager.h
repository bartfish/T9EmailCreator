#include "include\curses.h"

class myConsoleManager
{

	private:
		int x, y, i;

		// windows variables here
		WINDOW * nav_window,
			*title_window,
			*contact_window,
			*topic_window,
			*message_window,
			*vocabulary_window,
			*error_window;

		int parent_x, parent_y,
			nav_size, // navigation bar loader
			title_size, // contact loader 
			contact_size, // contact loader 
			topic_size, // topic loader 
			message_size, // message loader
			vocabulary_size, // vocabulary loader
			error_size; // field for validation messages

		string navigation_bar_informations;

public:
	myConsoleManager() {
		
		parent_x = 200, 
		parent_y = 500, 
		nav_size = 5, // contact loader 
		title_size = 3, // contact loader 
		contact_size = 6, // contact loader 
		topic_size = 6, // topic loader 
		message_size = 15, // message loader
		vocabulary_size = 10; // vocabulary loader
		navigation_bar_informations = "Press: ESC - to quit,  TAB - to go to the next field, TAB(3 times) - to save";

	}
	~myConsoleManager() {};

	void generate_message_windows();
	void draw_borders(WINDOW *screen);
	void load_main_console(vector <WINDOW*> wins, vector<string> wins_titles);
	void close_windows();

	inline WINDOW * get_nav_window() { return nav_window; }
	inline WINDOW * get_title_window() { return title_window; }
	inline WINDOW * get_contact_window() { return contact_window; }
	inline WINDOW * get_topic_window() { return topic_window; }
	inline WINDOW * get_message_window() { return message_window; }
	inline WINDOW * get_vocabulary_window() { return vocabulary_window; }
	inline WINDOW * get_error_window() { return error_window; }

	inline int get_parent_x() { return parent_x; }
	inline int get_parent_y() { return parent_y; }

	void backspace_clicked(string &s, int cursor_position_x, WINDOW *the_window);
	void set_default_title_window();
	void clear_screen_from_message_windows();
	int generate_navigation_bar();
};
