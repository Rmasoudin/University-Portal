#ifndef _APP_HANDLER_
#define _APP_HANDLER_

#include "UTMS.hpp"
using namespace std;
#define PUT "PUT"
#define DELETE "DELETE"
#define POST "POST"
#define GET "GET"
#define LOGIN "login"
#define LOGOUT "logout"
#define POST_ON_PAGE "post"
#define CONNECT "connect"
#define COURSES_DELIMITER "courses"
#define MESSAGE_DELIMITER '"'
#define ALL_COURSES_DELIMITER 2
#define UT_ACOOUNT_PASS "UT_account"
#define UT_ACOOUNT_ID 0
#define COURSE_OFFER "course_offer"
#define PERSONAL_PAGE "personal_page"
#define MY_COURSE "my_courses"
#define NEW_POST "New Post"
#define GET_COURSE "Get Course"
#define DELETE_COURSE "Delete Course"
#define NEW_COURSE_OFFERING "New Course Offering"
#define NOTIFICATION "notification"
typedef const char route;

class App_Handler {
public:
  App_Handler(route *file_path[]);
  void run();

private:
  UTMS *core;
  Token *user = nullptr;
  Ut_Account *ut_account = nullptr;
  Hub *saved_hub = new Hub();
  void control_input(string command);
  void post(string command);
  void get_(string command);
  void put(string command);
  void delete_(string command);
  void login(int id, string pass);
  void logout();
  void post_on_page(string command);
  void connect(vector<string> command);
  void add_course(string command);
  void set_info(route *file_path[]);
};

#endif