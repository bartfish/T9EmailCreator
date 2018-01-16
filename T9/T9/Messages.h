#pragma once
#include "libraries.h"
#include "Trie.h"

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

	virtual void load_contacts(const string &s) {}


	void load_vocabulary(const string & filename);
	vector<string> load_all_words_from_voc(const string & s);
};


// for the email validate email format
// no limit for the number of signs
class Email : public Message
{
private:
	//Trie Emails;
	string topic;
	unsigned int priority_type;
	enum Priority : unsigned int
	{
		HIGH = 1,
		NORMAL = 2,
		LOW = 3
	};


public:
	Email() : topic("Not set"), priority_type(NORMAL) {}
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






// for the SMS validate the contact number 
// maximum number of signs is 256

class SMS : public Message
{
private:
	//Trie Phones;
	enum SMS_TYPE : unsigned int
	{
		SMS_TEXT = 1,
		SMS_IMG = 2
	};


public:
	SMS() {}
	~SMS() {}

	bool is_valid_recepient_info(const string &s) { return true;  }

	void assign_recipient(const string &s);
	void assign_message_content(const string &s);
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

