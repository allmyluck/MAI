#include "search.hpp"
#include <ctime>

int main() {
    std::ios::sync_with_stdio(false);
    TZBlocks gg;
    gg.Read();
    double start, end;
    start = clock();
    gg.Result();
    end = clock();
    std::cout << "Time of working " << (end - start) / CLOCKS_PER_SEC << "sec" << std::endl;
    return 0;
}