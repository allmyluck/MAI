#ifndef QUEUE_OCTAGON_HPP
#define QUEUE_OCTAGON_HPP
#include <iostream>
#include <tuple>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <algorithm>

template <class T>
struct Octagon {
    using type = T;
    using vertex_t = std::pair<T,T>;
    vertex_t a;T R;
    Octagon(T x1, T y1, T R) : a(x1,y1), R(R)
    {
        if(R <= 0) {
            throw std::logic_error("always R > 0");
        }
    }
};

template <template <class> class F, class T>//get area for F<T> = Octagon<double>;
T get_area(F<T> o) {
    return 4 * sin(M_PI / 4) * o.R * o.R;
}

template <template <class> class F, class T> //show information about F<T> = Octagon<double>;
typename std::enable_if< std::is_same< F<T>, Octagon<T> >::value, F<T> >::type information(F<T> o) {
    std::cout << "Octagon" << std::endl;
    std::cout << "Area : " << get_area(o) << std::endl; 
    std::cout << "center point : "; 
    std::cout << "(" << o.a.first << "," << o.a.second << ")" << std::endl;
    T x,y,angle;
    for(int i = 0; i < 8;i++) {
        angle =  M_PI * i / 4;
        x = o.R * cos(angle) + o.a.first;
        y = o.R * sin(angle) + o.a.second;
        std::cout << "(" << x << "," << y << ")" << std::endl;
    }
    return o;
}



/* class queue with functions:Pop,Push,Pop,Insert(iterator,new_data),Erase(iterator),Find(position);
iterator in  function Insert(iterator,new_data) and function Erase(iterator) show position; 
*/
template <class T>
class Queue {
private:
    //part of Queue;
    struct Node {
        T data;
        std::shared_ptr<Node> next;//i use shared_ptr;
        Node(T d_t) : data(d_t), next(nullptr)
        {}
    };
    using ptr = std::shared_ptr<Node>;
    int size;//size of our queue
    ptr first;//first element in our queue
public:
    //Iterator for our queue with operators:++(),*,!=,==;
    class Iterator {
    private:
        ptr p_node;//our Node;
    public:
        Iterator(ptr it)
        {
            p_node = it;
        }

        ptr show() {
            return p_node;
        }

        
        bool operator == (const Iterator& other)
        {
            return (p_node == other.p_node);
        }


        bool operator != (const Iterator& other) 
        {
            return !(p_node == other.p_node);
        }


        T operator * () 
        {
                return p_node->data;
        }


        void operator ++ () 
        {
            if(p_node != nullptr) {
                p_node = p_node->next;
            } else {
                throw std::logic_error("This is last position");
            }
        }
    };

public:
    Queue() {
        size = 0;
        first = nullptr;
    }


    void Push(T new_dt) {
        if(size == 0) {
            first =  std::make_shared<Node>(new_dt);
        } else {
            ptr temp = first;
            while(temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = std::make_shared<Node>(new_dt);
        }
        size++;
    }


    void Pop() {
        if(size == 0) {
            throw std::logic_error("Queue is empty");
        } 
        first = first->next;
        size--;
    }


    ptr Top() {
        if(size == 0) {
           throw std::logic_error("Queue is empty"); 
        }
        return first;
    }


    ptr get_first() {
        return first;
    }

    int get_size() {
        return size;
    }

    Iterator begin() {
        return Iterator(first);
    }


    Iterator end() {
        return Iterator(nullptr);
    }


    Iterator Insert(ptr temp, T new_dt) {
        ptr time = first;
        ptr new_node;
        if(time == temp) {
            new_node = std::make_shared<Node>(new_dt);
            new_node->next = first;
            first = new_node;
        } else {
            while(time->next != temp) {
                time = time->next;
            }
            new_node = std::make_shared<Node>(new_dt);
            time->next = new_node;
            new_node->next = temp;
        }
        size++;
        return Iterator(new_node);
    }


    Iterator Find(int n) {
        if(n == size) {
            return Iterator(nullptr);
        }
        if(n >= size || n < 0) {
            throw std::logic_error("Element on this position was not found");
        }
        int i = 0;
        ptr time = first;
        while(i != n) {
            time = time->next;
            i++;
        }
        return Iterator(time);
    }


    Iterator Erase(ptr temp) {
        if(size == 0 || temp == nullptr) {
            throw std::logic_error("Element on this position was not found"); 
        }
        ptr time = first;
        if(time == temp) {
            first = first->next;
        } else {
            while(time->next != temp) {
                time = time->next;
            }
            time->next = temp->next;
        }
        size--;
        return Iterator(time->next);
    }    
};


#endif