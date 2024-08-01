#include "App_Handler.hpp"
#include "Data_Reader.hpp"
#include "Exception.hpp"
#include "Split.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#define SPACE_DELIMITER " "
#define ID_DELIMITER "id"
#define PASS_DELIMITER "password"
const char QUOT_DELIMITER = '\"';
#define NATURAL_NUMBER_DELIMITER 0
#define NOT_FOUND -1
using namespace std;

bool is_natural_number(int num) {
  if (num < NATURAL_NUMBER_DELIMITER)
    return false;
  return true;
}

void App_Handler::set_info(route *file_path[]) {
  Data_Reader temp_reader;
  core = temp_reader.set_info(file_path);
}

App_Handler::App_Handler(route *file_path[]) { set_info(file_path); }

void App_Handler::run() {
  string command;
  while (getline(cin, command)) {
    try {
      control_input(command);
    } catch (Exception ex) {
      cerr << ex.show_message() << endl;
    }
  }
}

void App_Handler::control_input(string command) {
  int pos = command.find(SPACE);
  string type = command.substr(0, pos);
  if (pos == -1)
    throw WrongRequest_EX();
  if (type == POST) {
    post(command.substr(pos + 1));
  } else if (type == GET) {
    get_(command.substr(pos + 1));
  } else if (type == PUT)
    put(command.substr(pos + 1));
  else if (type == DELETE)
    delete_(command.substr(pos + 1));
  else {
    throw WrongRequest_EX();
  }
}

void App_Handler::post(string command) {
  int id;
  string pass;
  int pos1 = command.find(SPACE);
  string type = command.substr(0, pos1);
  vector<string> splited = split(command, SPACE_DELIMITER);
  if (type == LOGIN) {
    if (splited.size() != 6)
      throw WrongRequest_EX();
    auto id_pos = find(splited.begin(), splited.end(), ID_DELIMITER);
    int id_index = distance(splited.begin(), id_pos);
    auto pass_pos = find(splited.begin(), splited.end(), PASS_DELIMITER);
    int pass_index = distance(splited.begin(), pass_pos);
    id = stoi(splited[id_index + 1]);
    pass = splited[pass_index + 1];
    if (id == UT_ACOOUNT_ID && pass == UT_ACOOUNT_PASS) {
      ut_account = new Ut_Account;
      cout << SUCCESS_MESSAGE << endl;
    } else if (ut_account != nullptr || user != nullptr)
      throw Access_EX();
    else
      login(id, pass);
  } else if (type == POST_ON_PAGE &&
             (user != nullptr || ut_account != nullptr)) {
    post_on_page(command);
  } else if (type == CONNECT && user != nullptr)
    connect(splited);
  else if (type == COURSE_OFFER && ut_account != nullptr) {
    add_course(command);
  } else if (user == nullptr && ut_account == nullptr &&
             (type == POST_ON_PAGE || type == CONNECT ||
              type == COURSE_OFFER)) {
    throw Access_EX();
  } else if (type == LOGOUT) {
    if (user == nullptr && ut_account == nullptr)
      throw Access_EX();
    logout();
  } else
    throw Undefined_EX();
}

void App_Handler::login(int id, string pass) {
  string check = core->check_login(id, pass);
  if (user != nullptr)
    throw Access_EX();
  if (check == STUDENT_SUCCESS || check == PROF_SUCCESS) {
    cout << SUCCESS_MESSAGE << endl;
    user = new Token(id, pass);
  } else if (check == ILLEGAL_REQUEST_MESSAGE)
    throw Access_EX();
  else if (check == UNDEFINED_MESSAGE)
    throw Undefined_EX();
}

void App_Handler::logout() {
  if (ut_account != nullptr) {
    saved_hub = ut_account->get_hub();
    delete ut_account;
    cout << SUCCESS_MESSAGE << endl;
    ut_account = nullptr;
    return;
  }
  if (user == nullptr)
    throw Access_EX();
  if (user != nullptr) {
    delete user;
    cout << SUCCESS_MESSAGE << endl;
    user = nullptr;
  }
}

vector<string> extract_post_info(string command) {
  vector<string> stored_info;
  size_t pos1 = command.find(QUOT_DELIMITER);
  size_t pos2 = command.find(QUOT_DELIMITER, pos1 + 1);
  size_t pos3 = command.find(QUOT_DELIMITER, pos2 + 1);
  string title = command.substr(pos1, pos2 - pos1 + 1);
  stored_info.push_back(title);
  string message = command.substr(pos3);
  stored_info.push_back(message);
  return stored_info;
}

void App_Handler::post_on_page(string command) {
  vector<string> splited = extract_post_info(command);
  string title = splited[0];
  string message = splited[1];
  if (title == message)
    throw WrongRequest_EX();
  if (user != nullptr)
    core->post(title, message, user->get_id());
  if (ut_account != nullptr) {
    Post *temp_post = new Post(title, message);
    ut_account->add_post(temp_post);
  }
  cout << SUCCESS_MESSAGE << endl;
  if (user == nullptr) {
    core->add_all_notif(0, NEW_POST);
    return;
  }
  core->add_notif(user->get_id(), NEW_POST);
}

