#include "Exception.hpp"

Exception::Exception(string _message) { set_info(_message); }

void Exception::set_info(string _message) { message = _message; }

string Exception::show_message() { return message; }

Empty_EX::Empty_EX() : Exception(EMPTY_MESSAGE) {}

Undefined_EX::Undefined_EX() : Exception(UNDEFINED_MESSAGE) {}

WrongRequest_EX::WrongRequest_EX() : Exception(WRONG_REQUEST_MESSAGE) {}

Access_EX::Access_EX() : Exception(ILLEGAL_REQUEST_MESSAGE) {}