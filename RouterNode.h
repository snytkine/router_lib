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

    class RouterNode {


    public :

        RouterNode(std::string uri, void *ctrl, std::string name = "") : origUriPattern(uri),
                                                               controller_name(name),
                                                               controller(ctrl) {
            //cout << "CREATED NODE for uri=[" << uri << "] origUriPattern=[" << origUriPattern << "]" << endl;
        }


        RouterNode() : origUriPattern("/"), controller_name("ROOT"), controller() {}

        RouterNode(std::string uri) : origUriPattern(uri), controller() {}

        virtual void *getController() const;

        void setController(void *ctrl);

        bool empty() const;

        virtual RouterNode *addRoute(std::string uri, void *controller, const std::string ctrl_name = "");

        virtual RouteResult *findRoute(const std::string uri, paramsList *params = new paramsList()) const;

        ~RouterNode() {
            if (children.size() > 0) {
                //cout << " RouterNode " << origUriPattern << " destructor called " << endl; // never called?
                children.clear();
            }
        }

    protected:
        void *controller;

        std::string controller_name;

        std::string origUriPattern;

        std::vector<RouterNode *> children;

        // This is where the work is done to match uri for this node, possibly extract router params and
        // return a result.
        // result may contain controller_id in which case the result is found
        // or it may append extracted route params to params, generate the "restString" and return
        // result with params and restString, in which case children will be searched for a match for the restString
        virtual RouteResult *getNodeResult(const std::string uri, paramsList *params = new paramsList()) const;

    };

}
#endif //ROUTER_ROUTER_NODE_H
