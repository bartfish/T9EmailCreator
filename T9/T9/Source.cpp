#include "Messages.h"
#include "Email.h"
#include "SMS.h"
#include <list>
#include <stdexcept>

int main()
{
	// load menu
	// defined windows needed for visual representation
	Message *M = nullptr;
	myConsoleManager Cons;

	while (1)
	{

		int c = Cons.generate_navigation_bar();
		Cons.generate_message_windows();

		if (c == 49)
		{
			Email E;
			E.load_vocabulary("words.txt");
			E.load_contacts();
			E.create_message(Cons);
			M->save_message(E);

		} else if (c == 50) {

			SMS S;
			S.load_vocabulary("words.txt");
			S.load_contacts();
			S.create_message(Cons);
			M->save_message(S);

		}
		else if (c == 48)
		{
			break;
		}
	}
	
	Cons.close_windows();
	endwin();

	system("pause");
	return 0;
}