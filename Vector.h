#include <iostream>

template<typename T>
class Vector
{
private:
    size_t m_size = 0;
    size_t m_capacity = 0;
    T* m_data = nullptr;

    void realloc(size_t new_size){
        T* tmp = m_data;
        m_data = new T[new_size];

        for(size_t i=0; i<m_size; i++)
            m_data[i] = std::move(tmp[i]);

        m_capacity = new_size;
        delete[] tmp;
    }

public:
    Vector(){
        realloc(2);
    }

    ~Vector(){
        delete[] m_data;
    }

    void push_back(const T& val){
        if(m_capacity <= m_size)
            realloc(m_capacity*2);

        m_data[m_size++] = std::move(val);
    }

    void push_back(T&& val){
        if(m_capacity <= m_size)
            realloc(m_capacity*2);

        m_data[m_size++] = std::move(val);
    }

    int size(){
        return m_size;
    }

    T& operator[] (size_t idx){
        return m_data[idx];
    }

};

struct my_int {
    int x;

    my_int(){}
    my_int(int x) : x(x) {}

    my_int(const my_int& other) : x(other.x) { std::cout << "copied" << std::endl; }
    my_int(my_int&& other) : x(other.x) { std::cout << "moved" << std::endl; }
    my_int& operator=(const my_int& other) { std::cout << "copied" << std::endl; x = other.x; return *this; }
    my_int& operator=(my_int&& other) { std::cout << "moved" << std::endl; x = other.x; return *this; }

    ~my_int(){ std::cout << "destroyed" << std::endl; }
};
