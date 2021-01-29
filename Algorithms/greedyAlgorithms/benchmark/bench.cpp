#include <iostream>

struct TInformation {
    long long *values;
    long long *counts;
    long long size;
    TInformation(long long& amount,long long& value) {
        values = new long long[amount];
        counts = new long long[amount];
        size = amount;
        for(long long i = 0, tempvalue = 1;i < amount;i++) {
            counts[i] = 0;
            values[i] = tempvalue;
            tempvalue *= value;
        }
    }

    ~TInformation() {
        delete [] values;
        delete [] counts;
    }

    void Print() {
        for(long long i = 0; i < size; i++) {
            std::cout << counts[i] << "\n";
        }
    }
};


int main() {
    long long n, p, number;
    std::cin >> n >> p >> number;
    if(n <= 0 || p <= 0) {
        return 0;
    }
    if(p == 1) {
        std::cout << number << "\n";
        return 0;
    }
    TInformation table(n,p);
    long long tempcount;
    double start,end;
    start = clock();
    while(number) {
        tempcount = number / table.values[n - 1];
        number = number - tempcount * table.values[n - 1];
        table.counts[n - 1] = tempcount;
        n--;
    }
    end = clock();
    std::cout << "Time of working " << (end - start) / CLOCKS_PER_SEC << "sec" << std::endl;
    //table.Print();
    return 0;
}