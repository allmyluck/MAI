#include <iostream>

int main() {
    srand(time(NULL));
    unsigned long long max, lines, start, finish;
    std::cin >> max >> lines;
    start = rand() % max + 1;
    finish = rand() % max + 1;
    std::cout <<  max << " " << lines << " " << start << " " << finish << std::endl;
    for(unsigned long long i = 0; i < lines; i++) {
        std::cout << rand() % max + 1  << " " << rand() % max + 1 << " " << rand() % 800 + 1 << std::endl;
    }
    return 0;
}