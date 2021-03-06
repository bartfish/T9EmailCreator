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
	string topic, message;
public:

	Message() : Vocabulary(""), recipient_info(""), topic(""), message("") {};
	~Message() {};

	virtual bool is_valid_recepient_info(const string &s) { return true; }

	virtual void set_recipient(const string &s) = 0;
	virtual void set_topic(const string &s) = 0;
	virtual void set_message_content(const string &s) = 0;

	virtual string assign_message_content() = 0;

	virtual bool load_contacts() { return false; }
	virtual void inputting_contact_info() {}
	virtual vector<string> load_all_words_from_contacts(const string & s) 
	{
		return Vocabulary.load_all_words("a");
	}
	virtual void create_message(myConsoleManager Con) {}

	void load_vocabulary();
	vector<string> load_all_words_from_voc(const string & s);

	// helper functions created for the purpose of validating email address
	bool is_character(const char & c) {
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
	}
	bool is_number(const char & c) {
		return (c >= '0' && c <= '9');
	}

	template<class Tobj>
	void save_message(Tobj o)
	{
		//cout << typeid(o).name() << endl;
		string id_name = typeid(o).name();
		string file_name_for_saving = "";
		Message *M = nullptr;
		if (id_name == "class Email") 
		{
			file_name_for_saving = "new_email.txt";
			M = &o;
		}
		else if (id_name == "class SMS")
		{
			file_name_for_saving = "new_sms.txt";
			M = &o;
		}
		else {
			file_name_for_saving = "new_message.txt";
			M = &o;
		}

		// create message string 
		string message_to_save = M->assign_message_content();

		// save message implementation
		fstream file;
		file.open(file_name_for_saving, ios::out);
		file << message_to_save;
		file.close();

		system("cls");
		cout << "New message was saved. Press enter to continue..." << endl;
		system("pause");
		
	}
};

