#pragma once
#include "libraries.h"
#include "Trie.h"
#include "myConsoleManager.h"

// implement classes of Email and sms, that inherit from Message class
class Message
{
protected:
	Trie Vocabulary; // public because the vocabulary is commonly used
	string recipient_info;
	string message;
public:

	Message() : Vocabulary(""), recipient_info(""), message("") {};
	~Message() {};

	virtual bool is_valid_recepient_info(const string &s) { return true;  }
	
	virtual void assign_recipient(const string &s) {}
	virtual void assign_message_content(const string &s) {}

	virtual void load_contacts() {}
	virtual void inputting_contact_info() {}
	virtual vector<string> load_all_words_from_contacts(const string & s) 
	{
		return Vocabulary.load_all_words("a");
	}
	virtual void create_message(myConsoleManager Con) {}
	//virtual void save_message() {}

	void load_vocabulary(const string & filename);
	vector<string> load_all_words_from_voc(const string & s);

	// helper functions created for the purpose of validating email address
	bool is_character(const char & c) {
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
	}
	bool is_number(const char & c) {
		return (c >= '0' && c <= '9');
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

template<class object_type>
class PromptManager
{
	private:
		string EmailTitle, SMSTitle;
	public:
		PromptManager() : EmailTitle(""), SMSTitle("") {}
		~PromptManager() {}

		void setMessageTitle(object_type obj)
		{

			if (typeof(obj) == Email)
			{
				EmailTitle = "Creating Email";
			}
			else if (typeof(obj) == SMS)
			{
				SMSTitle = "Creating SMS";
			}
		}
		string getMessageTitle(object_type obj)
		{

			if (typeof(obj) == Email)
			{
				return EmailTitle;
			}
			else if (typeof(obj) == SMS)
			{
				return SMSTitle;
			}
		}
};


