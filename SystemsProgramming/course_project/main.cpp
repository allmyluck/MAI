#include "src/CfreeG.hpp"
/*

Разработать КС-грамматику для строк, задающих множество отрезков на прямой.  
Например, { [1,2], (3, 5.1) } .
В отрезке отмечаются, входят ли границы. Для бесконечности предложить какой-либо знак.
Разработать класс на С++, описывающий такие множества. Должны быть методы
    1)проверка корректности: начало<=конец : есть(начало => конец)
    2)нормализация множества отрезков: отрезки не пересекаются и упорядочены по возрастанию (т.е. произвести операции объединения).

    1) Функция LLParsing(const std::string& str) является проверкой корректности
    2) для множества отрезков вызывается функция нормализации.
        Пример: {(100,300),[0,10],(20,300]} -> Normalize: {[0,10],(20,300]}

    // бесконечность: &;
    Кс-грамматика:
        S->{A
        A->[a,b]B|(a,b)B|[a,b)B|(a,b]B|};
        B->,A|}
*/

void PrintRules() {
    std::cout << "Context-free grammar" << std::endl;
    std::cout << "Infinity:&" << std::endl;
    std::cout << "long long int - type" << std::endl;
    std::cout << "S->{A" << std::endl;
    std::cout << "A->[a,b]B || (a,b)B ||[a,b)B || (a,b]B || }" << std::endl;
    std::cout << "B->,A || } " << std::endl;
}


void PrintMain() {
    std::cout << "Enter go:work" << std::endl;
    std::cout << "Enter end:exit" << std::endl;
    std::cout << "Enter help:help" << std::endl;
}


//  ConvertInString
int main() {
    std::string out;
    PrintRules();
    while(std::cin >> out) {
        if(out == "go") {
            try {
                std::string line;
                std::cin >> line;
                ContextFree* current = new ContextFree(line);
                current->CheckNormalize();
                delete current;
            } catch (std::logic_error& err) {
                std::cout << err.what() << std::endl;
            }
        } else if(out == "end") {
            break;
        } else if(out == "help") {
            PrintMain();
        }
    }    
    return 0;
}