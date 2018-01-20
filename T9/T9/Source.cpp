#include "Trie.h"
#include "Messages.h"
#include <list>
#include <stdexcept>

int main()
{
	// choose between Email and sms
	myConsoleManager Cons;


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
	Cons.generate_windows();

	Email M;
	M.load_vocabulary("words.txt");
	M.load_contacts();
	M.assign_message_content("message");
	M.create_message(Cons);

	// load options
		// save message

	endwin();

	system("pause");
	return 0;
}