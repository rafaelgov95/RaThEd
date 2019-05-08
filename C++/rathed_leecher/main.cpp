//
// Created by rafael on 03/05/19.
//

#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}

//#include <iostream>
//#include <future>
//#include <chrono>
//#include <util/util.h>
//
//static std::mutex cout_mutex;
//
//class Ticker
//{
//public:
//    // create but don't execute yet
//    Ticker(std::shared_future<void> f, std::chrono::milliseconds interval)
//            : interval{interval}, done{f}
//    { }
//    // run the thread
//    std::future<void> run() {
//        return std::async(std::launch::async, &Ticker::tickWrapper, this);
//    }
//private:
//    void tickWrapper() {
//        std::future_status status;
//        do {
//            status = done.wait_for(interval); // waits for the signal from main()
//            if (status == std::future_status::timeout) {
//                tickfunction();
//            }
//        } while (status != std::future_status::ready);
//    }
//    void tickfunction() {
//        std::lock_guard<std::mutex> lock(cout_mutex);
////        mySleep(10);
//        std::cout << "tick (" << std::this_thread::get_id() << ")" << std::endl;
//    }
//
//    const std::chrono::milliseconds interval;
//    std::shared_future<void> done;
//};
//int main()
//{
//    // for convenience in specifying time durations
//    using namespace std::chrono_literals;
//
//    // create a promise and associated shared_future
//    std::promise<void> done;
//    std::shared_future<void> done_future(done.get_future());
//
//    // create the Ticker objects
//    Ticker t1(done_future, 11ms);
////    Ticker t2(done_future, 500ms);
//
//    // start the threads
//    auto x = t1.run();
////    auto y = t2.run();
//
//    // delay for a while
//    std::this_thread::sleep_for(11ms);
//
//    // tell the other threads to stop
//    done.set_value();
//
//    std::cout << "Done\n";
//}