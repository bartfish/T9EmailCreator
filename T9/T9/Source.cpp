#include "Trie.h"
#include <list>
#include <stdexcept>

// TODO: IMPLEMENT SEARCHING FOR ALL WORDS - NOT ONLY FOR THE FIRST ONE
// SOLUTION: LIST

class error_m : public exception {

	string theFile;
	int theLine;
	exception theEx;

public:
	error_m(const std::string& file, int line, exception &ex)
	{
		theFile = file;
		theLine = line;
		theEx = ex;
	}

	virtual const char * what() const throw()
	{
		string ss;
		ss = "File: " + theFile + " Line: " + to_string(theLine) + " Error: " + theEx.what();

		char *y = new char[ss.length() + 1];
		strcpy(y, ss.c_str());

		return y;
	}
};
class my_exception : public exception
{
	string theFile;
	int theLine;
	exception theEx;

public:
	my_exception()
	{
	}
	virtual const char * what() const throw()
	{
		return "Custom exception";
	}
};



// implement class which will represemt the list of contacts

// implement classes of Email and sms, that inherit from Message class
class Message
{
	protected:
		string recipient_info;
		string message;
	public: 
		Message() : recipient_info(""), message("") {};
		~Message() {};
		
		virtual bool is_valid_recepient_info(const string &s);

		virtual void assign_recipient(const string &s);
		virtual void assign_message_content(const string &s);

};

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
};

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
		} else if (email[i] == '.')
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





// for the SMS validate the contact number 
// maximum number of signs is 256

class SMS : public Message
{
private:
	Trie Phones;
	enum SMS_TYPE : unsigned int
	{
		SMS_TEXT = 1,
		SMS_IMG = 2
	};


public:
	SMS() : Phones("") {}
	~SMS() {}
	
	bool is_valid_recepient_info(const string &s);

	void assign_recipient(const string &s);
	void assign_message_content(const string &s);
};

void SMS::assign_recipient(const string &s)
{
	// VALIDATE FIRST
	recipient_info = s;
}
void SMS::assign_message_content(const string &s)
{
	message = s;
}

int main()
{

	Trie Emails("");
	Trie T("");

	ifstream file("words.txt");
	ifstream emails("emails.txt");
	string s;

	int n = 0;
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	while (getline(file, s))
	{
		n++;
		T.insert(s);
		transform(s.begin(), s.end(), s.begin(), ::tolower);
	}

	n = 0;
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	while (getline(emails, s))
	{
		n++;
		Emails.insert(s);
		transform(s.begin(), s.end(), s.begin(), ::tolower);
	}

	vector<string> r = Emails.load_all_words("b");
	for (vector<string>::iterator it = r.begin(); it != r.end(); it++) {
		cout << *it << "\n";
	}

	

	string word = "";
	string text  = "";
	string str = "";
	
	char c;
	while (1)
	{
		str = "start \"Help\" cmd /C \"echo off &";
		c = _getch();
			if (c == ' ')
			{
				if (text != "")
				{
					text += " ";
				}
				text += word;
				word = "";

				system("cls");

				cout << text << "\n";

				continue;
			}
			else if (c == 8)
			{
				if (word.length() > 0)
				{
					word.pop_back();
				}
				else {
					word = "";
				}
			} else {
				word += c;
			}
			system("cls");
			cout << text << " " << word;

			vector<string> r = T.load_all_words(word);
			for (vector<string>::iterator it = r.begin(); it != r.end(); it++) {
				
				cout.width(60);
				cout << right << *it << endl;
				str += " echo ";
				str += *it;
				str += " & ";

			}
			str += " pause \"";
			const char * c_s = str.c_str();
			// option for showing characters on separate cmds
			//system(c_s);
			//system("start \"Help\" cmd /C \"echo off & echo Help text 1 & echo Help text 2 & echo Help text 3 & pause\"");
			if (c == 27)
			{
				break;
			}
		
	}
		
		
	//system("start \"Help\" cmd /C \"echo off & echo Help text 1 & echo Help text 2 & echo Help text 3 & pause\"");


	system("pause");
	return 0;
}