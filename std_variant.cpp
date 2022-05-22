#include <iostream>
#include <string>
#include <variant>
#include <vector>
 
struct a {
  int x;
 
  a(int x)
    : x{x}
  { }
 
  void operator()() const {
    std::cout << "a(" << x << ")\n";
  }
};
 
struct b {
  std::string y;
 
  b(std::string y)
    : y{y}
  { }
 
  void operator()() const {
    std::cout << "b[" << y << "]\n";
  }
};
 
using action_t = std::variant<a, b>;
 
struct executor {
  void operator()(const a &obj) {
    obj();
  }
 
  void operator()(const b &obj) {
    obj();
  }
};
 
void f(const std::vector<action_t> &actions) {
  for (auto it = actions.begin(); it != actions.end(); ++it) {
    std::visit(executor{}, *it);
  }
}
 
int main(int c, char **v) {
  std::vector<action_t> actions;
  for (int i = 1; i < c; ++i) {
    try {
      actions.push_back(a{std::stoi(v[i])});
    } catch (const std::invalid_argument &) {
      actions.push_back(b{v[i]});
    }
  }
  f(actions);
  return 0;
}
