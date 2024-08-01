#ifndef _DATA_READER_
#define _DATA_READER_
#include "UTMS.hpp"
#include <vector>
using namespace std;
typedef const char route;

class Data_Reader {
public:
  UTMS *set_info(route *file_path[]);

private:
  vector<Student *> retrieve_student_info(route *student_path);
  vector<Prof *> retrieve_prof_info(route *prof_path);
  vector<Major *> retrieve_major_info(route *major_path);
  vector<Course *> retrieve_course_info(route *course_path);
};

#endif