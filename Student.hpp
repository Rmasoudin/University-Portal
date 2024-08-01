#ifndef STUDENT
#define STUDENT
#include "Course.hpp"
#include "Major.hpp"
#include "User.hpp"
#define SPACE " "
#define COMMA ","
#define COLON ":"
#define LINE "-"
#define SLASH "/"
#include "Exception.hpp"
#include <vector>

string find_major(vector<Major *> majors, int id);

class Student : public User {
public:
  Student(vector<string> info);
  int get_semester();
  void take_course(Course_Presentation *course);
  vector<Course_Presentation *> get_taken_courses();
  void show_personal_page(vector<Major *> majors);
  void show_specific_page(vector<Major *> majors, int post_id_);
  string get_courses();
  void get_my_course();
  void delete_course(int course_id);

private:
  int semester;
  vector<Course_Presentation *> taken_courses;
};

#endif