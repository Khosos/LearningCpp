#include <iostream>
#include <type_traits>

class Array2D{

private:
    int numRows, numCols;
    int** data;

public:
    Array2D(int row, int col)
        :numRows(row), numCols(col)
    {
        data = new int*[numRows];
        for(int i=0; i<numRows; i++){
            data[i] = new int[numCols];
        }
    }

    ~Array2D(){
        std::cout << "deleted array" << std::endl;
        for(int i=0; i<numRows; i++){
            delete[] data[i];
        }
        delete[] data;
    }

    void insert(int row, int col, int val){
        data[row][col] = val;
    }

    int get(int row, int col){
        return data[row][col];
    }

    void print(){
        for(int i=0; i<numRows; i++){
            for(int j=0; j<numCols; j++){
                std::cout << data[i][j] << ", ";
            }
            std::cout << std::endl;
        }
    }
};

template <typename T, int ROWS, int COLS>
class Array2DOptimized {
private:
    T* data;

public:
    Array2DOptimized()
    {
        data = new T[ROWS*COLS];
    }

    T& operator()(int row, int col) const {
        return data[col + COLS*row];
    }

    ~Array2DOptimized(){
        std::cout << "deleted array" << std::endl;
        delete[] data;
    }

    void print(){
        for(int i=0; i<ROWS*COLS; i++){
            if(i%COLS == 0)
                std::cout<<std::endl;
            std::cout<<data[i] << ", ";
        }
    }
};

int main()
{
    Array2DOptimized<float, 5, 3> myArr;
    myArr(0,0) = 1.5;
    myArr(0,1) = 2.3;
    myArr.print();

    return 0;
}
