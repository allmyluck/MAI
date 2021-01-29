//Токарев Никита Станиславович M8o-207Б-18
/*Реализовать класс FazzyNumber для работы с нечеткими числами, которые представляются тройками
чисел (x – e, x, x + e). Для чисел A = (A – a, A, A + a) и B = (B – b, B, B + b) арифметические операции
выполняются по следующим формулам:
сложение A + B = (A + B – a  – b  , A + B, A + B + a + b);
вычитание A – B = (A – B – a – b, A – B, A – B + a+ b);
умножение A * B = (A * B – B * a  – A * b + a * b , A * B, A * B + B * a + A * b  + a * b);
обратное число A = (1 / (A + a), 1 / A, 1 / (A – a)), A>0;
деление A / B = ((A – a) / (B + b), A / B, (A + a) / (B – b)), B>0;
Считать,что число представлено парой (x,e);.
Реализовать операции сравнения по х.
Операции сложения, вычитания, умножения, деления, сравнения (на равенство, больше и меньше) должны быть выполнены в виде перегрузки операторов. 
Необходимо реализовать пользовательский литерал для работы с константами типа FazzyNumber.
*/
#include <iostream>
#include <cstdlib>
using namespace std;
void help() {//функция,описывающая возможные вызовы в свич-меню
    printf("A+B: press a\n");
    printf("Print: press p\n");
    printf("A/B: press d\n");
    printf("A in -1: press r\n");
    printf("A-B: press s\n");
    printf("A*B: press m\n");
    printf("A>?B: press c\n");
    printf("Help: press h\n");
    printf("Exit: press e\n");
}



class fazzynumber {
    private:
        long  double a,e,l,c,r;
    public:
    fazzynumber(long double x, long double y) {//конструктор класса
        a = x;
        e = y;
    }
    fazzynumber & operator + (const fazzynumber & b) {//функция сложения двух нечетких чисел
        long double a1,e1;
        a1 = (this->a) + b.a;
        e1 = (this->e) + b.e;
        l = a1 - e1;
        c = a1;
        r = a1 + e1; 
        return *this;
    }
    fazzynumber & operator -(const fazzynumber & b) {//функция вычитания
        long double a1,e1;
        a1 = this->a - b.a;
        e1 = this->e + b.e;
        l = a1 - e1;
        c = a1;
        r = a1 + e1;
        return *this;  
    }
     fazzynumber & operator *(const fazzynumber & b) {//функция умножения
        long double a1,e1,a1e2,a2e1;
        a1 = this->a * b.a;
        e1 = this->e * b.e;
        a1e2 = this->a * b.e;
        a2e1 = b.a * this->e;
        l = a1 - a1e2 - a2e1 + e1;
        c = a1;
        r = a1 + a1e2 + a2e1 + e1 ;
        return *this;
    }
     void oop(){//функция получения обратного числа
            l = 1/(this->a + this->e);
            c = 1/this->a;
            r = 1/(this->a - this->e);    
    }
    fazzynumber & operator /(const fazzynumber & b) {//функция деления
        l = (this->a - this->e)/(b.a + b.e);
        c = this->a/b.a;
        r = (this->a + this->e)/(b.a - b.e);
        return *this;
    }
    void print() {//функция печати нечеткого числа
        cout <<"(" << a - e << "," << a << "," << a + e << ")" << endl;
    }
    fazzynumber & operator >(const fazzynumber & b){//функция сравнения двух чисел по x
        if(this->a > b.a) {
            cout << "A(x) > B(x)" << endl;
        } else if (this->a < b.a) {
            cout << "A(x) < B(x)"<< endl;
        } else {
            cout << "A(x) = B(x)" << endl;
        }
        return *this;
    }
    long double getleft() {
        return l;
    }
    long double getright() {
        return r;
    }
    long double getcentre() {
        return c;
    }
    long double getx() {
        return a;
    }
};
fazzynumber operator ""_f(const char* str,size_t size);
fazzynumber operator ""_f(const char* str,size_t size) {
    size_t i = 0;
    long double r1,r2;
    string a,b;
        while(str[i] != ' ') {
            a = a + str[i];
            i++;
        }
        r1 = stold(a,0);
        i++;
        while(str[i] != '\0') {
            b = b  + str[i];
            i++;
        }
        r2 = stold(b,0);
        return fazzynumber(r1,r2);
}

int main() {
    char c;
    fazzynumber A = "2.12 3.5"_f;
    fazzynumber B = "1.0 2.5"_f;
    help();
    while (true) {
        cin >> c;
        switch (c) {//Свич меню.
            case 'a':
                A+B;//вызов функция сложения 
                cout <<"(" << A.getleft() << "," << A.getcentre() << "," << A.getright() << ")" << endl;
            break;
            case 'r':
                if (A.getx() > 0) {
                    A.oop();//вызов функции взятия обратного числа
                    cout <<"(" << A.getleft() << "," << A.getcentre() << "," << A.getright() << ")" << endl;
                }  else {
                    cout << "A(x) <= 0"<< endl;
                }
            break;
            case 'p':
                cout << "A = ";
                A.print();
                 cout << "B = ";
                 B.print();
            break;
            case 'd':
                if(B.getx() > 0) {
                    A/B;
                    cout <<"(" << A.getleft() << "," << A.getcentre() << "," << A.getright() << ")" << endl; 
                }  else {
                    cout << "B(x) <= 0"<< endl;
                }
            break;
            case 's':
                A-B;
                cout <<"(" << A.getleft() << "," << A.getcentre() << "," << A.getright() << ")" << endl;
            break;
            case 'm':
                A*B;
                cout <<"(" << A.getleft() << "," << A.getcentre() << "," << A.getright() << ")" << endl;
            break;
            case 'c':
                A>B;
            break;
            case 'h':
                help();
            break;
            case 'e':
                return 0;
            break;  
        }
    }
    return 0;
}
