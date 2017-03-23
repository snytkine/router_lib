//
// Created by Snytkine, Dmitri (CORP) on 3/21/17.
//

#include "node_result.h"

namespace router_lib {

    bool RouteResult::isEmpty() const {
        return false;
    }

    bool EmptyResult::isEmpty() const {
        return true;
    }
}
