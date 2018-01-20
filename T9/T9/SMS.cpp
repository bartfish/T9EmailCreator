#include "SMS.h"

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
