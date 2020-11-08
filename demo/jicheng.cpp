#include <iostream>
#include <string>
using namespace std;
class Staff {
public:
    virtual void set_birth(string birth) {
        _birth = birth;
    }

private:
    string _birth;
};

class Leader:public Staff {
public:
    using Staff::set_birth;
    virtual void set_birth(int birth) {
        set_birth(to_string(birth));
    }
};

int main() {
    Leader s;
    s.set_birth("1990");
    return 0;
}

