//
// Created by Snytkine, Dmitri (CORP) on 3/22/17.
//

#include "RouterNode.h"
#include "PathParamNode.h"
#include "constants.h"

namespace router_lib {

    template<class T>
    RouterNode<T> *createRouterNode(string nodeUri);

    template<typename T>
    RouterNode<T> *createRouterNode(string nodeUri, T &id, string name) {
        cout << " ENTERED router_lib::createRouterNode()" << endl;
        size_t psOpen = nodeUri.find(PLACEHOLDER_START);
        if (psOpen == 0 && psOpen < nodeUri.find(PLACEHOLDER_END)) {
            // cout << "TO create PathParamNode with nodeUri [" << nodeUri << "] with id: " << id << endl;
            RouterNode<T> *ret = new PathParamNode<T>(nodeUri, id, name);
            // cout << "CREATED PathParamNode paramName=" << ret->getParamName() << " EMPTY=" << ret->empty() << endl;
            return ret;
        }

        return new RouterNode<T>(nodeUri, &id, name);
    }

    template<class T>
    RouterNode<T> *createRouterNode(string nodeUri) {
        // cout << " ENTERED RouterNode::createRouterNode()" << endl;
        size_t psOpen = nodeUri.find(PLACEHOLDER_START);
        if (psOpen == 0 && psOpen < nodeUri.find(PLACEHOLDER_END)) {
            // cout << "TO create PathParamNode with nodeUri [" << nodeUri << "] NO ID " << endl;
            return new PathParamNode<T>(nodeUri);
        }

        return new RouterNode<T>(nodeUri);
    }
}
