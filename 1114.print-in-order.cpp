/*
 * @lc app=leetcode id=1114 lang=cpp
 *
 * [1114] Print in Order
 */

#include <iostream>
#include <thread>
#include <functional>
#include <atomic>
#include <mutex>
#include <condition_variable>

// using namespace std;
// // @lc code=start
// class Foo {
// public:
//     std::atomic_int i;

//     Foo() {
//         i=0;
//     }

//     void first(function<void()> printFirst) {
//         // printFirst() outputs "first". Do not change or remove this line.
//         printFirst();
//         i++;
//     }

//     void second(function<void()> printSecond) {
//         while (i!=1);

//         // printSecond() outputs "second". Do not change or remove this line.
//         printSecond();
//         i++;
//     }

//     void third(function<void()> printThird) {
//         while (i!=2);

//         // printThird() outputs "third". Do not change or remove this line.
//         printThird();
//     }
// };
// // @lc code=end

using namespace std;
// @lc code=start
class Foo
{
public:

    std::mutex lock;
    std::condition_variable cv;
    uint8_t i = 0;
    Foo()
    {
    }

    void first(function<void()> printFirst)
    {
        std::unique_lock<std::mutex> lck(lock);
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        i++;
        cv.notify_all();
    }

    void second(function<void()> printSecond)
    {
        std::unique_lock<std::mutex> lck(lock);
        while (i != 1)
        {
            cv.wait(lck);
        }
        // printSecond() outputs "second". Do not change or remove this line.

        printSecond();
        i++;
        cv.notify_all();
    }

    void third(function<void()> printThird)
    {
        std::unique_lock<std::mutex> lck(lock);
        while (i != 2)
        {
            cv.wait(lck);
        }

        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};
// @lc code=end

void func1()
{
    std::cout << "first";
}

void func2()
{
    std::cout << "second";
}

void func3()
{
    std::cout << "third";
}

int main()
{
    Foo fo;
    thread thread_pool[3];
    thread t1(&Foo::first, &fo, func1);
    thread_pool[0].swap(t1);
    thread t2(&Foo::second, &fo, func2);
    thread_pool[1].swap(t2);
    thread t3(&Foo::third, &fo, func3);
    thread_pool[2].swap(t3);

    for(int i = 0; i < 3; i++)
    {
        thread_pool[i].join();
    }
}