#include <iostream>
#include <string>
#include <variant>
 
using action_t = std::variant<std::string, bool, int>;
 
struct SettingVisitor {
    void operator()(const std::string& s) const {
        printf("A string: %s\n", s.c_str());
    }

    void operator()(const int n) const {
        printf("An integer: %d\n", n);
    }

    void operator()(const bool b) const {
        printf("A boolean: %d\n", b);
    }
};

int main() {
    action_t a("Hello");
    action_t b(true);
    action_t c(1);

    std::cout << a.index() << std::endl;
    std::cout << b.index() << std::endl;
    std::cout << c.index() << std::endl;
    
    std::visit(SettingVisitor{}, a);
    std::visit(SettingVisitor{}, b);
    std::visit(SettingVisitor{}, c);
    
    return 0;
}
