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

    template<typename T>
    class RouterNode {


    public :

        RouterNode<T>(string uri, T *ctrl, string name = "") : origUriPattern(uri),
                                                               controller_name(name),
                                                               controller(ctrl) {
            cout << "CREATED NODE for uri=[" << uri << "] origUriPattern=[" << origUriPattern << "]" << endl;
        }


        RouterNode<T>() : origUriPattern("/"), controller_name("ROOT"), controller() {}

        RouterNode<T>(std::string uri) : origUriPattern(uri), controller() {}

        RouterNode<T> *createRouterNode(string nodeUri, T &id, string name);

        RouterNode<T> *createRouterNode(string nodeUri);

        virtual T *getController() const {
            return controller;
        }

        virtual string getParamName() const;

        void setController(T *ctrl) {
            controller = ctrl;
        }

        bool empty() const {
            return controller == nullptr;
        }

        virtual RouterNode<T> *addRoute(string uri, T &controller, string ctrl_name = "");

        virtual RouteResult<T> *findRoute(const string uri, paramsList *params = new paramsList()) const;

        ~RouterNode() {
            if (children.size() > 0) {
                //cout << " RouterNode " << origUriPattern << " destructor called " << endl; // never called?
                children.clear();
                delete controller;
            }
        }

        //virtual string rest(const string s) const;

    protected:
        T *controller;

        string controller_name;

        string origUriPattern;

        vector<RouterNode<T> *> children;

        // This is where the work is done to match uri for this node, possibly extract router params and
        // return a result.
        // result may contain controller_id in which case the result is found
        // or it may append extracted route params to params, generate the "restString" and return
        // result with params and restString, in which case children will be searched for a match for the restString
        virtual RouteResult<T> *getNodeResult(const string uri, paramsList *params = new paramsList()) const;



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
