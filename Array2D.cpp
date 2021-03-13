#include <iostream>
#include <cstring>
#include <chrono>

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

    T& operator()(int row, int col) { return m_data[col + COLS*row]; }

    const T& operator()(int row, int col) const { return m_data[col + COLS*row]; }

    void print(){
        for(int i=0; i<ROWS*COLS; i++){
            if(i%COLS == 0)
                std::cout<<std::endl;
            std::cout<<m_data[i] << ", ";
        }
    }

    T* data() { return m_data; }

    T size() { return ROWS*COLS; }
};

int main()
{
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
