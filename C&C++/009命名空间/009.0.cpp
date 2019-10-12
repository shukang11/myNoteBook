#include <iostream>
#include <string>

using namespace std;

namespace A_space {
    void soa() {
        cout << "Inside A-space" << endl;
    }
};

namespace B_space {
    void soa() {
        cout << "Inside B_space" << endl;
    }
};

using namespace B_space;
int main() {
    A_space::soa();
    soa();
    return 0;
};