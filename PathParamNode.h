//
// Created by Snytkine, Dmitri (CORP) on 3/18/17.
//

#ifndef ROUTER_PATHPARAMNODE_H
#define ROUTER_PATHPARAMNODE_H

#include "RouterNode.h"

namespace router_lib {

    using namespace std;

    class PathParamNode : public RouterNode {

    public:

        PathParamNode(string uri, void* pVoid, string name = "") : RouterNode(uri, pVoid, name) {

            END_WITH_SLASH = uri.back() == '/';
            string pn = uri.substr(1, uri.length() - 3);
            setParamName(pn);

            // cout << "CREATED PathParamNode paramName=" << paramName << " TYPE=" << kind() << endl;
        }

        PathParamNode(string uri) : RouterNode(uri) {
            END_WITH_SLASH = uri.back() == '/';
            setParamName(uri.substr(1, uri.length() - 3));
        }

        string getParamName() const;


    protected:

        bool END_WITH_SLASH;

        string paramName_;

        void setParamName(string pn);
        //string uri_;

        //vector<RouterNode<T> *> children;

        // This is where the work is done to match uri for this node, possibly extract router params and
        // return a result.
        // result may contain controller_id in which case the result is found
        // or it may append extracted route params to params, generate the "restString" and return
        // result with params and restString, in which case children will be searched for a match for the restString
        RouteResult *getNodeResult(const string uri, paramsList *params = new paramsList()) const;

        //virtual string rest(const string s) const;

    };


    //template class router_lib::PathParamNode<int>;
}


#endif //ROUTER_PATHPARAMNODE_H
