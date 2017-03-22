//
// Created by Snytkine, Dmitri (CORP) on 3/22/17.
//

#ifndef ROUTER_CONSTANTS_H
#define ROUTER_CONSTANTS_H
#include <iostream>

namespace router_lib {
    using namespace std;
    static const string PATH_SEPARATOR = "/";
    static const string PLACEHOLDER_START = "{";
    static const string PLACEHOLDER_END = "}";
    static const string P_START = "(";
    static const string P_END = ")";

    string tail_(const string s);
}
#endif //ROUTER_CONSTANTS_H
