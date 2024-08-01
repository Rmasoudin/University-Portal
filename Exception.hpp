#ifndef _EX_
#define _EX_
#include <string>
using namespace std;

#define SUCCESS_MESSAGE "OK"
#define EMPTY_MESSAGE "Empty"
#define UNDEFINED_MESSAGE "Not Found"
#define WRONG_REQUEST_MESSAGE "Bad Request"
#define ILLEGAL_REQUEST_MESSAGE "Permission Denied"
#define STUDENT_SUCCESS "Student found"
#define PROF_SUCCESS "Prof found"
class Exception {
public:
  Exception(string _message);
  string show_message();

protected:
  string message;
  void set_info(string _message);
};

class Empty_EX : public Exception {
public:
  Empty_EX();
};

class Undefined_EX : public Exception {
public:
  Undefined_EX();
};

class WrongRequest_EX : public Exception {
public:
  WrongRequest_EX();
};

class Access_EX : public Exception {
public:
  Access_EX();
};

#endif