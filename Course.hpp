#ifndef _COURSE_
#define _COURSE_
#include <string>
#include <vector>
using namespace std;

class Course {
public:
  Course(int i, string n, int c, int p, vector<int> a);
  int get_id();
  string get_name();
  int get_pre_req();
  vector<int> get_majors();

private:
  int id;
  string name;
  int credit;
  int pre_req;
  vector<int> allowed_majors;
  void set_info(int i, string n, int c, int p, vector<int> a);
};

class Date {
public:
  Date();
  Date(int day_, int month_, int year_);
  int get_day();
  int get_month();
  int get_year();

private:
  int day;
  int month;
  int year;
  void set_info(int day_, int month_, int year_);
};

class Time {
public:
  Time();
  Time(string week_day_, int start_hour_, int end_hour_);
  string get_week_day();
  int get_start_hour();
  int get_end_hour();

private:
  string week_day;
  int start_hour;
  int end_hour;
  void set_info(string week_day_, int start_hour_, int end_hour_);
};

class Course_Presentation {
public:
  Course_Presentation(int id_, int prof_id_, int capacity_, string time_,
                      string exam_date_, int class_number_, Course *course_,
                      string prof_);
  void show_courses();
  void show_specific_course();
  bool is_correct_course(int id_);
  bool is_same_time(string time_);
  int get_id();
  int get_prof_id();
  int get_capacity();
  string get_prof_name();
  Time get_time();
  Date get_date();
  int get_class_num();
  bool is_student_same_time(vector<Course_Presentation *> c);
  Course *get_course();

private:
  Course *course;
  int id;
  int prof_id;
  string prof_name;
  int capacity;
  int class_number;
  Date date;
  Time time;
  void set_date(string date_);
  void set_time(string time_);
  void set_info(int id_, int prof_id_, int capacity_, string time_,
                string exam_date_, int class_number_, Course *course_,
                string prof_);
};
#endif