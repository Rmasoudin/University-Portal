#include "Prof.hpp"
#include <iostream>

Prof::Prof(vector<string> info)
    : User(info[1], stoi(info[0]), stoi(info[2]), info[4]) {
  string pos = info[3];
}

string Prof::get_pos() { return pos; }

string Prof::get_courses(vector<Course_Presentation *> availble_courses) {
  string all_courses;
  for (auto c : availble_courses) {
    all_courses.append(c->get_course()->get_name());
    all_courses.append(COMMA);
  }
  return all_courses.substr(0, all_courses.size() - 1);
}

void Prof::show_personal_page(vector<Major *> majors,
                              vector<Course_Presentation *> availble_courses) {
  cout << name << SPACE << find_major(majors, major_id) << SPACE << pos << SPACE
       << get_courses(availble_courses) << endl;
  show_posts();
}

void Prof::show_specific_page(vector<Major *> majors,
                              vector<Course_Presentation *> availble_courses,
                              int post_id_) {
  cout << name << SPACE << find_major(majors, major_id) << SPACE << pos << SPACE
       << get_courses(availble_courses) << endl;
  find_post(post_id_);
}
