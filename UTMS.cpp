#include "UTMS.hpp"
#include "Exception.hpp"
#include "Split.hpp"
#include <algorithm>
#include <iostream>
#define COLON_DELIMITER ":"
#define LINE_DELIMITER "-"
#define UT_ACOOUNT_PASS "UT_account"
bool compare_id(Prof *a, Prof *b) { return a->get_id() < b->get_id(); }

UTMS::UTMS(vector<Student *> s, vector<Prof *> p, vector<Major *> m,
           vector<Course *> c) {
  set_info(s, p, m, c);
}

void UTMS::set_info(vector<Student *> s, vector<Prof *> p, vector<Major *> m,
                    vector<Course *> c) {
  students = s;
  profs = p;
  majors = m;
  courses = c;
  sort(profs.begin(), profs.end(), compare_id);
}

string UTMS::check_login(int i, string p) {
  int check_id = 0;
  int check_pass = 0;
  for (auto users : students) {
    if (users->get_id() == i) {
      if (users->get_pass() == p)
        return STUDENT_SUCCESS;
      check_pass++;
      if (check_pass == students.size() - 1)
        return ILLEGAL_REQUEST_MESSAGE;
    }
    check_id++;
  }
  if (check_id == students.size())
    return UNDEFINED_MESSAGE;
  check_id, check_pass = 0;
  for (auto users : profs) {
    if (users->get_id() == i) {
      if (users->get_pass() == p)
        return PROF_SUCCESS;
      check_pass++;
      if (check_pass == profs.size() - 1)
        return ILLEGAL_REQUEST_MESSAGE;
    }
    check_id++;
  }
  if (check_id == profs.size())
    return UNDEFINED_MESSAGE;
}

void UTMS::post(string title_, string message_, int id) {
  Post *temp_post = new Post(title_, message_);
  for (int i = 0; i < students.size(); i++) {
    if (students[i]->get_id() == id) {
      students[i]->add_post(temp_post);
      return;
    }
  }
  for (int i = 0; i < profs.size(); i++) {
    if (profs[i]->get_id() == id) {
      profs[i]->add_post(temp_post);
      return;
    }
  }
}

string UTMS::check_connection(int user_id, int wanted_id) {
  for (int i = 0; i < students.size(); i++) {
    if (students[i]->get_id() == user_id) {
      for (int j = 0; j < students[i]->get_con().size(); j++) {
        if (students[i]->get_con()[j] == wanted_id)
          return WRONG_REQUEST_MESSAGE;
      }
    }
    if (students[i]->get_id() == wanted_id)
      return SUCCESS_MESSAGE;
  }
  return UNDEFINED_MESSAGE;
}

void UTMS::connect(int user_id, int wanted_id) {
  for (int i = 0; i < students.size(); i++) {
    if (students[i]->get_id() == user_id)
      students[i]->add_connection(wanted_id);
    if (students[i]->get_id() == wanted_id)
      students[i]->add_connection(user_id);
    if (profs[i]->get_id() == user_id)
      profs[i]->add_connection(wanted_id);
    if (profs[i]->get_id() == wanted_id)
      profs[i]->add_connection(user_id);
  }
}

void UTMS::get_courses() {
  if (available_courses.empty())
    throw Empty_EX();
  for (auto course : available_courses) {
    course->show_courses();
  }
}

void UTMS::get_specific_course(int id_) {
  if (available_courses.empty())
    throw Empty_EX();
  for (auto course : available_courses)
    if (course->is_correct_course(id_))
      course->show_specific_course();
}

string UTMS::find_prof(int id_) {
  for (auto prof : profs) {
    if (prof->get_major_id() == id_) {
      return prof->get_name();
    }
  }
}

void UTMS::get_my_course(int self_id) {
  for (auto st : students) {
    if (st->get_id() == self_id)
      st->get_my_course();
  }
}

bool UTMS::check_course_major(int course_id, int user_id) {
  for (auto c : courses) {
    if (c->get_id() == course_id) {
      for (auto st : students) {
        if (st->get_id() == user_id) {
          for (auto maj : c->get_majors()) {
            if (maj == st->get_major_id())
              return true;
          }
        }
      }
    }
  }
  return false;
}

void UTMS::delete_post(int post_id, int user_id) {
  for (auto st : students) {
    if (st->get_id() == user_id) {
      st->delete_post(post_id);
      return;
    }
  }
  for (auto prof : profs) {
    if (prof->get_id() == user_id) {
      prof->delete_post(post_id);
      return;
    }
  }
  throw Undefined_EX();
}

void UTMS::add_notif(int id_, string message_) {
  for (auto st : students) {
    if (st->get_id() == id_)
      for (auto cn : st->get_con()) {
        for (auto noti : students) {
          if (noti->get_id() == cn) {
            noti->add_notif(id_, st->get_name(), message_);
          }
        }
        for (auto p : profs) {
          if (p->get_id() == cn) {
            p->add_notif(id_, st->get_name(), message_);
          }
        }
      }
  }
  for (auto prof : profs) {
    if (prof->get_id() == id_)
      for (auto cn : prof->get_con()) {
        for (auto noti : profs) {
          if (noti->get_id() == cn) {
            noti->add_notif(id_, prof->get_name(), message_);
          }
        }
        for (auto s : students) {
          if (s->get_id() == cn) {
            s->add_notif(id_, prof->get_name(), message_);
          }
        }
      }
  }
}

