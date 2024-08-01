#include "Data_Reader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
const int START_OF_LINE = 0;
const char COMMA_DELIMITER = ',';
const char SEMI_COLON_DELIMITER = ';';

UTMS *Data_Reader::set_info(route *file_path[]) {
  route *student_path = file_path[2];
  vector<Student *> s = retrieve_student_info(student_path);

  route *prof_path = file_path[4];
  vector<Prof *> p = retrieve_prof_info(prof_path);

  route *major_path = file_path[1];
  vector<Major *> m = retrieve_major_info(major_path);

  route *course_path = file_path[3];
  vector<Course *> c = retrieve_course_info(course_path);

  UTMS *core = new UTMS(s, p, m, c);
  return core;
}

void discard_first_line(ifstream &file) {
  string usless_line;
  getline(file, usless_line);
}

ifstream file_open(route *file_path) {
  ifstream file;
  file.open(file_path);
  file.seekg(START_OF_LINE);
  discard_first_line(file);
  return file;
}

vector<Student *> Data_Reader::retrieve_student_info(route *student_path) {
  vector<Student *> students;
  string line;
  ifstream file = file_open(student_path);
  while (getline(file, line)) {
    vector<string> info;
    istringstream stream(line);
    string token;
    while (getline(stream, token, COMMA_DELIMITER)) {
      info.push_back(token);
    }
    Student *s = new Student(info);
    students.push_back(s);
  }
  file.close();
  return students;
}

vector<Prof *> Data_Reader::retrieve_prof_info(route *prof_path) {
  vector<Prof *> profs;
  string line;
  ifstream file = file_open(prof_path);
  while (getline(file, line)) {
    vector<string> info;
    istringstream stream(line);
    string token;
    while (getline(stream, token, COMMA_DELIMITER)) {
      info.push_back(token);
    }
    Prof *p = new Prof(info);
    profs.push_back(p);
  }
  file.close();
  return profs;
}

vector<Major *> Data_Reader::retrieve_major_info(route *major_path) {
  vector<Major *> majors;
  string line;
  ifstream file = file_open(major_path);
  while (getline(file, line)) {
    vector<string> info;
    istringstream stream(line);
    string token;
    while (getline(stream, token, COMMA_DELIMITER)) {
      info.push_back(token);
    }
    Major *ma = new Major(info);
    majors.push_back(ma);
  }
  file.close();
  return majors;
}

vector<Course *> Data_Reader::retrieve_course_info(route *major_path) {
  vector<Course *> courses;
  string line;
  ifstream file = file_open(major_path);
  while (getline(file, line)) {
    vector<string> info;
    istringstream stream(line);
    string token;
    while (getline(stream, token, COMMA_DELIMITER)) {
      info.push_back(token);
    }
    vector<int> allowed;
    string temp_allowed;
    string token_allowed;
    token_allowed = info[4];
    stringstream stream_allowed(token_allowed);
    while (getline(stream_allowed, temp_allowed, SEMI_COLON_DELIMITER)) {
      int int_allowed = stoi(temp_allowed);
      allowed.push_back(int_allowed);
    }
    Course *c = new Course(stoi(info[0]), info[1], stoi(info[2]), stoi(info[3]),
                           allowed);
    courses.push_back(c);
  }
  file.close();
  return courses;
}
