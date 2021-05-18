#include <iostream>
#include <string>
#include <gmpxx.h>
#include <vector>
#include <ctime>


class po_Polard{
public:
    po_Polard(const mpz_class& num);
    po_Polard(const std::string& num);
    mpz_class get_factor();
private:
    mpz_class factor_of_num(mpz_class& num);
    void Polard_GCD(mpz_class& ans, mpz_class& x, mpz_class& y);
    void Polard_MOD(mpz_class& ans, mpz_class& x, mpz_class& y);
    void Polard_ABSOLUTE(mpz_class& ans, mpz_class& x, mpz_class& y);
    mpz_class number;
};


mpz_class po_Polard::factor_of_num(mpz_class& num){
    mpz_class x, y, ans, absolute;
    unsigned long long i = 0, stage = 2;
    x = (rand() % (number - 1)) + 1;
    y = 1;
    Polard_ABSOLUTE(absolute, x, y);
    Polard_GCD(ans, num, absolute);
    while(ans == 1){
        if(i == stage){
            y = x;
            stage <<= 1;
        }
        absolute = x * x + 1;
        Polard_MOD(x, absolute, num);
        ++i;
        Polard_ABSOLUTE(absolute, x, y);
        Polard_GCD(ans, num, absolute);
    }
    return ans;
}

mpz_class po_Polard::get_factor(){
    return factor_of_num(number);
}


po_Polard::po_Polard(const mpz_class& num){
    srand(time(0));
    number = num;
}

po_Polard::po_Polard(const std::string& str){
    srand(time(0));
    number = str;
}

void po_Polard::Polard_ABSOLUTE(mpz_class& ans, mpz_class& x, mpz_class& y){
    x -= y;
    mpz_abs(ans.get_mpz_t(), x.get_mpz_t());
    x += y;
}


void po_Polard::Polard_GCD(mpz_class& ans, mpz_class& x, mpz_class& y){
    mpz_gcd(ans.get_mpz_t(), x.get_mpz_t(), y.get_mpz_t());
}

void po_Polard::Polard_MOD(mpz_class& ans, mpz_class& x, mpz_class& y){
    mpz_mod(ans.get_mpz_t(), x.get_mpz_t(), y.get_mpz_t());
}

using namespace std;

int main(){
    // 95383 95393 
    std::string number = "9098870519";
    mpz_class numberBig;
    numberBig = number; 
    po_Polard polard(numberBig);
    double startcl, end;
    startcl = clock();
    mpz_class factor = polard.get_factor();
    std::cout << "Factor_1: " << factor << endl;
    std::cout << "Factor_2: " << numberBig / factor << endl;
    end = clock();
    std::cout << "Time of working " << (end - startcl) / CLOCKS_PER_SEC << "sec" << std::endl;
    return 0;
}