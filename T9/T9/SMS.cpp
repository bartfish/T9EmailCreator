#include "SMS.h"

void SMS::set_recipient(const string &s)
{
	recipient_info = s;
}
void SMS::set_topic(const string &s)
{
	topic = s;
}
void SMS::set_message_content(const string &s)
{
	message = s;
}
string SMS::assign_message_content()
{
	SMS *S = this;
	string message_s;
	message_s = "EMAIL MESSAGE \n";
	message_s += "To: " + S->recipient_info + "\n";
	message_s += "Topic: " + S->topic + "\n";
	message_s += "Message: " + S->message + "\n";

	return message_s;
}

vector<string> SMS::load_all_words_from_contacts(const string & s)
{
	return Contacts.load_all_words(s);
}

bool SMS::load_contacts()
{
	string s, filename = "phones.txt";
	ifstream words_file(filename);

	try {
		if (!words_file.good())
		{
			throw false;
		}
		throw true;
	}
	catch (bool e)
	{
		if (!e)
		{
			system("cls");
			cout << "Application was not able to open " << filename << endl;
			system("pause");
			return e;
		}
		else {

			int n = 0;
			transform(s.begin(), s.end(), s.begin(), ::tolower);
			while (getline(words_file, s))
			{
				n++;
				Contacts.insert(s);
				transform(s.begin(), s.end(), s.begin(), ::tolower);
			}

			return e;
		}

	}
}
bool SMS::is_valid_recepient_info(const string & phone_number) 
{ 
	// erase last 2 characters which are sign of tab '\t'
	string s = phone_number.substr(0, phone_number.size() - 2);

	if (s.empty() 
		|| s.length() != 9
		|| !(is_number(s[0]))) // assuming only Polish numbers
	{
		return false;
	}
	else {
		return true;
	}
}

