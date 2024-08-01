#include "Split.hpp"

vector<string> split(string s, string delimiter) {
  vector<string> splited;
  int pos = s.find(delimiter);
  while (pos != -1) {
    string each_char = s.substr(0, pos);
    splited.push_back(each_char);
    s = s.substr(pos + 1);
    pos = s.find(delimiter);
  }
  splited.push_back(s);
  return splited;
}