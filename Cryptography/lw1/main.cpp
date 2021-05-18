#include <iostream>
#include <string>
#include <vector>
#include <csignal>
#include <ctime>
#include <cmath>
#include <gmpxx.h>
#include <fstream>


using namespace std;


int main() {
    mpz_class number, result;
    ifstream file("vars.txt");
    vector<mpz_class> numbers(39);
    string s;
    int i = 0;
    while(getline(file, s)) {
       numbers[i] = s;
       i++;
    }
    file.close();
    number = "1695128485402083763773247025508607781296883851800934596605324477902989989672390098441314233687038522543796524362932674511659084990877094461405769068305253980165481952276151264282270169307424982451349364468884452626363366332792106697498300154504289109043538314722171490851577202002936469515837846884472685701320555954675270470981711883452876152967636160722991943031737727674462234803964546522349706678813412341712703190842025567979822278829254837642753739546649159";
    for (unsigned i = 0; i < numbers.size(); ++i) {
        mpz_gcd(result.get_mpz_t(), numbers[i].get_mpz_t(), number.get_mpz_t());
        if (result != 1) {
            cout << "index: " << i << endl;
            cout << "factor 1: " << result << endl;
            cout << "factor 2: " << number / result << endl;
            break;
        }
    }
    return 0;
}