//
// Created by Snytkine, Dmitri (CORP) on 3/22/17.
//

#ifndef ROUTER_FUNCPARAMNODE_H
#define ROUTER_FUNCPARAMNODE_H

#include "RouterNode.h"
#include "constants.h"
#include "PathParamNode.h"


namespace router_lib {


    class FuncParamNode : public PathParamNode {

    public:

        FuncParamNode(std::string uri, void* pVoid, std::string name = "") : PathParamNode(uri, pVoid, name) {
            init(uri);
        }

        FuncParamNode(std::string uri) : PathParamNode(uri) {
            init(uri);
        }


    protected:

        void init(std::string uri);

        std::string prefix;

        int startPos;

        // This is where the work is done to match uri for this node, possibly extract router params and
        // return a result.
        // result may contain controller_id in which case the result is found
        // or it may append extracted route params to params, generate the "restString" and return
        // result with params and restString, in which case children will be searched for a match for the restString
        virtual RouteResult *getNodeResult(const std::string uri, paramsList *params = new paramsList()) const override;

    };
}


#endif //ROUTER_FUNCPARAMNODE_H
