//
// Created by Snytkine, Dmitri (CORP) on 3/24/17.
//

#ifndef ROUTER_ROUTERNODEINT_H
#define ROUTER_ROUTERNODEINT_H
#include "RouterNode.h"

namespace router_lib {


    template
    class RouterNode<>: RouteResult{
        RouterNode(): RouterNode(){}
    };
}
#endif //ROUTER_ROUTERNODEINT_H
