#include "Messages.h"


// for the SMS validate the contact number 
// maximum number of signs is 256

class SMS : public Message
{
private:
	Trie Contacts;
	enum SMS_TYPE : unsigned int
	{
		SMS_TEXT = 1,
		SMS_IMG = 2
	};

public:
	SMS() : Contacts("") {}
	~SMS() {}

	bool is_valid_recepient_info(const string &s) { return true; }

	void assign_recipient(const string &s);
	void assign_message_content(const string &s);
	vector<string> load_all_words_from_contacts(const string & s);
	void create_message(myConsoleManager Con);
	//void save_message(); // save to "SMS" folder
};