// similar method to the Email implementation, however input data implemented differently
void SMS::create_message(myConsoleManager Con)
{
	// call console method get_windowtype() and assign windows to the ones from here
	WINDOW *title_window = Con.get_title_window();
	WINDOW *contact_window = Con.get_contact_window();
	WINDOW *topic_window = Con.get_topic_window();
	WINDOW *message_window = Con.get_message_window();
	WINDOW *vocabulary_window = Con.get_vocabulary_window();
	WINDOW *error_window = Con.get_error_window();

	// set necesary vars for creating messages
	char c;

	string word = "";
	string text = "";
	string str = "";

	bool can_exit_while = false;

	int cursor_position_x = 1;
	int cursor_position_y = 1;

	Con.clean_window_content(contact_window);
	while (1)
	{
		if (can_exit_while)
		{
			break;
		}

		wrefresh(contact_window);
		c = mvwgetch(contact_window, 1, 1);

		if (c == ' ') // disable spaces
		{
			if (text != "")
			{
				text += " ";
			}
			else {
				continue;
			}
		}
		else if (c == '\n')
		{
			continue;
		}
		else if (c == 8)
		{
			if (word.length() > 0)
			{
				Con.backspace_clicked(word, cursor_position_x, contact_window);
			}
			else {
				word = "";
			}
		}
		else if (c == 9)
			{
				// validate phone number inserted if is not found in the trie
				// if not valid do not break, show validation message and clear window
				bool is_valid_number = !(SMS::is_valid_recepient_info(word)); // negate output to get true

				try
				{
					if (is_valid_number)
					{
						recipient_info = word;
						throw true;
					}
					throw false;
				}
				catch (bool e)
				{
					if (e)
					{
						break;
					}
					else {
						word = "";
						werase(contact_window);
						werase(error_window);

						mvwprintw(error_window, 1, 1, invalid_number_message.c_str());

						Con.draw_borders(contact_window);
						Con.draw_borders(error_window);

						wrefresh(contact_window);
						wrefresh(error_window);
						continue;
					}
				}

			

		}
		else if (c == 27)
		{
			// ask if user is sure to exit
			werase(title_window);
			mvwprintw(title_window, 1, 1, "Press: y - to exit, n - to stay");
			Con.draw_borders(title_window);
			wrefresh(title_window);

			c = wgetch(title_window);
			if (c == 'y')
			{
				return;
			}
			else {
				// backup default title window
				Con.set_default_title_window();

				// continue editing
				continue;
			}
		}
		else {
			word += c;
		}

		Con.update_window_content(contact_window, word, 1, cursor_position_x);
		vector<string> r = this->load_all_words_from_contacts(word);
		str = Con.load_vocabulary_content(r);
		Con.update_window_content(vocabulary_window, str, 1, 1);

	}


	Con.reset_message_vars(word, text, str, can_exit_while, cursor_position_x, cursor_position_y);
	Con.clean_window_content(topic_window);
	while (1)
	{

		wrefresh(topic_window);
		c = mvwgetch(topic_window, 1, 1);

		if (can_exit_while)
		{
			break;
		}
		if (text != "")
		{
			werase(topic_window);
			Con.draw_borders(topic_window);

			mvwprintw(topic_window, 1, 1, text.c_str());
			cursor_position_x = text.length() + 2; // word end + space
			wrefresh(topic_window);
		}

		if (c == ' ')
		{/*
		 if (text != "")
		 {
		 text += " ";
		 }
		 text += word;
		 word = "";
		 */
			word = "";
			text += " ";

			werase(topic_window);
			Con.draw_borders(topic_window);
			mvwprintw(topic_window, 1, 1, text.c_str());
			cursor_position_x = text.length() + 2; // word end + space
			wrefresh(topic_window);

			continue;
		}
		else if (c == '\n')
		{
			continue;
		}
		else if (c == 8) // backspace implementaton for text
		{
			if (word.length() == 1)
			{
				word.pop_back();
				continue;
			}
			if (text.length() > 0)
			{
				Con.backspace_clicked(text, cursor_position_x, topic_window);


				if (text[text.length() - 1] == ' ') // backspacing space
				{
					text.pop_back();
					continue;
				}

				if (word.length() >= 1)
				{
					word.pop_back();
				}

				// take word without one element or the last word from text
				string search_word = "";

				if (word == "")
				{
					for (int i = 0; i<text.length(); ++i)
					{
						if (text[i] != ' ')
						{
							search_word += (char)text[i];
						}
						else {
							break;
						}
					}
				}
				else {
					search_word = word;
				}

				vector<string> r = this->load_all_words_from_voc(search_word);
				str = Con.load_vocabulary_content(r);
				Con.update_window_content(vocabulary_window, str, 1, 1);
				Con.draw_borders(topic_window);
			}
			continue;

		}
		else if (c == 9)
		{
			// assign inputted data to the message 
			(!empty(text)) ? this->set_topic(text) : this->set_topic(word);
			can_exit_while = true;
		}
		else if (c == 27)
		{
			// ask if user is sure to exit
			werase(title_window);
			mvwprintw(title_window, 1, 1, "Press: y - to exit, n - to stay");
			Con.draw_borders(title_window);
			wrefresh(title_window);

			c = wgetch(title_window);
			if (c == 'y')
			{
				return;
			}
			else {
				// backup default title window
				Con.set_default_title_window();

				// continue editing
				continue;
			}
		}
		word += c;
		text += c;

		Con.update_window_content(topic_window, text, 1, 1);
		vector<string> r = this->load_all_words_from_voc(word);
		str = Con.load_vocabulary_content(r);
		Con.update_window_content(vocabulary_window, str, 1, 1);
	}


	Con.reset_message_vars(word, text, str, can_exit_while, cursor_position_x, cursor_position_y);
	Con.clean_window_content(message_window);
	while (1)
	{

		wrefresh(message_window);
		c = mvwgetch(message_window, 1, 1);

		if (can_exit_while)
		{
			break;
		}
		if (text != "")
		{
			werase(message_window);
			Con.draw_borders(message_window);

			mvwprintw(message_window, 1, 1, text.c_str());
			cursor_position_x = text.length() + 2; // word end + space
			wrefresh(message_window);
		}
		if (c == ' ')
		{

			word = "";
			text += " ";

			werase(message_window);
			Con.draw_borders(message_window);
			mvwprintw(message_window, 1, 1, text.c_str());
			cursor_position_x = text.length() + 2; // word end + space
			wrefresh(message_window);

			continue;
		}
		else if (c == '\n')
		{
			continue;
		}
		else if (c == 8)
		{
			if (word.length() == 1)
			{
				word.pop_back();
				continue;
			}
			if (text.length() > 0)
			{
				Con.backspace_clicked(text, cursor_position_x, message_window);

				if (text[text.length() - 1] == ' ') // backspacing space
				{
					text.pop_back();
					continue;
				}

				if (word.length() >= 1)
				{
					word.pop_back();
				}

				// take word without one element or the last word from text
				string search_word = "";

				if (word == "")
				{
					for (int i = 0; i<text.length(); ++i)
					{
						if (text[i] != ' ')
						{
							search_word += (char)text[i];
						}
						else {
							break;
						}
					}
				}
				else {
					search_word = word;
				}

				vector<string> r = this->load_all_words_from_voc(search_word);
				str = Con.load_vocabulary_content(r);
				Con.update_window_content(vocabulary_window, str, 1, 1);
				Con.draw_borders(message_window);
			}
			continue;
		}
		else if (c == 9)
		{
			(!empty(text)) ? this->set_message_content(text) : this->set_message_content(word);
			can_exit_while = true;
		}
		else if (c == 27)
		{
			// ask if user is sure to exit
			werase(title_window);
			mvwprintw(title_window, 1, 1, "Press: y - to exit, n - to stay");
			Con.draw_borders(title_window);
			wrefresh(title_window);

			c = wgetch(title_window);
			if (c == 'y')
			{
				return;
			}
			else {
				// backup default title window
				Con.set_default_title_window();

				// continue editing
				continue;
			}
		}
		word += c;
		text += c;

		Con.update_window_content(message_window, text, 1, 1);
		vector<string> r = this->load_all_words_from_voc(word);
		str = Con.load_vocabulary_content(r);
		Con.update_window_content(vocabulary_window, str, 1, 1);


	}

}
