//
// Created by Snytkine, Dmitri (CORP) on 3/27/17.
//

#ifndef ROUTER_COUNTER_H
#define ROUTER_COUNTER_H

#include "RouterNode.h"


namespace router_lib {

    template<typename T>
    int getNodesCount(RouterNode <T> *node) {

        static int j = 1;
        auto cc = node->getChildres();
        int ts = cc.size();

        if (ts > 0) {
            j += ts;
            for (auto &&i: cc) {
                getNodesCount(i);
            }
        }

        return j;
    }

}
#endif //ROUTER_COUNTER_H
