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

vector<string> SMS::load_all_words_from_contacts(const string & s)
{
	return Contacts.load_all_words(s);
}

void SMS::load_contacts()
{
	string s;
	ifstream words_file("phones.txt");

	int n = 0;
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	while (getline(words_file, s))
	{
		n++;
		Contacts.insert(s);
		transform(s.begin(), s.end(), s.begin(), ::tolower);
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

	string word = "";
	string text = "";
	string str = "";

	char c;
	int cursor_position_x = 1;
	int cursor_position_y = 1;
	werase(contact_window);

	Con.draw_borders(title_window);
	Con.draw_borders(contact_window);
	Con.draw_borders(topic_window);
	Con.draw_borders(vocabulary_window);
	Con.draw_borders(error_window);

	while (1)
	{
		wrefresh(contact_window);
		c = mvwgetch(contact_window, 1, 1);

		if (c == ' ')
		{
			continue;
		}
		if (c == 8)
		{
			if (word.length() > 0)
			{
				Con.backspace_clicked(word, cursor_position_x, contact_window);
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
		Con.draw_borders(vocabulary_window);

		mvwprintw(vocabulary_window, 1, 1, str.c_str());
		wrefresh(vocabulary_window);

		if (c == 9)
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

		if (c == 27)
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
			// go to main navigation
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
				Con.backspace_clicked(text, cursor_position_x, topic_window);
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

		Con.draw_borders(topic_window);
		Con.draw_borders(vocabulary_window);

		mvwprintw(vocabulary_window, 1, 1, str.c_str());
		wrefresh(vocabulary_window);

		if (c == 9)
		{
			break;
		}
	}

	word = "";
	text = "";
	str = "";
	cursor_position_x = 1;
	cursor_position_y = 1;
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
		else if (c == '\n')
		{
			// include new line into message field
			cursor_position_y++;
			text += c;
			mvwprintw(message_window, cursor_position_y, 1, text.c_str());
			cursor_position_x = text.length() + 2; // word end + space
			wrefresh(message_window);
			continue;
		}
		else if (c == 8)
		{
			if (word.length() > 0)
			{
				Con.backspace_clicked(text, cursor_position_x, message_window);
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

		Con.draw_borders(message_window);
		Con.draw_borders(vocabulary_window);

		mvwprintw(vocabulary_window, 1, 1, str.c_str());
		wrefresh(vocabulary_window);

		if (c == 9)
		{
			break;
		}
	}

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