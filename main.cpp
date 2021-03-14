#include <iostream>
#include <cstring>
#include <chrono>
#include "Vector.h"
#include "Array2D.h"
#include "LinkedList.h"

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

int main()
{

    //Testing linked list
    Node<int>* head = new Node<int>(5);
    Node<int>* second = new Node<int>(10);
    Node<int>* third = new Node<int>(15);
    head->next = second;
    second->next = third;
    third->next = nullptr;

    Node<int>* dummy = head;
    while(dummy != nullptr){
        std::cout << dummy->val << std::endl;
        dummy = dummy->next;
     }

    //Created optimized 2D Array.
    Array2DOptimized<float, 2, 2> arr;
    arr(0,0) = 5;
    arr(0,1) = 6;
    arr(1,0) = 7;
    arr(1,1) = 8;

    //iterator for loop.
    for(Array2DOptimized<float, 2, 2>::Iterator it = arr.begin();
        it!= arr.end(); it++){
        std::cout << *it << std::endl;
    }

    //range based for loop.
    for(int val: arr)
        std::cout << val << std::endl;

    //The timer starts when consructed. And stops when destroyed. It is deleted in this scope.
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

    //Testing vector class. So far only push_back is created.
    Vector<my_int> a;
    a.push_back(my_int(1));
    a.push_back(my_int(1));
    a.push_back(my_int(1));
    */

    std::cin.get();

    return 0;
}
