//
// Created by Snytkine, Dmitri (CORP) on 3/22/17.
//
#include <iostream>
#include "constants.h"


namespace router_lib {

    std::string tail_(const std::string s) {

        // todo check that len of s must be > len of origUriPattern? Do we need this check?
        // is it possible to pass shorter string here?

        // cout << "ENTERED RouterNode::rest with s=[" << s << "] origUriPattern=" << origUriPattern << endl;


        std::string ret = s.substr(s.find(PATH_SEPARATOR) + 1, std::string::npos);

        // cout << "RouterNode::rest ret[" << ret << "] result for [" << s << "] in NODE  " << controller_name << endl;

        return ret;
    }
}

