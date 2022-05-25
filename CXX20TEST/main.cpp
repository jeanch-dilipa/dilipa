#include <QCoreApplication>

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    return a.exec();
//}

//#include <iostream>
//#include <pthread.h>

//const int PTHREAD_NUM = 5;

//void *Do(void* args)
//{
//    int id = *((int *)args);
//    std::cout << __TIME__ << "  " << id << std::endl;
//    pthread_exit(nullptr);
//    return 0;
//}

///*
//连接和分离线程
//pthread_join (threadid, status)
//pthread_detach (threadid)
//*/

//int main()
//{
//    pthread_t tid[PTHREAD_NUM];

//    for(int i = 0; i < PTHREAD_NUM; i++)
//    {
//        int ret = pthread_create(&tid[i],nullptr,Do,(void*)&i);
//        if(false != ret)
//        {
//            std::cout << "failure";
//        }
//    }

//    pthread_exit(nullptr);
//}


//#include <iostream>
//#include <csignal>
//#include <unistd.h>

//void signalHandler(int signalint)
//{
//    exit(signalint);
//}

///*
//c++自己的信号处理机制
//sigabrt---异常终止
//sigfpe----浮点数溢出
//sigill----异常指令
//sigint----交互指令
//sigegv----内存非法访问
//sigerm----终止请求
//*/

//int main()
//{
//    signal(SIGINT,signalHandler);

//    int i = 1;

//    while(i)
//    {
//        i++;
//        if(20 == i)
//        {
//            raise(SIGINT);
//        }
//        std::cout << i;
//    }
//}



//#include <iostream>
//#include <chrono>
//#include <algorithm>

//class Timer
//{
//public:
//    using clock_type = std::chrono::steady_clock;
//    using secound_type = std::chrono::duration<double,std::ratio<1>>;

//    std::chrono::time_point<clock_type> m_seg;

//    Timer():m_seg{clock_type::now()}{}
//    void reset(){m_seg = clock_type::now();}
//    double elapsed() const
//    {
//        return std::chrono::duration_cast<secound_type>(clock_type::now() - m_seg).count();
//    }
//};

//int main()
//{
//    Timer time;
//    std::cout << time.elapsed() << "\n";

//    std::array<int,10000> m_array;
//    std::iota(m_array.begin(),m_array.end(),1);
//    time.reset();

//    std::sort(m_array.begin(),m_array.end());
//    std::cout << time.elapsed() << "\n";

//    assert(false);

//    return 0;
//}


//#include <iostream>
//#include <cstdarg> // needed to use ellipsis

//// The ellipsis must be the last parameter
//// count is how many additional arguments we're passing
//double findAverage(int count, ...)
//{
//    double sum{ 0 };

//    // We access the ellipsis through a va_list, so let's declare one
//    va_list list;

//    // We initialize the va_list using va_start.  The first parameter is
//    // the list to initialize.  The second parameter is the last non-ellipsis
//    // parameter.
//    va_start(list, count);

//    // Loop through all the ellipsis arguments
//    for (int arg{ 0 }; arg < count; ++arg)
//    {
//         // We use va_arg to get parameters out of our ellipsis
//         // The first parameter is the va_list we're using
//         // The second parameter is the type of the parameter
//         sum += va_arg(list, int);
//    }

//    // Cleanup the va_list when we're done.
//    va_end(list);

//    return sum / count;
//}

//int main()
//{
//    std::cout << findAverage(5, 1, 2, 3, 4, 5) << '\n';
//    std::cout << findAverage(6, 1, 2, 3, 4, 5, 6) << '\n';
//斐波那契数列的lambda求解方式
//std::function<int(int)> lfib = [&lfib](int n) {return n < 2 ? 1 : lfib(n-1) + lfib(n-2);};
//}




//#include <iostream>
//#include <vector>

//// h/t to potterman28wxcv for a variant of this code
//int fibonacci(int count)
//{
//    // We'll use a static std::vector to cache calculated results
//    static std::vector<int> results{ 0, 1 };

//    // If we've already seen this count, then use the cache'd result
//    if (count < static_cast<int>(std::size(results)))
//        return results[count];
//    else
//    {
//        // Otherwise calculate the new result and add it
//        results.push_back(fibonacci(count - 1) + fibonacci(count - 2));
//        return results[count];
//    }
//}

//// And a main program to display the first 13 Fibonacci numbers
//int main()
//{
//    for (int count { 0 }; count < 13; ++count)
//        std::cout << fibonacci(count) << " ";

//    return 0;
//}






//#include <array>
//#include <iostream>
//#include <string_view>
//#include <tuple>
//#include <type_traits>

//namespace a::b::c
//{
//    inline constexpr std::string_view str{ "hello" };
//}

//template <class... T>
//std::tuple<std::size_t, std::common_type_t<T...>> sum(T... args)
//{
//    return { sizeof...(T), (args + ...) };
//}

//int main()
//{
//    auto [iNumbers, iSum]{ sum(1, 2, 3) };
//    std::cout << a::b::c::str << ' ' << iNumbers << ' ' << iSum << '\n';

//    std::array arr{ 1, 2, 3 };

//    std::cout << std::size(arr) << '\n';

//    quint8 a;
//    std::uint8_t b;

//    std::cout <<"quint8:"<<sizeof (a)<<"std::uint8_t:"<<sizeof(b)<<"\n";

//    return 0;
//}
