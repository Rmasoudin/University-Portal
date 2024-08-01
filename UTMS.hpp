#ifndef _UTMS_
#define _UTMS_
#include "Course.hpp"
#include "Major.hpp"
#include "Prof.hpp"
#include "Student.hpp"
#include <vector>
class Token {
public:
  Token(int i, string p);
  int get_id();
  string get_pass();

private:
  int id;
  string password;
  void set_info(int i, string p);
};

class Ut_Account {
public:
  void add_post(Post *post_);
  void show_posts();
  void find_posts(int post_id);
  Hub *get_hub();

private:
  Hub *hub = new Hub();
};

class UTMS {
public:
  UTMS(vector<Student *> s, vector<Prof *> p, vector<Major *> m,
       vector<Course *> c);
  string check_login(int i, string p);
  string check_connection(int user_id, int wanted_id);
  void post(string title_, string message_, int id_);
  void connect(int user_id, int wanted_id);
  void get_courses();
  void get_specific_course(int id);
  void present_course(int id_, int prof_id_, int capacity_, string time_,
                      string exam_date_, int class_number_, Course *course_);
  Course *find_course(int id_);
  bool check_course_availabilty(int course_id);
  bool check_course_pre_req(int course_id, int user_id);
  string check_prof_availabilty(int prof_id, int course_id);
  bool check_prof_time(int prof_id, string time);
  void take_course(int course_id, int user_id);
  bool check_course_time(int course_id, int used_id);
  bool show_personal_page(int id_);
  bool get_specific_post(int id_, int post_id_);
  bool check_course_major(int course_id, int user_id);
  void delete_post(int post_id, int user_id);
  void delete_course(int course_id, int user_id);
  void get_my_course(int self_id);
  void add_notif(int id_, string message_);
  void add_all_notif(int id_, string message_);
  void get_notif(int id_);

private:
  vector<Student *> students;
  vector<Prof *> profs;
  vector<Major *> majors;
  vector<Course *> courses;
  vector<Course_Presentation *> available_courses;
  string find_prof(int id_);
  void set_info(vector<Student *> s, vector<Prof *> p, vector<Major *> m,
                vector<Course *> c);
};
#endif