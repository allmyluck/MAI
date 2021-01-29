/* Токарев Никита Станиславович М8о-107Б-18
Разработать классы согласно варианту задания, классы должны наследоваться от базового класса Figure. Фигуры являются фигурами вращения. Все классы должны поддерживать набор общих методов:
1.       Вычисление геометрического центра фигуры;
2.       Вывод в стандартный поток вывода std::cout координат вершин фигуры; 3. Вычисление площади фигуры;
Фигуры: восьмиугольник, треугольник, квадрат.
Создать программу, которая позволяет:
•       Вводить из стандартного ввода std::cin фигуры, согласно варианту задания.
•       Сохранять созданные фигуры в динамический массив std::vector<Figure*>
•       Вызывать для всего массива общие функции (1-3 см. выше).Т.е. распечатывать для каждой фигуры в массиве геометрический центр, координаты вершин и площадь.
•       Необходимо уметь вычислять общую площадь фигур в массиве.
•       Удалять из массива фигуру по индексу;
*/


#include "source/point_figure.hpp"
#include "source/octagon.hpp"
#include "source/square.hpp"
#include "source/triangle.hpp"

void help() {
    std::cout << "add = add figure" << std::endl;
    std::cout << "delete = delete figure" << std::endl;
    std::cout << "print = show information about figure" << std::endl;
    std::cout << "print_all = show information about all figures" << std::endl;
    std::cout << "size = the size of our array of figures" << std::endl;
    std::cout << "all_area = the sum area of all figures" << std::endl;
    std::cout << "exit = exit" << std::endl;
}

void simple_add(std::vector<Figure*>& figures) {
    std::cout << "Press t to add triangle, o to add octagon, s to add square" << std::endl;
    std::string inf;
    Triangle *t = nullptr;
    Square *s = nullptr;
    Octagon *o = nullptr;
    std::cin >> inf;
    if (inf == "t") {
        std::cout << "Please, your coordinates of three vertices" << std::endl;
        double x1,y1, x2, y2, x3, y3;
        std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        Point p1(x1,y1),p2(x2,y2), p3(x3,y3);
        try {
				t = new Triangle(p1,p2,p3);
                figures.push_back(dynamic_cast<Figure*>(t));
			} catch (std::logic_error& err) {
                delete t;
				std::cout << err.what() << std::endl;
			}
    } else if (inf == "s") {
        std::cout << "Please, your coordinates of opposite vertices" << std::endl;
        double x1,y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        Point p1(x1,y1),p2(x2,y2);
        try {
				s = new Square(p1,p2);
                figures.push_back(dynamic_cast<Figure*>(s));
			} catch (std::logic_error& err) {
                delete s;
				std::cout << err.what() << std::endl;
			}
    } else if (inf == "o") {
        std::cout << "Please, your center coordinate and circle radius" << std::endl;
        double x1,y1,R;
        std::cin >> x1 >> y1 >> R;
        Point p(x1,y1);
        try {
				o = new Octagon(p,R);
                figures.push_back(dynamic_cast<Figure*>(o));
			} catch (std::logic_error& err) {
                delete o;
				std::cout << err.what() << std::endl;
			}
    }
}

std::vector<Figure*> delete_el(std::vector<Figure*>& figures, int del) {
    int i = 0;
    std::vector<Figure*> n_figures;
    while(i < figures.size()) {
        if(i != del) {
            n_figures.push_back(figures[i]);
        }
        i++;
    }
    figures.clear();
    return n_figures;   
}


int main() {
    std::cout << std::fixed;
    std::cout.precision(3);
    std::vector<Figure*> figures;
    std::string data;
    int i;
    help();
    while(std::cin >> data) {
        if(data == "add") {
            simple_add(figures);
        } else if(data == "delete") { 
            std::cout << "Index = ";
            std::cin >> i;
            if(i < 0 || i >= figures.size()) {
                std::cout << "Error" << std::endl;
            } else {
               delete figures[i];
               figures = delete_el(figures, i);
            }
        } else  if(data == "print") {
            std::cout << "Index : ";
            std::cin >> i;
            if(i < 0 || i >= figures.size()) {
                std::cout << "Error" << std::endl;
            } else {
                figures[i]->output();
                 std::cout << "center ";
                figures[i]->get_centre().P_output();
                std::cout << "Area : " << figures[i]->get_area() << std::endl;
            }
        } else if(data == "print_all") {
            for(int j = 0; j < figures.size(); j++) {
                std::cout << j << "-st figure" << std::endl;
                figures[j]->output();
                std::cout << "center ";
                figures[j]->get_centre().P_output();
                std::cout << "Area : " << figures[j]->get_area() << std::endl;
            }
        } else if(data == "size") {
            std::cout << figures.size() << std::endl;
        } else if(data == "all_area") {
            double b = 0;
            for(int j = 0; j < figures.size(); j++) {
                b = b + figures[j]->get_area();
            }
            std:: cout << "Area of all fiqures : " << b << std::endl;
        } else if(data == "exit") {
            for(int j = 0; j < figures.size(); j++) {
                delete figures[j];
            }
            return 0;
        }
    }
    return 0;
}
