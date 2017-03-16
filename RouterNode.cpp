//
// Created by Snytkine, Dmitri (CORP) on 3/14/17.
//

#include "RouterNode.h"
#include "strlib.h"


RouteResult *RouterNode::getNodeResult(string s, paramsList *params) {
    RouteResult *res = new RouteResult(params);

    if (s == uri_) {
        res->controller_id = controller_id;
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

RouteResult *RouterNode::findRoute(string s, paramsList *params) {

    //std::cout << " Entered  RouterNode::findRoute Node: " << uri_ << " looking for: " << s << endl;
    RouteResult *res = getNodeResult(s, params);
    std::cout << " RouteResult controller_id " << res->controller_id << " restString: " << res->restString << endl;
    // What is result NOT found at all?

    // result can be one of 3:
    // nullptr - nothing at all found meaning there is no need to look in children.
    // result with empty restString which means there is nothing else left to match, just return in
    // a result with restString in which case keep looking in children using restString as input

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


    return new RouteResult(params);
}

RouterNode *RouterNode::addChild(string uri, int id) {
    RouterNode *child = new RouterNode(uri, id);
    children.push_back(child);
    return child;
}
