#include "Messages.h"

void Message::load_vocabulary(const string & file_name)
{
	string s;
	ifstream words_file(file_name);

	int n = 0;
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	while (getline(words_file, s))
	{
		n++;
		Vocabulary.insert(s);
		transform(s.begin(), s.end(), s.begin(), ::tolower);
	}
}
vector<string> Message::load_all_words_from_voc(const string & s)
{
	return Vocabulary.load_all_words(s);
}





bool Email::is_valid_recepient_info(const string &email)
{
	// Validate email
	if (email.empty())
	{
		return false;
	}

	if (!is_character(email[0]))
	{
		return false;
	}

	bool is_at = false;
	bool is_dot = false;

	unsigned int email_length = email.length();
	for (unsigned int i = 0; i < email_length; i++)
	{
		if (email[i] == '@')
		{
			is_at = true;
		}
		else if (email[i] == '.')
		{
			is_dot = true;
		}
	}
	if ((!is_at || !is_dot))
	{
		false;
	}
	return true;
}

void Email::assign_recipient(const string &s)
{
	// Validate email
	bool is_valid_email_address = is_valid_recepient_info(s);
	try
	{
		if (is_valid_email_address)
		{
			recipient_info = s;
		}
		throw error_m(__FILE__, __LINE__, my_exception());
	}
	catch (exception & e)
	{
		cout << e.what() << endl;
	}
}
void Email::assign_message_content(const string &s)
{
	message = s;
}
void Email::load_contacts()
{
	string s;
	ifstream words_file("emails.txt");

	int n = 0;
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	while (getline(words_file, s))
	{
		n++;
		Emails.insert(s);
		transform(s.begin(), s.end(), s.begin(), ::tolower);
	}
}
vector<string> Email::load_all_words_from_contacts(const string & s)
{
	return Emails.load_all_words(s);
}


void Email::create_message(myConsoleManager Con)
{

	// call console method get_windowtype() and assign windows to the ones from here
	WINDOW *title_window = Con.get_title_window();
	WINDOW *contact_window = Con.get_contact_window();
	WINDOW *topic_window = Con.get_topic_window();
	WINDOW *message_window = Con.get_message_window();
	WINDOW *vocabulary_window = Con.get_vocabulary_window();

	string word = "";
	string text = "";
	string str = "";

	char c;
	int cursor_position_x = 1;
	werase(contact_window);
	Con.draw_borders(contact_window);

	while (1)
	{
		wrefresh(contact_window);
		c = mvwgetch(contact_window, 1, 1);

		if (c == ' ')
		{
			if (text != "")
			{
				text += " ";
			}
			text += word;
			word = "";

			mvwprintw(contact_window, 1, 1, text.c_str());
			cursor_position_x = text.length() + 2; // word end + space
			wrefresh(contact_window);

			continue;
		}
		else if (c == 8)
		{
			if (word.length() > 0)
			{
				word.pop_back();

				mvwprintw(contact_window, 1, cursor_position_x - 1, word.c_str());
				wrefresh(contact_window);
			}
			else {
				word = "";
			}
		}
		else {
			word += c;
		}

		mvwprintw(contact_window, 1, cursor_position_x, word.c_str());
		wrefresh(contact_window);

		str = "";
		vector<string> r = this->load_all_words_from_contacts(word);
		for (vector<string>::iterator it = r.begin(); it != r.end(); it++)
		{
			str += *it + ", ";
		}

		werase(vocabulary_window);
		wrefresh(vocabulary_window);

		Con.draw_borders(contact_window);
		Con.draw_borders(topic_window); // simulate the game loop 
		Con.draw_borders(message_window); // simulate the game loop 
		Con.draw_borders(vocabulary_window); // simulate the game loop 


		mvwprintw(vocabulary_window, 1, 1, str.c_str());
		wrefresh(vocabulary_window);

		if (c == 27 || c == 9)
		{
			break;
		}
	}

	word = "";
	text = "";
	str = "";
	cursor_position_x = 1;
	werase(topic_window);
	Con.draw_borders(topic_window);

	while (1)
	{
		wrefresh(topic_window);
		c = mvwgetch(topic_window, 1, 1);

		if (c == ' ')
		{
			if (text != "")
			{
				text += " ";
			}
			text += word;
			word = "";

			mvwprintw(topic_window, 1, 1, text.c_str());
			cursor_position_x = text.length() + 2; // word end + space
			wrefresh(topic_window);

			continue;
		}
		else if (c == 8)
		{
			if (word.length() > 0)
			{
				word.pop_back();

				mvwprintw(topic_window, 1, cursor_position_x - 1, word.c_str());
				wrefresh(topic_window);
			}
			else {
				word = "";
			}
		}
		else {
			word += c;
		}

		mvwprintw(topic_window, 1, cursor_position_x, word.c_str());
		wrefresh(topic_window);

		str = "";
		vector<string> r = this->load_all_words_from_voc(word);
		for (vector<string>::iterator it = r.begin(); it != r.end(); it++)
		{
			str += *it + ", ";
		}

		werase(vocabulary_window);
		wrefresh(vocabulary_window);

		Con.draw_borders(contact_window);
		Con.draw_borders(topic_window); // simulate the game loop 
		Con.draw_borders(message_window); // simulate the game loop 
		Con.draw_borders(vocabulary_window); // simulate the game loop 

		mvwprintw(vocabulary_window, 1, 1, str.c_str());
		wrefresh(vocabulary_window);

		if (c == 27 || c == 9)
		{
			break;
		}
	}

	word = "";
	text = "";
	str = "";
	cursor_position_x = 1;
	werase(message_window);
	Con.draw_borders(message_window);

	while (1)
	{
		wrefresh(message_window);
		c = mvwgetch(message_window, 1, 1);

		if (c == ' ')
		{
			if (text != "")
			{
				text += " ";
			}
			text += word;
			word = "";

			mvwprintw(message_window, 1, 1, text.c_str());
			cursor_position_x = text.length() + 2; // word end + space
			wrefresh(message_window);

			continue;
		}
		else if (c == 8)
		{
			if (word.length() > 0)
			{
				word.pop_back();

				mvwprintw(message_window, 1, cursor_position_x - 1, word.c_str());
				wrefresh(message_window);
			}
			else {
				word = "";
			}
		}
		else {
			word += c;
		}

		mvwprintw(message_window, 1, cursor_position_x, word.c_str());
		wrefresh(message_window);

		str = "";
		vector<string> r = this->load_all_words_from_voc(word);
		for (vector<string>::iterator it = r.begin(); it != r.end(); it++)
		{
			str += *it + ", ";
		}

		werase(vocabulary_window);
		wrefresh(vocabulary_window);

		Con.draw_borders(contact_window);
		Con.draw_borders(topic_window); // simulate the game loop 
		Con.draw_borders(message_window); // simulate the game loop 
		Con.draw_borders(vocabulary_window); // simulate the game loop 

		mvwprintw(vocabulary_window, 1, 1, str.c_str());
		wrefresh(vocabulary_window);

		if (c == 27 || c == 9)
		{
			break;
		}
	}

	delwin(contact_window);
	delwin(topic_window);
	delwin(message_window);
	delwin(vocabulary_window);
}




void SMS::assign_recipient(const string &s)
{
	// VALIDATE FIRST
	recipient_info = s;
}
void SMS::assign_message_content(const string &s)
{
	message = s;
}
vector<string> SMS::load_all_words_from_contacts(const string & s)
{
	return Contacts.load_all_words(s);
}
