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
#include "constants.h"


namespace router_lib {

    template<class T>
    class RouterNode {

    public :

        RouterNode<T>(std::string uri, T *ctrl, std::string name = "") : origUriPattern(uri),
                                                                         controller_name(name),
                                                                         controller(ctrl) {
            init(uri);
            //cout << "CREATED NODE for uri=[" << uri << "] origUriPattern=[" << origUriPattern << "]" << endl;
        }


        RouterNode<T>() : origUriPattern("/"), controller_name("ROOT"), controller(), nodeType_(NodeType::BasicNode) {}

        RouterNode<T>(std::string uri) : origUriPattern(uri), controller() {
            init(uri);
        }

        T *getController() const;

        //void setController(T *ctrl);

        bool empty() const;

        virtual void *addRoute(std::string uri, T &controller, const std::string ctrl_name = "");

        virtual RouteResult<T> *findRoute(const std::string uri, paramsList *params = new paramsList());

        ~RouterNode<T>() {
            if (children.size() > 0) {
                //cout << " RouterNode " << origUriPattern << " destructor called " << endl; // never called?
                children.clear();
            }
        }

    protected:

        NodeType nodeType_ = NodeType::BasicNode;

        T *controller;

        std::string controller_name;

        std::string origUriPattern;

        std::vector<RouterNode<T> *> children;

        bool END_WITH_SLASH;

        std::string paramName_;

        std::string prefix;

        void init(std::string uri);

        size_t startPos;

        // This is where the work is done to match uri for this node, possibly extract router params and
        // return a result.
        // result may contain controller_id in which case the result is found
        // or it may append extracted route params to params, generate the "restString" and return
        // result with params and restString, in which case children will be searched for a match for the restString
        RouteResult<T> *getNodeResult(const std::string uri, paramsList *params = new paramsList());

        RouteResult<T> *getParamNodeResult(const std::string uri, paramsList *params = new paramsList());

        RouteResult<T> *getFuncNodeResult(const std::string uri, paramsList *params = new paramsList());

    };

    template class RouterNode<int>;
}
#endif //ROUTER_ROUTER_NODE_H