void App_Handler::connect(vector<string> command) {
  int id = stoi(command[3]);
  if (!is_natural_number(id))
    throw WrongRequest_EX();
  if (core->check_connection(user->get_id(), id) == WRONG_REQUEST_MESSAGE)
    throw WrongRequest_EX();
  if (core->check_connection(user->get_id(), id) == UNDEFINED_MESSAGE)
    throw Undefined_EX();
  core->connect(user->get_id(), id);
  cout << SUCCESS_MESSAGE << endl;
}

void App_Handler::get_(string command) {
  int pos1 = command.find(SPACE);
  string type = command.substr(0, pos1);
  vector<string> splited = split(command, SPACE_DELIMITER);
  if (type == COURSES_DELIMITER && splited.size() == ALL_COURSES_DELIMITER) {
    core->get_courses();
  } else if (type == COURSES_DELIMITER &&
             splited.size() != ALL_COURSES_DELIMITER) {
    int id = stoi(splited[3]);
    if (!is_natural_number(id))
      throw WrongRequest_EX();
    if (!core->check_course_availabilty(id))
      throw Undefined_EX();
    core->get_specific_course(id);
  } else if (type == PERSONAL_PAGE) {
    int id = stoi(splited[3]);
    if (id == 0) {
      cout << UT_ACOOUNT_PASS << endl;
      saved_hub->show_posts();
      return;
    }
    if (!is_natural_number(id))
      throw WrongRequest_EX();
    if (!core->show_personal_page(id))
      throw Undefined_EX();
  } else if (type == POST_ON_PAGE) {
    int id = stoi(splited[3]);
    int post_id = stoi(splited[5]);
    if (id == 0) {
      cout << UT_ACOOUNT_PASS << endl;
      saved_hub->find_post(post_id);
      return;
    }
    if (!is_natural_number(id))
      throw WrongRequest_EX();
    if (!is_natural_number(post_id))
      throw WrongRequest_EX();
    if (!core->get_specific_post(id, post_id))
      throw Undefined_EX();
  } else if (type == MY_COURSE)
    core->get_my_course(user->get_id());
  else if (type == NOTIFICATION) {
    core->get_notif(user->get_id());
  } else
    throw Undefined_EX();
}

void App_Handler::add_course(string command) {
  if (ut_account == nullptr)
    throw Undefined_EX();
  vector<string> splited = split(command, SPACE_DELIMITER);
  int course_id = stoi(splited[3]);
  int prof_id = stoi(splited[5]);
  int capacity = stoi(splited[7]);
  string time = splited[9];
  string exam_date = splited[11];
  int class_num = stoi(splited[13]);
  if (!is_natural_number(course_id))
    throw WrongRequest_EX();
  if (!is_natural_number(prof_id))
    throw WrongRequest_EX();
  if (!is_natural_number(capacity))
    throw WrongRequest_EX();
  if (!is_natural_number(class_num))
    throw WrongRequest_EX();
  if (!core->check_course_availabilty(course_id)) {
    throw Undefined_EX();
  }
  if (core->check_prof_availabilty(prof_id, course_id) == UNDEFINED_MESSAGE) {
    throw Undefined_EX();
  }
  if (core->check_prof_availabilty(prof_id, course_id) ==
      ILLEGAL_REQUEST_MESSAGE)
    throw Access_EX();
  if (!core->check_prof_time(prof_id, time))
    throw Access_EX();
  Course *wanted_course = core->find_course(course_id);
  core->present_course(course_id, prof_id, capacity, time, exam_date, class_num,
                       wanted_course);
  cout << SUCCESS_MESSAGE << endl;
  core->add_all_notif(prof_id, NEW_COURSE_OFFERING);
}

void App_Handler::delete_(string command) {
  int pos1 = command.find(SPACE);
  string type = command.substr(0, pos1);
  vector<string> splited = split(command, SPACE_DELIMITER);
  int id = stoi(splited[3]);
  if (!is_natural_number(id))
    throw WrongRequest_EX();
  if (type == POST_ON_PAGE) {
    core->delete_post(id, user->get_id());
  }
  if (type == MY_COURSE) {
    core->delete_course(id, user->get_id());
    core->add_notif(user->get_id(), DELETE_COURSE);
  }
  cout << SUCCESS_MESSAGE << endl;
}

void App_Handler::put(string command) {
  vector<string> splited = split(command, SPACE_DELIMITER);
  int course_id = stoi(splited[3]);
  if (!is_natural_number(course_id)) {
    throw WrongRequest_EX();
  }
  if (!core->check_course_availabilty(course_id)) {
    throw Undefined_EX();
  }
  if (!core->check_course_pre_req(course_id, user->get_id())) {
    throw Access_EX();
  }
  if (!core->check_course_time(course_id, user->get_id())) {
    throw Access_EX();
  }
  if (!core->check_course_major(course_id, user->get_id())) {
    throw Access_EX();
  }
  core->take_course(course_id, user->get_id());
  cout << SUCCESS_MESSAGE << endl;
  core->add_notif(user->get_id(), GET_COURSE);
}

Token::Token(int i, string p) { set_info(i, p); }

void Token::set_info(int i, string p) {
  id = i;
  password = p;
}

int Token::get_id() { return id; }

string Token::get_pass() { return password; }
