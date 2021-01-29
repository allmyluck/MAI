#include <iostream>

int main() {
   
    srand(time(NULL));
    for(int i = 0; i < 16000000; i++) {
        for(int i = 0; i < (1 + rand() % 17); i++) {
            std::cout << char ('a' + rand() % ('z' - 'a'));
        }
        std::cout << " ";
        if(i % 50 == 0 && i != 0) {
            std::cout << "\n";
        }
    }
    return 0;
}
