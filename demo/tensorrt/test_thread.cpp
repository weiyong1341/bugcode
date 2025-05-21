// 主线程发送数据，子线程计算，并返回给主线程
// 子线程初始化，需要在主线程初始化之前完成
//

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <opencv2/opencv.hpp>
#include <random>
#include <future>

using namespace std;
using namespace cv;

queue<int> sharedQueue;
mutex mtx;
mutex mtx2;

condition_variable producer_cond;

condition_variable consumer_cond1;
condition_variable consumer_cond2;
condition_variable consumer_cond3;

int result1 = 0;
int result2 = 0;
int result3 = 0;

bool flag1 = false;
bool flag2 = false;
bool flag3 = false;

void thread1(){
    

    // while (true)
    for(int i=0; i<100; i++)
    {
        Mat img = cv::imread("dog.jpg");
        unique_lock<mutex> lock(mtx);

        // 处理数据
        cout << "准备数据：" << endl;

        flag1 = false;
        flag2 = false;
        flag3 = false;

        lock.unlock();
        
        consumer_cond1.notify_one();
        consumer_cond2.notify_one();
        consumer_cond3.notify_one();
        
        // 等待计算结束
        unique_lock<mutex> lock2(mtx2);
        producer_cond.wait(lock2, []{ return flag1 & flag2 & flag3; });
        std::cout << "result1: "  << result1 << " result2: "  << result2 << " result3: "  << result3 << std::endl;

    }
}

void thread2(promise<int>& promise){

    // 初始化
    this_thread::sleep_for(chrono::milliseconds(1000));
    promise.set_value(2);

    while (true)
    {
        unique_lock<mutex> lock(mtx);
        consumer_cond1.wait(lock);
        // 获取数据
        result1 = rand() % 100;
        lock.unlock();

        std::cout << "result1: " << result1 << std::endl;
        this_thread::sleep_for(chrono::milliseconds(result1));
        flag1 = true;
        producer_cond.notify_one();

    }
}

void thread3(promise<int>& promise){

    // 初始化
    this_thread::sleep_for(chrono::milliseconds(5000));
    promise.set_value(3);

    while (true)
    {
        unique_lock<mutex> lock(mtx);
        consumer_cond2.wait(lock);
        result2 = rand() % 100;
        lock.unlock();

        // 获取数据
        std::cout << "result2: " << result2 << std::endl;
        this_thread::sleep_for(chrono::milliseconds(result2));
        flag2 = true;
        producer_cond.notify_one();
    }
}

void thread4(promise<int>& promise){

    // 初始化
    this_thread::sleep_for(chrono::milliseconds(5000));
    promise.set_value(3);
    
    while (true)
    {
        unique_lock<mutex> lock(mtx);
        consumer_cond3.wait(lock);

        // 获取数据
        result3 = rand() % 100;
        lock.unlock();
        
        std::cout << "result3: " << result3 << std::endl;
        this_thread::sleep_for(chrono::milliseconds(result3));
        flag3 = true;

        producer_cond.notify_one();
    }
}


int main() {

    promise<int> promise1;
    promise<int> promise2;
    promise<int> promise3;
    future<int> future1 = promise1.get_future();
    future<int> future2 = promise2.get_future();
    future<int> future3 = promise3.get_future();

    std::thread t2(thread2, ref(promise1));
    std::thread t3(thread3, ref(promise2));
    std::thread t4(thread4, ref(promise3));

    future1.wait();
    future2.wait();
    future3.wait();
    std::cout << future1.get() << std::endl;
    std::cout << future2.get() << std::endl;
    std::cout << future3.get() << std::endl;


    std::thread t1(thread1);
    t1.join();

    t2.join();
    t3.join();
    t4.join();

    return 0;
}
