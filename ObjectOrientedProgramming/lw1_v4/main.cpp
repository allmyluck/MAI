#include "fazzynumber.h"

void help() {
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

int main() {
    double c1,ec;
    char c;
    cout << "A = ";
    cin >> c1;
    cout << "E(A) = ";
    cin >> ec;
    fazzynumber A(c1,ec);
    double d1,ed;
    cout << "B = ";
    cin >> d1;
    cout << "E(B) = ";
    cin >> ed;
    fazzynumber B(d1,ed);
    help();
    while (true) {
        cin >> c;
        switch (c) {
            case 'a':
                A.add(B); 
                cout <<"(" << A.getleft() << "," << A.getcentre() << "," << A.getright() << ")" << endl;
            break;
            case 'r':
                if (A.getx() > 0) {
                    A.opp();
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
                    A.div(B);
                    cout <<"(" << A.getleft() << "," << A.getcentre() << "," << A.getright() << ")" << endl; 
                }  else {
                    cout << "B(x) <= 0"<< endl;
                }
            break;
            case 's':
                A.sub(B);
                cout <<"(" << A.getleft() << "," << A.getcentre() << "," << A.getright() << ")" << endl;
            break;
            case 'm':
                A.mul(B);
                cout <<"(" << A.getleft() << "," << A.getcentre() << "," << A.getright() << ")" << endl;
            break;
            case 'c':
                A.comp(B);
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
