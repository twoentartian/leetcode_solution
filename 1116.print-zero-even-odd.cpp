#include <iostream>
#include <thread>
#include <functional>
#include <atomic>
#include <mutex>
#include <condition_variable>
using namespace std;

class ZeroEvenOdd
{
private:
    int n;
    mutex mtx;
    condition_variable cv;
    int current_index = 0;
    std::atomic<bool> exit = false;

public:
    ZeroEvenOdd(int n)
    {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber)
    {
        while (true)
        {
            if (exit)
            {
                return;
            }
            unique_lock<mutex> ul(mtx);
            if (current_index % 4 != 0 && current_index % 4 != 2)
            {
                cv.wait(ul);
                continue;
            }
            else
            {
                printNumber(0);
                current_index++;
                if (current_index >= n * 2)
                {
                    exit = true;
                    cv.notify_all();
                    return;
                }
                else
                {
                    cv.notify_all();
                }
            }
        }
    }

    void even(function<void(int)> printNumber)
    {
        while (true)
        {
            if (exit)
            {
                return;
            }
            unique_lock<mutex> ul(mtx);
            if (current_index % 4 != 3)
            {
                cv.wait(ul);
                continue;
            }
            else
            {
                printNumber(current_index / 2 + 1);

                current_index++;
                if (current_index >= n * 2)
                {
                    exit = true;
                    cv.notify_all();
                    return;
                }
                else
                {
                    cv.notify_all();
                }
            }
        }
    }

    void odd(function<void(int)> printNumber)
    {

        while (true)
        {
            if (exit)
            {
                return;
            }
            unique_lock<mutex> ul(mtx);
            if (current_index % 4 != 1)
            {
                cv.wait(ul);
                continue;
            }
            else
            {
                printNumber(current_index / 2 + 1);

                current_index++;
                if (current_index >= n * 2)
                {
                    exit = true;
                    cv.notify_all();
                    return;
                }
                else
                {
                    cv.notify_all();
                }
            }
        }
    }
};

void printNumber(int i)
{
    std::cout << i;
}

int main()
{
    ZeroEvenOdd f(5);
    std::thread t1(&ZeroEvenOdd::zero, &f, printNumber);
    std::thread t2(&ZeroEvenOdd::even, &f, printNumber);
    std::thread t3(&ZeroEvenOdd::odd, &f, printNumber);

    t1.join();
    t2.join();
    t3.join();
}