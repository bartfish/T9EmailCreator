#include "Messages.h"
#include "Email.h"
#include "SMS.h"
#include <list>
#include <stdexcept>

int main()
{
	while (1)
	{
		// load menu
		cout << "/////// EMAIL & SMS CREATOR //////" << endl;
		cout << "Choose: " << endl;
		cout << "1 to create an email" << endl;
		cout << "2 to create a SMS" << endl;

		cout << endl << "Your choice: (enter number and the program will continue)";
		char choice = _getch();

		int c;
		switch (choice)
		{
			case '1':
				c = 1;
				break;
			case '2':
				c = 2;
				break;
			case '0':
				return 0;
				break;
		}

		// defined windows needed for visual representation
		myConsoleManager Cons;
		Cons.generate_message_windows();

		if (c == 1)
		{
			Email M;
			M.load_vocabulary("words.txt");
			M.load_contacts();
			M.create_message(Cons);

		} else {

			SMS S;
			S.load_vocabulary("words.txt");
			S.load_contacts();
			S.create_message(Cons);

		}
	}

	endwin();

	system("pause");
	return 0;
}