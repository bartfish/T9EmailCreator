#include "Messages.h"
#include "Email.h"
#include "SMS.h"
#include <list>
#include <stdexcept>

int main()
{

	Message *M = nullptr;
	myConsoleManager Cons;
	int c;
	bool is_trie_loaded;

	c = Cons.generate_navigation_bar();
	Cons.generate_message_windows();

	if (c == 49)
	{
		Email E;
		E.load_vocabulary();
		is_trie_loaded = E.load_contacts();
		if (is_trie_loaded)
		{
			E.create_message(Cons);
			M->save_message(E);
		} 

	} else if (c == 50) {

		SMS S;
		S.load_vocabulary();
		is_trie_loaded = S.load_contacts();
		if (is_trie_loaded)
		{
			S.create_message(Cons);
			M->save_message(S);
		}

	}

	cout << "Press enter to exit the program" << endl;
	
	Cons.close_windows();
	endwin();

	system("pause");
	return 0;
}