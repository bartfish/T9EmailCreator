#include "Messages.h"
#include "Email.h"
#include "SMS.h"
#include <list>
#include <stdexcept>

int main()
{
	// choose between Email and sms
/*	Email *E = new Email();
	SMS *S = new SMS();
	Message *Mess = new Message();
	// load menu
	cout << "/////// EMAIL & SMS CREATOR //////" << endl;
	cout << "Choose: " << endl; 
	cout << "1 to create an email" << endl;
	cout << "2 to create a SMS" << endl;

	cout << endl << "Your choice: (enter number and the program will continue)";
	char choice = _getch();
	
	switch (choice)
	{
	case 1:
		Mess = dynamic_cast<Email*>(E);
		break;
	case 2:
		Mess = dynamic_cast<SMS*>(S);
		break;
	}
	cout << typeid(Mess).name() << endl;
	system("pause");
	*/
	// defined windows needed for visual representation
	myConsoleManager Cons;
	Cons.generate_message_windows();
	
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