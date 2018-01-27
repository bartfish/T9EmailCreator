#include "Messages.h"


// for the SMS validate the contact number 
// maximum number of signs is 256

class SMS : public Message
{
private:
	Trie Contacts;
	string invalid_number_message, topic;
	enum SMS_TYPE : unsigned int
	{
		SMS_TEXT = 1,
		SMS_IMG = 2
	};

public:
	SMS() : 
		Contacts(""),
		invalid_number_message("Please, enter valid phone number (9 digits).") {}
	~SMS() {}

	bool is_valid_recepient_info(const string &s);
	bool load_contacts();

	void set_recipient(const string &s);
	void set_topic(const string &s);
	void set_message_content(const string &s);

	string assign_message_content();
	vector<string> load_all_words_from_contacts(const string & s);
	void create_message(myConsoleManager Con);
};
