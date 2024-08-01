#ifndef _MAJOR_
#define _MAJOR_
#include <string>
#include <vector>
using namespace std;

class Major {
public:
  Major(vector<string> info);
  int get_id();
  string get_name();

private:
  string name;
  int id;
  void set_info(vector<string> info);
};

#endif