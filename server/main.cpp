#include "Server.h"

int main() {
    Server s("127.0.0.1", "8080", 1);
    s.run();

    return 0;
}