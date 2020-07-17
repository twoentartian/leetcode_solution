#include <iostream>
#include <thread>
#include <functional>
#include <atomic>
#include <mutex>
#include <condition_variable>
using namespace std;


class FooBar {
private:
    int n;
    mutex mtx;

public:
    atomic<uint8_t> v = 0;
    condition_variable cv;

    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            std::unique_lock<mutex> uc(mtx);
            while(v != 0)
            {
                cv.wait(uc);
            }
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            v = 1;
            cv.notify_all();
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            std::unique_lock<mutex> uc(mtx);
            while(v != 1)
            {
                cv.wait(uc);
            }
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            v = 0;
            cv.notify_all();
        }
    }
};

void printFoo()
{
    std::cout << "Foo";
}

void printBar()
{
    std::cout << "bar";
}

int main()
{
    FooBar f(5);
    std::thread t1(&FooBar::foo, &f, printFoo);
    std::thread t2(&FooBar::bar, &f, printBar);

    t1.join();
    t2.join();
}