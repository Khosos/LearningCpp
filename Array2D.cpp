#include <iostream>
#include <cstring>
#include <chrono>

//Timer class. When created the timer starts. The timer stops when destroyed.
class Timer
{
public:
    Timer()
    {
        m_StartTimePoint = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        Stop();
    }

    void Stop()
    {
        auto endTimePoint = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
        auto stop = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
        auto duration = stop - start;
        auto duration_ms = duration*0.001;
        std::cout << duration << "us " << duration_ms << "ms" << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
};

//Iterator for our Array class.
template<typename  T>
class ArrayIterator
{
public:
    using ValueType = T;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;
public:
    ArrayIterator(PointerType ptr)
        : m_Ptr(ptr){}

    ArrayIterator& operator++(){
        *m_Ptr++;
        return *this;
    }

    ArrayIterator operator++(int){
        ArrayIterator it = *this;
        ++(*this);
        return it;
    }

    ReferenceType operator[](int index){
        return *(m_Ptr + index);
    }

    PointerType operator->(){
        return m_Ptr;
    }

    ReferenceType operator*(){
        return *m_Ptr;
    }

    bool operator==(const ArrayIterator& other) const {
        return m_Ptr == other.m_Ptr;
    }

    bool operator!=(const ArrayIterator& other) const {
        return !(*this == other);
    }

private:
    PointerType m_Ptr;
};

//Also a 2D array class using double pointers. The data is allocated on the heap using the new keyword.
template <typename T>
class Array2D{
private:
    int numRows, numCols;
    T** m_data;

public:
    Array2D(int row, int col)
        :numRows(row), numCols(col)
    {
        m_data = new T*[numRows];
        for(int i=0; i<numRows; i++){
            m_data[i] = new int[numCols];
        }
    }

    ~Array2D(){
        //std::cout << "deleted array" << std::endl;
        for(int i=0; i<numRows; i++){
            delete[] m_data[i];
        }
        delete[] m_data;
    }

    void insert(int row, int col, int val){
        m_data[row][col] = val;
    }

    int get(int row, int col){
        return m_data[row][col];
    }

    void print(){
        for(int i=0; i<numRows; i++){
            for(int j=0; j<numCols; j++){
                std::cout << m_data[i][j] << ", ";
            }
            std::cout << std::endl;
        }
    }
};

//Templated Array class. The array containing the data is stored on the stack.
template <typename T, int ROWS, int COLS>
class Array2DOptimized {
private:
    int m_size = ROWS*COLS;
    T m_data[ROWS*COLS];

public:
    using ValueType = T;
    using Iterator = ArrayIterator<T>;

public:

    T& operator()(int row, int col) { return m_data[col + COLS*row]; }

    const T& operator()(int row, int col) const { return m_data[col + COLS*row]; }

    Iterator begin()
    {
        return Iterator(m_data);
    }

    Iterator end()
    {
        return Iterator(m_data + m_size);
    }

    T* data() { return m_data; }

    T size() { return ROWS*COLS; }

    void print(){
        for(int i=0; i<ROWS*COLS; i++){
            if(i%COLS == 0)
                std::cout<<std::endl;
            std::cout<<m_data[i] << ", ";
        }
    }
};

int main()
{
    Array2DOptimized<int, 2, 2> arr;
    arr(0,0) = 5;
    arr(0,1) = 6;
    arr(1,0) = 7;
    arr(1,1) = 8;

    //iterator for loop.
    for(Array2DOptimized<int, 2, 2>::Iterator it = arr.begin();
        it!= arr.end(); it++){
        std::cout << *it << std::endl;
    }

    //range based for loop.
    for(int val: arr)
        std::cout << val << std::endl;

    {
        Timer timer;
        for(int i=0; i<1000000; i++)
        {
            Array2D<int> arr(100,100);
        }
    }

    {
        Timer timer;
        for(int i=0; i<1000000; i++)
        {
            Array2DOptimized<int, 100, 100> arr;
        }
    }

    return 0;
}
