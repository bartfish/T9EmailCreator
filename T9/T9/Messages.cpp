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


void Email::inputting_contact_info()
{

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