//
// Created by Snytkine, Dmitri (CORP) on 3/27/17.
//

#include <iostream>
#include "http_methods.h"

namespace router_lib {

    HTTP_METHOD str_to_method(std::string m) {

        std::transform(m.begin(), m.end(), m.begin(), ::toupper);

        if (m == "GET") {
            return HTTP_METHOD::GET;
        } else if (m == "POST") {
            return HTTP_METHOD::POST;
        } else if (m == "PUT") {
            return HTTP_METHOD::PUT;
        } else if (m == "DELETE") {
            return HTTP_METHOD::DELETE;
        } else if (m == "HEAD") {
            return HTTP_METHOD::HEAD;
        } else if (m == "TRACE") {
            return HTTP_METHOD::TRACE;
        } else if (m == "CONNECT") {
            return HTTP_METHOD::CONNECT;
        } else if (m == "OPTIONS") {
            return HTTP_METHOD::OPTIONS;
        } else {
            throw std::invalid_argument("Method " + m + " is NOT supported");
        }
    }


    std::string http_method_to_string(HTTP_METHOD m) {
        switch (m) {
            case HTTP_METHOD::GET:
                return "GET";
            case HTTP_METHOD::POST:
                return "POST";
            case HTTP_METHOD::PUT:
                return "PUT";
            case HTTP_METHOD::DELETE:
                return "DELETE";
            case HTTP_METHOD::HEAD:
                return "HEAD";
            case HTTP_METHOD::TRACE:
                return "TRACE";
            case HTTP_METHOD::CONNECT:
                return "CONNECT";
            case HTTP_METHOD::OPTIONS:
                return "OPTIONS";
        }
    }


}

