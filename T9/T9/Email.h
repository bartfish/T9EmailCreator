#include "Messages.h"

// for the email validate email format
// no limit for the number of signs
class Email : public Message
{
	private:
		Trie Emails;
		string invalid_email_message;
		unsigned int priority_type;
		enum Priority : unsigned int
		{  
			HIGH = 1,
			NORMAL = 2,
			LOW = 3
		};


	public:
		Email() : 
			Emails(""),
			priority_type(NORMAL),
			invalid_email_message("Please, enter valid email address(e.x. example@example.com)") 
		{}
		~Email() {}

		bool is_valid_recepient_info(const string &s);

		void set_recipient(const string &s);
		void set_topic(const string &s);
		void set_message_content(const string &s);

		string assign_message_content();

		void inputting_contact_info() {};
		void load_contacts();
		vector<string> load_all_words_from_contacts(const string & s);
		void create_message(myConsoleManager Con);

};