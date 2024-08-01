#ifndef USER
#define USER
#include <string>
#include <vector>
using namespace std;

class Post {
public:
  Post(string title_, string message_);
  void set_id(int id_);
  string get_title();
  string get_message();
  int get_id();

private:
  int id;
  string title;
  string message;
  void set_info(string title_, string message_);
};

class Hub {
public:
  void add_post(Post *post_);
  void show_posts();
  void find_post(int post_id_);
  void delete_post(int post_id_);

private:
  int id_controller;
  vector<Post *> posts;
};

class Notif {
public:
  Notif();
  Notif(int id_, string name_, string message_);
  int get_id();
  string get_name();
  string get_message();

private:
  int id;
  string name;
  string message;
  void set_info(int id_, string name_, string message_);
};

class User {
public:
  User(string n, int i, int m_i, string p);
  int get_id();
  string get_name();
  string get_pass();
  vector<int> get_con();
  int get_major_id();
  void add_post(Post *post_);
  void add_connection(int wanted);
  void show_posts();
  void find_post(int post_id_);
  void delete_post(int post_id_);
  void add_notif(int id_, string name_, string message_);
  void get_notif();

protected:
  string name;
  int id;
  int major_id;
  string password;
  Hub *hub = new Hub();
  vector<Notif *> notifs;
  vector<int> connections;
  void set_info(string n, int i, int m_i, string p);
};

#endif