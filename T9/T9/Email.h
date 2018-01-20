#include "Messages.h"

// for the email validate email format
// no limit for the number of signs
class Email : public Message
{
private:
	Trie Emails;
	string topic;
	unsigned int priority_type;
	enum Priority : unsigned int
	{
		HIGH = 1,
		NORMAL = 2,
		LOW = 3
	};


public:
	Email() : Emails(""), topic("Not set"), priority_type(NORMAL) {}
	~Email() {}

	bool is_valid_recepient_info(const string &s);

	void assign_recipient(const string &s);
	void assign_message_content(const string &s);

	// helper functions created for the purpose of validating email address
	bool is_character(const char & c) {
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
	}
	bool is_number(const char & c) {
		return (c >= '0' && c <= '9');
	}

	void inputting_contact_info() {};
	void load_contacts();
	vector<string> load_all_words_from_contacts(const string & s);
	void create_message(myConsoleManager Con);
	//void save_message(); // save to "Emails" folder

};