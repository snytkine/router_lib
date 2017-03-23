//
// Created by Snytkine, Dmitri (CORP) on 3/22/17.
//

#ifndef ROUTER_FUNCPARAMNODE_H
#define ROUTER_FUNCPARAMNODE_H

#include "RouterNode.h"
#include "constants.h"


namespace router_lib {


    class FuncParamNode : public RouterNode {

    public:

        FuncParamNode(string uri, void* pVoid, string name = "") : RouterNode(uri, pVoid, name) {
            init(uri);
        }

        FuncParamNode(string uri) : RouterNode(uri) {
            init(uri);
        }

        string getParamName() const;


    protected:

        void setParamName(string pn);

        void init(string uri) {
            END_WITH_SLASH = uri.back() == '/';
            startPos = uri.find(P_START) + 1;
            prefix = uri.substr(0, startPos);

            string pn = uri.substr(uri.find(PLACEHOLDER_START) + 1,
                                   uri.find(PLACEHOLDER_END) - uri.find(PLACEHOLDER_START) - 1);
            setParamName(pn);
        }

        string prefix;

        int startPos;

        bool END_WITH_SLASH;

        string paramName_;

        // This is where the work is done to match uri for this node, possibly extract router params and
        // return a result.
        // result may contain controller_id in which case the result is found
        // or it may append extracted route params to params, generate the "restString" and return
        // result with params and restString, in which case children will be searched for a match for the restString
        RouteResult *getNodeResult(const string uri, paramsList *params = new paramsList()) const;

    };


    //template class router_lib::FuncParamNode<int>;
}


#endif //ROUTER_FUNCPARAMNODE_H
