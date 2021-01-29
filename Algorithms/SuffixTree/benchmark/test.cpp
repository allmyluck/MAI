#include <iostream>

int main() {
   
    srand(time(NULL));
    int amount;
    std::cin >> amount;
    for(int i = 0; i < amount; i++) {
        for(int i = 0; i < (20); i++) {
            std::cout << char ('a' + rand() % ('z' - 'a'));
        }
            std::cout << "\n";
    }
    return 0;
}
