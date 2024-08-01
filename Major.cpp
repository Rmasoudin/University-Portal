#include "Major.hpp"

Major::Major(vector<string> info) { set_info(info); }

void Major::set_info(vector<string> info) {
  name = info[1];
  id = stoi(info[0]);
}

int Major::get_id() { return id; }

string Major::get_name() { return name; }