//
// Created by Snytkine, Dmitri (CORP) on 3/27/17.
//

#ifndef ROUTER_HTTP_METHODS_H
#define ROUTER_HTTP_METHODS_H

#include <iostream>

namespace router_lib {

    enum class HTTP_METHOD {
        GET, POST, PUT, DELETE, HEAD, TRACE, CONNECT, OPTIONS
    };

    HTTP_METHOD str_to_method(std::string m);


    std::string http_method_to_string(HTTP_METHOD m);
}
#endif //ROUTER_HTTP_METHODS_H
