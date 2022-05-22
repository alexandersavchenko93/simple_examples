// https://lejabque.github.io/cpp-notes/18_decltype_auto_nullptr.html

// DECLTYPE
struct x {
    int a;
};

int main() {
    decltype(x::a) n = 10;
    
    int a;
    decltype(a) b = 42; // int b = 42
    decltype((a)) c = a; // int& c = a
}
