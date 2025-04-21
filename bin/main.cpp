#include <iostream>
#include <string>
#include "LCSQuery.h"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s, t;
    std::cin >> s >> t;
    LCSQuery lcsQuery(s, t);
    int q;
    std::cin >> q;
    while(q--) {
        int i, j;
        std::cin >> i >> j;
        std::cout << lcsQuery.Query(i, j) << "\n";
    }
    return 0;
}
