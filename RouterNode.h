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
#include "node_result.h"


namespace router_lib {
    using namespace std;

    static const string PATH_SEPARATOR = "/";
    static const string PLACEHOLDER_START = "{";
    static const string PLACEHOLDER_END = "}";



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



    template<typename T>
    class RouterNode {


    public :

        RouterNode<T>(string uri, T* ctrl, string name = "") : origUriPattern(uri),
                                                                                     controller_name(name),
                                                                                     controller(ctrl) {
            cout << "CREATED NODE for uri=[" << uri << "] origUriPattern=[" << origUriPattern << "]" << endl;
        }


        RouterNode<T>() : origUriPattern("/"), controller_name("ROOT") {}

        RouterNode<T>(std::string uri) : origUriPattern(uri) {}

        RouterNode<T> *createRouterNode(string nodeUri, T &id, string name);

        RouterNode<T> *createRouterNode(string nodeUri);

        virtual T* getController(){
            return controller;
        }

        virtual string getParamName(){
            return "";
        }

        void setController(T* ctrl){
            controller = ctrl;
        }

        bool empty(){
            return controller == nullptr;
        }

        virtual RouterNode<T> *addRoute(string uri, T &controller, string ctrl_name = "");

        virtual RouteResult<T> *findRoute(string uri, paramsList *params = new paramsList());

        ~RouterNode() {
            if (children.size() > 0) {
                cout << " RouterNode " << origUriPattern << " destructor called " << endl; // never called?
                children.clear();
            }
        }


    protected:
        T* controller = nullptr;

        string controller_name;

        string origUriPattern;

        vector<RouterNode<T> *> children;

        // This is where the work is done to match uri for this node, possibly extract router params and
        // return a result.
        // result may contain controller_id in which case the result is found
        // or it may append extracted route params to params, generate the "restString" and return
        // result with params and restString, in which case children will be searched for a match for the restString
        virtual RouteResult<T> *getNodeResult(string uri, paramsList *params = new paramsList());

        virtual string rest(const string s);

    };


    //template
    //class RouterNode<int>;


    //template<typename T>
    //RouterNode<T>* createRouterNode(string nodeUri, T id, string name);

    //template
    //RouterNode<int>* createRouterNode(string nodeUri, int id, string name);

    //template <typename T>
    //RouterNode<T>* emptyNode();

}
#endif //ROUTER_ROUTER_NODE_H
