//
// Created by Snytkine, Dmitri (CORP) on 3/14/17.
//

#include "RouterNode.h"
#include "strlib.h"

template <class T>
RouteResult<T> *RouterNode<T>::getNodeResult(string s, paramsList *params) {

    RouteResult<T> *res = new RouteResult<T>(params);

    if (s == uri_) {
        res->controller_id = controller;
        return res;
    } else if (startsWith(s, uri_)) {
        // set the restString value and return
        res->restString = s.substr(uri_.length());
        return res;
    } else {
        // Not exact match and no children or search uri is NOT substring of uri_
        std::cout << " RouterNode::getNodeResult returning nullptr " << endl;
        res->isEmpty = true;

        std::cout << " RouterNode::getNodeResult result isEmpty: " << res->isEmpty << endl;
        return res;

    }
}

template <class T>
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

template <class T>
RouterNode<T> *RouterNode<T>::addChild(string uri, T id) {
    RouterNode<T> *child = new RouterNode<T>(uri, id);
    children.push_back(child);
    return child;
}
