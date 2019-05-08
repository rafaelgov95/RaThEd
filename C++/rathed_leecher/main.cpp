//
// Created by rafael on 03/05/19.
//

#include "widget.h"
#include <QApplication>
#include <util/Temporizador.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}

//int main()
//{
//    // for convenience in specifying time durations
//    using namespace std::chrono_literals;
//    // create a promise and associated shared_future
//    std::promise<void> done;
//    std::shared_future<void> done_future(done.get_future());
//    Temporizador *t1;
//
//    std::cout << "Temp Inicial: "<<MyTempMS()<<std::endl;
//
//    t1= new Temporizador(done_future,11ms);
//    auto x = t1->run();
//
//    // delay for a while
//    std::this_thread::sleep_for(11ms);
//
//    // tell the other threads to stop
//    done.set_value();
//    std::cout << "Temp FIM: "<<MyTempMS()<<std::endl;
//
//    std::cout << "Done\n";
//}