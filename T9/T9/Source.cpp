#include "Messages.h"
#include "Email.h"
#include "SMS.h"
#include <list>
#include <stdexcept>

int main()
{
	// load menu
	// defined windows needed for visual representation
	myConsoleManager Cons;
	while (1)
	{

		int c = Cons.generate_navigation_bar();
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