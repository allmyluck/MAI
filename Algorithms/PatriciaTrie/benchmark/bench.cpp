#include "Patricia.hpp"
#include <ctime>


struct TData_type {
    unsigned long long data;
    char* key;
    TData_type() : key(nullptr), data(0)
    {}
    
    void Init(char*& nkey, unsigned long long ndata) {
        key = std::move(nkey);
        data = ndata;
    }

};

int main() {
    TPatricia* temp = new TPatricia;
    unsigned long long size,sizestr;
    std::cin >> size;
    std::cin >> sizestr;
    std::cout << "Size of test: " << size << "\n";
    std::cout << "Size of str : " << sizestr << "\n";
    sizestr = sizestr + 1;
    unsigned long long a;
    TData_type table[size];
    for(long int i = 0;i < size;i++) {
        char* str = new char[sizestr];
        std::cin >> str;
        std::cin >> a;
        table[i].Init(str,a);
    }
    double start, end;
    start = clock();
    for(int i = 0; i < size; i++) {
        temp->Insert(table[i].key,table[i].data);
    }
    end = clock();
    std::cout << "Time of working(Insert) " << (end - start) / CLOCKS_PER_SEC << "sec" << std::endl;
    double start1, end1;
    start1 = clock();
    for(int i = 0; i < size; i++) {
        temp->Delete(table[i].key);
    }
    end1 = clock();
    std::cout << "Time of working(Delete) " <<  (end1 - start1) / CLOCKS_PER_SEC << "sec" << std::endl; 
    delete temp;
    return 0;
}
