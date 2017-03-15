//
// Created by Snytkine, Dmitri (CORP) on 3/14/17.
//

#include "RouterNode.h"
#include "strlib.h"

RouteResult* RouterNode::findRoute(string s, paramsList *params) {
    RouteResult ret = {};
    RouteResult *res;
    if (s == uri_) {
        ret.controller_id = controller_id;
    } else if (children.size() > 0 && startsWith(s, uri_)) {
        //http://en.cppreference.com/w/cpp/language/range-for
        for (auto &&i : children) {
            std::string temp = s.substr(uri_.length());
            std::cout << " Looking in Child for " << temp << endl;
            res = i->findRoute(temp);
            if (res->controller_id > 0) {
                return res;
            }
        }

    }

    return &ret;
}

RouterNode* RouterNode::addChild(string uri, int id){
    RouterNode* child = new RouterNode(uri, id);
    children.push_back(child);
    return child;
}
