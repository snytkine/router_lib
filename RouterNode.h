//
// Created by Snytkine, Dmitri (CORP) on 3/14/17.
//

#ifndef ROUTER_ROUTER_NODE_H
#define ROUTER_ROUTER_NODE_H


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
    TimeVar t1 = timeNow();
    func(std::forward<Args>(args)...);
    return duration(timeNow() - t1);
}

class RouteParam {

public:
    const string name;
    const string val;

    RouteParam(const string nn, const string vv) : name(nn), val(vv) {}
};

typedef vector<RouteParam *> paramsList;

template <typename T>
class RouteResult {

public:
    bool isEmpty;
    paramsList *params;
    T controller_id;
    string restString = "";
    RouteResult(){}
    RouteResult(paramsList *p, T cid = 0, string rest = "", bool empty = false) : restString(rest), isEmpty(empty) {
        params = p;
        controller_id = cid;
    }

    ~RouteResult<T>() {
        if (params != nullptr) {
            cout << " RouteResult destructor has params " << endl;
            params->clear();
            params = nullptr;
        } else {
            //cout << " RouteResult destructor has NO params " << endl;
        }
    };
};

template class RouteResult<int>;


template <typename T>
class RouterNode {

protected:

    string uri_;

    string originalUriPattern;

    T controller;

    vector<RouterNode<T> *> children;

    // This is where the work is done to match uri for this node, possibly extract router params and
    // return a result.
    // result may contain controller_id in which case the result is found
    // or it may append extracted route params to params, generate the "restString" and return
    // result with params and restString, in which case children will be searched for a match for the restString
    virtual RouteResult<T> *getNodeResult(string uri, paramsList *params = new paramsList());

public :
    RouterNode<T>(std::string uri, T id) : uri_(uri) {
        controller = id;
    }

    virtual RouterNode<T> *addChild(string uri, T id);

    virtual RouteResult<T> *findRoute(string uri, paramsList *params = new paramsList());

    ~RouterNode() {
        if (children.size() > 0) {
            cout << " RouterNode " << uri_ << " destructor called " << endl; // never called?
            children.clear();
        }


    }

};

template class RouterNode<int>;
#endif //ROUTER_ROUTER_NODE_H
