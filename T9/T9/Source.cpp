
#include "Trie.h"
#include <allegro5\allegro.h> // for formatting console interface


int main()
{
	al_init();
	al_install_keyboard();
	al_install_mouse();
	ALLEGRO_DISPLAY *window = al_create_display(800, 800);
	al_set_window_title(window, "Email creator");
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_flip_display();



	if (!window)
	{
		throw exception();
	}

	Trie T("");

	ifstream file("words.txt");
	string s;

	int n = 0;
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	while (getline(file, s))
	{
		n++;
		T.insert(s);
		transform(s.begin(), s.end(), s.begin(), ::tolower);
	}

	vector<string> r = T.load_all_words("F");
	for (vector<string>::iterator it = r.begin(); it != r.end(); it++) {
		cout << *it << endl;
	}

	string word = "";
	char c;
	while (1)
	{
		c = _getch();
		word += c;
		cout << word << endl;

		vector<string> r = T.load_all_words(word);
		for (vector<string>::iterator it = r.begin(); it != r.end(); it++) {
			cout << *it << endl;
		}
		if (word == "exit")
		{
			break;
		}
	}

	al_destroy_display(window);


	system("pause");
	return 0;
}