void UTMS::add_all_notif(int id_, string message_) {
  if (id_ == 0) {
    for (auto st : students) {
      st->add_notif(id_, UT_ACOOUNT_PASS, message_);
    }
    for (auto prof : profs) {
      prof->add_notif(id_, UT_ACOOUNT_PASS, message_);
    }
  }
  for (auto prof : profs) {
    if (prof->get_id() == id_) {
      for (auto st : students) {
        st->add_notif(id_, prof->get_name(), message_);
      }
      for (auto prof : profs) {
        prof->add_notif(id_, prof->get_name(), message_);
      }
    }
  }
}

void UTMS::delete_course(int course_id, int user_id) {
  for (auto st : students) {
    if (st->get_id() == user_id) {
      st->delete_course(course_id);
      return;
    }
  }
  throw Undefined_EX();
}

void UTMS::get_notif(int id_) {
  for (auto st : students) {
    if (st->get_id() == id_) {
      st->get_notif();
    }
  }
  for (auto prof : profs) {
    if (prof->get_id() == id_) {
      prof->get_notif();
    }
  }
}

void UTMS::present_course(int id_, int prof_id_, int capacity_, string time_,
                          string exam_date_, int class_number_,
                          Course *course_) {
  available_courses.push_back(
      new Course_Presentation(id_, prof_id_, capacity_, time_, exam_date_,
                              class_number_, course_, find_prof(id_)));
}

Course *UTMS::find_course(int id_) {
  for (auto course : courses)
    if (course->get_id() == id_)
      return course;
}

bool UTMS::check_course_availabilty(int course_id) {
  for (auto course : courses) {
    if (course->get_id() == course_id) {
      return true;
    }
  }
  return false;
}

bool UTMS::check_prof_time(int prof_id, string time) {
  if (available_courses.size() != 0) {
    for (auto course : available_courses) {
      if (course->get_prof_id() == prof_id)
        if (!course->is_same_time(time))
          return false;
        else
          return true;
    }
  } else
    return true;
}

bool UTMS::check_course_time(int course_id, int user_id) {
  for (auto st : students) {
    if (st->get_id() == user_id) {
      for (auto course : available_courses) {
        if (course->get_id() == course_id) {
          if (st->get_taken_courses().size() == 0)
            return true;
          if (!course->is_student_same_time(st->get_taken_courses())) {
            return false;
          } else {
            return true;
          }
        }
      }
    }
  }
}

string UTMS::check_prof_availabilty(int prof_id, int course_id) {
  for (auto c : courses) {
    if (c->get_id() == course_id) {
      for (auto p : profs) {
        if (p->get_id() == prof_id) {
          for (auto m : c->get_majors()) {
            if (m == p->get_major_id()) {
              return SUCCESS_MESSAGE;
            }
          }
          return ILLEGAL_REQUEST_MESSAGE;
        }
      }
    }
  }
  for (auto st : students) {
    if (st->get_id() == prof_id)
      return ILLEGAL_REQUEST_MESSAGE;
  }
  return UNDEFINED_MESSAGE;
}

void UTMS::take_course(int course_id, int user_id) {
  for (auto student : students) {
    if (student->get_id() == user_id)
      for (auto course : available_courses) {
        if (course->get_id() == course_id)
          student->take_course(course);
      }
  }
}

bool UTMS::check_course_pre_req(int course_id, int user_id) {
  for (auto course : courses) {
    if (course->get_id() == course_id) {
      for (auto student : students) {
        if (student->get_id() == user_id) {
          if (course->get_pre_req() > student->get_semester()) {
            return false;
          } else {
            return true;
          }
        }
      }
    }
  }
}

bool UTMS::show_personal_page(int id_) {
  for (auto st : students) {
    if (st->get_id() == id_) {
      st->show_personal_page(majors);
      return true;
    }
  }
  for (auto p : profs) {
    if (p->get_id() == id_) {
      p->show_personal_page(majors, available_courses);
      return true;
    }
  }
  return false;
}

bool UTMS::get_specific_post(int id_, int post_id_) {
  for (auto st : students) {
    if (st->get_id() == id_) {
      st->show_specific_page(majors, post_id_);
      return true;
    }
  }
  for (auto p : profs) {
    if (p->get_id() == id_) {
      p->show_specific_page(majors, available_courses, post_id_);
      return true;
    }
  }
  return false;
}

void Ut_Account::add_post(Post *post) { hub->add_post(post); }

void Ut_Account::show_posts() { hub->show_posts(); }

void Ut_Account::find_posts(int post_id) { hub->find_post(post_id); }

Hub *Ut_Account::get_hub() { return hub; }
