//
// Created by Snytkine, Dmitri (CORP) on 3/23/17.
//

#include "RouterNode.h"
#include "PathParamNode.h"
#include "FuncParamNode.h"
#include "constants.h"

namespace router_lib {


    RouterNode *createRouterNode(const std::string nodeUri, void* pVoid, const std::string name) {
        //cout << " ENTERED router_lib::createRouterNode() with nodeUri=[" << nodeUri << "]" << endl;
        size_t psOpen = nodeUri.find(PLACEHOLDER_START);
        size_t psClose = nodeUri.find(PLACEHOLDER_END);
        size_t bOpen = nodeUri.find(P_START);
        size_t bClose = nodeUri.find(P_END);
        if (psOpen == 0 && psOpen < psClose) {

            //cout << "WILL CREATE PLACEHOLDER NODE for uri=[" << nodeUri << "]" << endl;

            // cout << "TO create PathParamNode with nodeUri [" << nodeUri << "] with id: " << id << endl;
            RouterNode *ret = new PathParamNode(nodeUri, pVoid, name);
            //cout << "CREATED PathParamNode paramName=" << ret->getParamName() << " EMPTY=" << ret->empty() << endl;
            return ret;

        } else if (psOpen > 0 && psOpen < psClose && bOpen == psOpen - 1 && bClose == psClose + 1) {
            RouterNode *fnode = new FuncParamNode(nodeUri, pVoid, name);
            // cout << "CREATED FuncParamNode paramName=" << fnode->getParamName() << " EMPTY=" << fnode->empty() << endl;
            return fnode;
        }

        return new RouterNode(nodeUri, pVoid, name);
    }


    RouterNode *createRouterNode(const std::string nodeUri) {
        // cout << " ENTERED RouterNode::createRouterNode()" << endl;
        size_t psOpen = nodeUri.find(PLACEHOLDER_START);
        size_t psClose = nodeUri.find(PLACEHOLDER_END);
        size_t bOpen = nodeUri.find(P_START);
        size_t bClose = nodeUri.find(P_END);

        if (psOpen == 0 && psOpen < psClose) {
            //cout << "WILL CREATE PLACEHOLDER NODE (NC) for uri=[" << nodeUri << "]" << endl;

            //cout << "CREATED PathParamNode node for uri=[" << nodeUri << "]" << endl;
            return new PathParamNode(nodeUri);

        } else if (psOpen > 0 && psOpen < psClose && bOpen == psOpen - 1 && bClose == psClose + 1) {
            //cout << "CREATED PathParamNode node (NC) for uri=[" << nodeUri << "]" << endl;
            return new FuncParamNode(nodeUri);
        }

        return new RouterNode(nodeUri);
    }
}
