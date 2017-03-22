//
// Created by Snytkine, Dmitri (CORP) on 3/22/17.
//

#ifndef ROUTER_MEASURE_H
#define ROUTER_MEASURE_H

#endif //ROUTER_MEASURE_H


#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>
#include <utility>

using namespace std;

template<typename TimeT = std::chrono::milliseconds>
struct measure {
    template<typename F, typename ...Args>
    static typename TimeT::rep execution(F &&func, Args &&... args) {
        auto start = std::chrono::steady_clock::now();
        std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
        auto duration = std::chrono::duration_cast<TimeT>
                (std::chrono::steady_clock::now() - start);
        return duration.count();
    }
};


typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

template<typename F, typename... Args>
double funcTime(F func, Args &&... args) {

    cout << "BEFORE std::forward " << endl;
    TimeVar t1 = timeNow();

    func(std::forward<Args>(args)...);

    return duration(timeNow() - t1);
}

