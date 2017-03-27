//
// Created by Snytkine, Dmitri (CORP) on 3/27/17.
//

#ifndef ROUTER_T_CONTROLLER_H
#define ROUTER_T_CONTROLLER_H
#include <iostream>
#include <vector>
#include "http_methods.h"

namespace router_lib {

    template<class T>
    class TController {
    public:
        const std::string name;
        const HTTP_METHOD httpMethod;
        const T ctrl;
    };

}


#endif //ROUTER_T_CONTROLLER_H
