#include "Course.hpp"
#include "Prof.hpp"
#include "Split.hpp"
#include <iostream>
#include <string>
#define SPACE " "
#define SLASH_DELIMITER "/"
#define COLON_DELIMITER ":"
#define LINE_DELIMITER "-"

Course::Course(int i, string n, int c, int p, vector<int> a) {
  set_info(i, n, c, p, a);
}

void Course::set_info(int i, string n, int c, int p, vector<int> a) {
  id = i;
  name = n;
  credit = c;
  pre_req = p;
  allowed_majors = a;
}

int Course::get_id() { return id; }

string Course::get_name() { return name; }

int Course::get_pre_req() { return pre_req; }

int Course_Presentation::get_capacity() { return capacity; }

vector<int> Course::get_majors() { return allowed_majors; }

Course_Presentation::Course_Presentation(int id_, int prof_id_, int capacity_,
                                         string time_, string exam_date_,
                                         int class_number_, Course *course_,
                                         string prof_) {
  set_info(id_, prof_id_, capacity_, time_, exam_date_, class_number_, course_,
           prof_);
}

string Course_Presentation::get_prof_name() { return prof_name; }

Date Course_Presentation::get_date() { return date; }

int Course_Presentation::get_class_num() { return class_number; }

bool check_time(int start, int end, int temp_start, int temp_end) {
  for (int i = start; i < end + 1; i++) {
    for (int j = temp_start; j < temp_end + 1; j++) {
      if (i == j) {
        return true;
      }
    }
  }
  return false;
}

bool Course_Presentation::is_same_time(string time_) {
  vector<string> temp_time = split(time_, COLON_DELIMITER);
  vector<string> temp_hour = split(temp_time[1], LINE_DELIMITER);
  bool same_time = check_time(time.get_start_hour(), time.get_end_hour(),
                              stoi(temp_hour[0]), stoi(temp_hour[1]));
  if (time.get_week_day() == temp_time[0] && same_time)
    return false;
  return true;
}

// (time.get_start_hour() == stoi(temp_hour[0]) || time.get_start_hour() ==
//     && time.get_end_hour() == stoi(temp_hour[1]))

void Course_Presentation::set_info(int id_, int prof_id_, int capacity_,
                                   string time_, string exam_date_,
                                   int class_number_, Course *course_,
                                   string prof_) {
  course = course_;
  id = id_;
  prof_id = prof_id_;
  capacity = capacity_;
  class_number = class_number_;
  prof_name = prof_;
  set_date(exam_date_);
  set_time(time_);
}

void Course_Presentation::show_courses() {
  cout << id << SPACE << course->get_name() << SPACE << capacity << SPACE
       << prof_name << endl;
}

void Course_Presentation::show_specific_course() {
  cout << id << SPACE << course->get_name() << SPACE << capacity << SPACE
       << prof_name << SPACE << time.get_week_day() << COLON_DELIMITER
       << time.get_start_hour() << LINE_DELIMITER << time.get_end_hour()
       << SPACE << date.get_day() << SLASH_DELIMITER << date.get_month()
       << SLASH_DELIMITER << date.get_year() << SPACE << class_number << endl;
}

Date::Date() {
  day = 1;
  month = 1;
  year = 1;
}

Date::Date(int day_, int month_, int year_) { set_info(day_, month_, year_); }

void Date::set_info(int day_, int month_, int year_) {
  day = day_;
  month = month_;
  year = year_;
}

int Date::get_day() { return day; }

int Date::get_month() { return month; }

int Date::get_year() { return year; }

Time::Time() {
  week_day = " ";
  start_hour = 0;
  end_hour = 0;
}

Time::Time(string week_day_, int start_hour_, int end_hour_) {
  set_info(week_day_, start_hour_, end_hour_);
}

void Time::set_info(string week_day_, int start_hour_, int end_hour_) {
  week_day = week_day_;
  start_hour = start_hour_;
  end_hour = end_hour_;
}

string Time::get_week_day() { return week_day; }

int Time::get_end_hour() { return end_hour; }

int Time::get_start_hour() { return start_hour; }

void Course_Presentation::set_date(string date_) {
  vector<string> temp_date = split(date_, SLASH_DELIMITER);
  date = Date(stoi(temp_date[2]), stoi(temp_date[1]), stoi(temp_date[0]));
}

void Course_Presentation::set_time(string time_) {
  vector<string> temp_time = split(time_, COLON_DELIMITER);
  vector<string> temp_hour = split(temp_time[1], LINE_DELIMITER);
  time = Time(temp_time[0], stoi(temp_hour[0]), stoi(temp_hour[1]));
}

bool Course_Presentation::is_correct_course(int id_) {
  if (id == id_)
    return true;
  else
    return false;
}

int Course_Presentation::get_id() { return id; }

int Course_Presentation::get_prof_id() { return prof_id; }

Time Course_Presentation::get_time() { return time; }

Course *Course_Presentation::get_course() { return course; }

bool Course_Presentation::is_student_same_time(
    vector<Course_Presentation *> c) {
  for (auto cours : c) {
    if (cours->get_time().get_week_day() == time.get_week_day() &&
        cours->get_time().get_start_hour() == time.get_start_hour() &&
        cours->get_time().get_end_hour() == time.get_end_hour()) {
      return false;
    } else
      return true;
  }
}