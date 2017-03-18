//
// Created by Snytkine, Dmitri (CORP) on 3/14/17.
//

#include "RouterNode.h"
#include "strlib.h"

namespace router_lib {

    template<typename T>
    string RouterNode<T>::rest(const string s) {
        return s.substr(uri_.length());
    }

    template<class T>
    RouteResult<T> *RouterNode<T>::getNodeResult(string s, paramsList *params) {

        RouteResult<T> *res = new RouteResult<T>(params);

        if (s == uri_) {
            res->controller_id = controller;
            return res;
        } else if (startsWith(s, uri_)) {
            // set the restString value and return
            res->restString = rest(s);
            return res;
        } else {
            // Not exact match and no children or search uri is NOT substring of uri_
            std::cout << " RouterNode::getNodeResult returning nullptr " << endl;
            res->isEmpty = true;

            std::cout << " RouterNode::getNodeResult result isEmpty: " << res->isEmpty << endl;
            return res;

        }
    }


    template<typename T>
    RouteParam *RouterNode<T>::extractParam() {
        return nullptr;
    }

    template<class T>
    RouteResult<T> *RouterNode<T>::findRoute(string s, paramsList *params) {

        //std::cout << " Entered  RouterNode::findRoute Node: " << uri_ << " looking for: " << s << endl;
        RouteResult<T> *res = getNodeResult(s, params);
        //std::cout << " RouteResult controller_id " << res->controller_id << " restString: " << res->restString << endl;

        if (res->isEmpty == true) {
            std::cout << " RouterNode::findRoute Result isEmpty:" << res->isEmpty << endl;
            return res;
        } else if (res->restString.length() == 0) {
            std::cout << " RouterNode::findRoute Result found. controller_id:" << res->controller_id << endl;
            return res;
        } else if (children.size() > 0) {
            for (auto &&i : children) {
                std::cout << " Looking in Child for " << res->restString << endl;
                auto cres = i->findRoute(res->restString, params);
                if (!cres->isEmpty && cres->restString.length() == 0) {
                    return cres;
                }
            }
        }


        return new RouteResult<T>(params);
    }

    template<class T>
    RouterNode<T> *RouterNode<T>::addChild(string uri, T id) {
        RouterNode<T> *child = new RouterNode<T>(uri, id, "OK");
        children.push_back(child);
        return child;
    }


    template<class T>
    RouterNode<T> *RouterNode<T>::addRoute(string uri, T id, string name) {

    }

}