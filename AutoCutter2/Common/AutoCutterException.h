#pragma once
#include <iostream>
using namespace std;
class AutoCutterException : public std::exception
{
public:
	AutoCutterException(void);
	AutoCutterException(const string& pMessage);
	AutoCutterException(const char* pMessage);
	string& toString();
	~AutoCutterException(void);

	virtual const char* what() const throw() {
		return _message.c_str();
	}

private:
	string _message;
};

