#include "User.hpp"
#include "Exception.hpp"
#include <iostream>
#define SPACE " "
using namespace std;
#define DEFAULT_ID 0
#define DEFAULT_STRING " "
#define COLON ":"

void User::set_info(string n, int i, int m_i, string p) {
  name = n;
  id = i;
  major_id = m_i;
  password = p;
}

User::User(string n, int i, int m_i, string p) { set_info(n, i, m_i, p); }

int User::get_id() { return id; }

string User::get_pass() { return password; }

Post::Post(string title_, string message_) { set_info(title_, message_); }

void Post::set_info(string title_, string message_) {
  id = 0;
  title = title_;
  message = message_;
}

void User::add_post(Post *post_) { hub->add_post(post_); }

vector<int> User::get_con() { return connections; }

void User::add_connection(int wanted) { connections.push_back(wanted); }

int User::get_major_id() { return major_id; }

string User::get_name() { return name; }

void User::show_posts() { hub->show_posts(); }

void User::find_post(int post_id_) { hub->find_post(post_id_); }

void User::delete_post(int post_id_) { hub->delete_post(post_id_); }

void User::add_notif(int id_, string name_, string message_) {
  notifs.push_back(new Notif(id_, name_, message_));
}

Notif::Notif() {
  id = DEFAULT_ID;
  name = DEFAULT_STRING;
  message = DEFAULT_STRING;
}

void User::get_notif() {
  if (notifs.empty())
    throw Empty_EX();
  for (int i = notifs.size() - 1; i > -1; i--) {
    cout << notifs[i]->get_id() << SPACE << notifs[i]->get_name() << COLON
         << SPACE << notifs[i]->get_message() << endl;
  }
  notifs.clear();
}

void Post::set_id(int id_) { id = id_; }

int Post::get_id() { return id; }

string Post::get_title() { return title; }

string Post::get_message() { return message; }

void Hub::add_post(Post *post_) {
  posts.push_back(post_);
  if (posts.size() == 1) {
    id_controller = 1;
    posts[0]->set_id(id_controller);
    return;
  }
  id_controller += 1;
  posts[posts.size() - 1]->set_id(id_controller);
}

void Hub::show_posts() {
  if (posts.empty())
    throw Empty_EX();
  for (auto p : posts) {
    cout << p->get_id() << SPACE << p->get_title() << endl;
  }
}

void Hub::find_post(int post_id_) {
  for (auto p : posts) {
    if (p->get_id() == post_id_)
      cout << p->get_id() << SPACE << p->get_title() << SPACE
           << p->get_message() << endl;
  }
}

void Hub::delete_post(int post_id_) {
  for (int i = 0; i < posts.size(); i++) {
    if (posts[i]->get_id() == post_id_) {
      posts.erase(posts.begin() + i);
      return;
    }
  }
  throw Undefined_EX();
}

Notif::Notif(int id_, string name_, string message_) {
  set_info(id_, name_, message_);
}

void Notif::set_info(int id_, string name_, string message_) {
  id = id_;
  name = name_;
  message = message_;
}

int Notif::get_id() { return id; }

string Notif::get_name() { return name; }

string Notif::get_message() { return message; }