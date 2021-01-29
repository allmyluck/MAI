/*
Токарев Никита M8o-207Б-18,вариант 24
Реализовать программу, которая: 
1)Позволяет вводить с клавиатуры фигуры (с типом int в качестве параметра шаблона фигуры) и добавлять в коллекцию;
2)Позволяет удалять элемент из коллекции по номеру элемента;
3)Выводит на экран введенные фигуры и выводит на экран количество объектов, у которых площадь меньше заданной  c помощью std::for_each;
*/


#include "queue_octagon.hpp"
void help() {
    std::cout << "add = add figure" << std::endl;
    std::cout << "del = delete figure" << std::endl;
    std::cout << "size = size of queue" << std::endl;
    std::cout << "print_all = show all figures in queue" << std::endl;
    std::cout << "check_area = show amount of figures,which area is less than a given " << std::endl;
    std::cout << "exit = exit" << std::endl;
}


int main() {
    Queue<Octagon<double>> our;
    std::cout << std::fixed;
    std::cout.precision(3);// shows three elements after a floating point
    Octagon<double> o(2,2,4);
    std::string inf;
    help();
    while(std::cin >> inf) {
        if(inf == "add") {
            try {
                int a;
                double x,y,r;
                std::cout << "Your x y R: ";
                std::cin >> x >> y >> r;
                Octagon<double> o(x,y,r);
                std::cout << "Your position: ";
				std::cin >> a;
                Queue<Octagon<double>>::Iterator it(our.get_first());
                it = our.Find(a);
                it = our.Insert(it.show(),o);

			} catch (std::logic_error& err) {
				std::cout << err.what() << std::endl;
			}
        } else if (inf == "del") {
            try {
                int a;
                std::cout << "Your position: ";
				std::cin >> a;
                Queue<Octagon<double>>::Iterator it(our.get_first());
                it = our.Find(a);
                it = our.Erase(it.show());
			} catch (std::logic_error& err) {
				std::cout << err.what() << std::endl;
			}
        } else if (inf == "exit") {
            return 0;
        } else if(inf == "print_all") {
            std::for_each(our.begin(),our.end(),[](Octagon<double> o)
            {
                return information(o);
            });
        } else if(inf == "check_area") {
            double a;
            std::cout << "Area : ";
            std::cin >> a;
            int am = 0;
            std::for_each(our.begin(),our.end(),[a,&am](Octagon<double> o)
            {
                if(get_area(o)  <  a) {
                    am = am + 1;
                }
            });
            std::cout << "Amount : " << am << std::endl;
        } else if(inf == "size") {
            std::cout << our.get_size() << std::endl;
        }
    }
    return 0;
}