#include <QCoreApplication>
#include <iostream>
//#include <csignal>
#include <unistd.h>
#include <pthread.h>

namespace dealSignal
{
    void SIGINTCMD(const int signum)
    {
        std::cout << "signum: " << signum << std::endl;
        exit(signum);
    }
}

//namespace dealPthread
//{
//    void* sayHello(void* args)
//    {
//        Q_UNUSED(args);
//        std::cout << "hello" << *((int*)args) << std::endl;
//        return 0;
//    }
//}

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);

//    return a.exec();
    Q_UNUSED(argc);
    Q_UNUSED(argv);

//    pthread_t tid[5];
//    for(int i = 0; i < 5; i++)
//    {
//        int ret = pthread_create(&tid[i], nullptr, dealPthread::sayHello, (void*)i);
//        if(0 != ret)
//        {
//            std::cout << "create pthread err!" << std::endl;
//        }
//    }
//    pthread_exit(nullptr);

    signal(SIGINT, dealSignal::SIGINTCMD);
    while (1)
    {
        std::cout << "1" << std::endl;
        sleep(1);
        raise(SIGINT);
    }
}
