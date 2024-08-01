#ifndef _PROF_
#define _PROF_
#include "Student.hpp"
#include <vector>

class Prof : public User {
public:
  Prof(vector<string> info);
  string get_pos();
  void show_personal_page(vector<Major *> majors,
                          vector<Course_Presentation *> availble_courses);
  string get_courses(vector<Course_Presentation *> availble_courses);
  void show_specific_page(vector<Major *> majors,
                          vector<Course_Presentation *> availble_courses,
                          int post_id_);

private:
  string pos;
};

#endif
