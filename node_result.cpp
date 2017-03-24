//
// Created by Snytkine, Dmitri (CORP) on 3/21/17.
//

#include "node_result.h"

namespace router_lib {

    template <class T>
    bool RouteResult<T>::isEmpty() {
        return false;
    }

    template <class T>
    bool EmptyResult<T>::isEmpty() {
        return true;
    }
}
