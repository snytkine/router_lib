//
// Created by Snytkine, Dmitri (CORP) on 3/22/17.
//

#ifndef ROUTER_CONSTANTS_H
#define ROUTER_CONSTANTS_H
#include <iostream>

namespace router_lib {

    static const std::string PATH_SEPARATOR = "/";
    static const std::string PLACEHOLDER_START = "{";
    static const std::string PLACEHOLDER_END = "}";
    static const std::string P_START = "(";
    static const std::string P_END = ")";

    std::string tail_(const std::string s);
}
#endif //ROUTER_CONSTANTS_H
