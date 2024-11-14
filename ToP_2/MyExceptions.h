#pragma once
#include <exception>
#include <string>

class MyException : public std::exception
{
public:
	MyException(const std::string& message) : message{ message } {}
	const char* what() const noexcept {
		return message.c_str();
	}
private:
	std::string message;
};