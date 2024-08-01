#include "Student.hpp"
#include <iostream>
using namespace std;

Student::Student(vector<string> info)
    : User(info[1], stoi(info[0]), stoi(info[2]), info[4]) {
  semester = stoi(info[3]);
}

int Student::get_semester() { return semester; }

void Student::take_course(Course_Presentation *course) {
  taken_courses.push_back(course);
}

vector<Course_Presentation *> Student::get_taken_courses() {
  return taken_courses;
}

string find_major(vector<Major *> majors, int id) {
  for (auto m : majors) {
    if (m->get_id() == id) {
      return m->get_name();
    }
  }
}

string Student::get_courses() {
  string all_courses;
  for (auto c : taken_courses) {
    all_courses.append(c->get_course()->get_name());
    all_courses.append(COMMA);
  }
  return all_courses.substr(0, all_courses.size() - 1);
}

void Student::get_my_course() {
  if (taken_courses.empty())
    throw Empty_EX();
  for (auto c : taken_courses) {
    cout << c->get_id() << SPACE << c->get_course()->get_name() << SPACE
         << c->get_capacity() << SPACE << c->get_prof_name() << SPACE
         << c->get_time().get_week_day() << COLON
         << c->get_time().get_start_hour() << LINE
         << c->get_time().get_end_hour() << SPACE << c->get_date().get_year()
         << SLASH << c->get_date().get_month() << SLASH
         << c->get_date().get_day() << SPACE << c->get_class_num() << endl;
  }
}

void Student::show_personal_page(vector<Major *> majors) {
  cout << name << SPACE << find_major(majors, major_id) << SPACE << semester
       << SPACE << get_courses() << endl;
  show_posts();
}

void Student::show_specific_page(vector<Major *> majors, int post_id_) {
  cout << name << SPACE << find_major(majors, major_id) << SPACE << semester
       << SPACE << get_courses() << endl;
  find_post(post_id_);
}

void Student::delete_course(int course_id) {
  for (int i = 0; i < taken_courses.size(); i++) {
    if (taken_courses[i]->get_id() == course_id) {
      taken_courses.erase(taken_courses.begin() + i);
      return;
    }
  }
  throw Undefined_EX();
}