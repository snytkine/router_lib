//
// Created by Snytkine, Dmitri (CORP) on 3/18/17.
//

#ifndef ROUTER_PATHPARAMNODE_H
#define ROUTER_PATHPARAMNODE_H

#include "RouterNode.h"

namespace router_lib {

    using namespace std;

    template<typename T>
    class PathParamNode : public RouterNode<T> {

    public:

        PathParamNode(string uri, T &id, string name = "") : RouterNode<T>::RouterNode(uri, &id, name) {

            END_WITH_SLASH = uri.back() == '/';
            string pn = uri.substr(1, uri.length() - 3);
            setParamName(pn);

            // cout << "CREATED PathParamNode paramName=" << paramName << " TYPE=" << kind() << endl;
        }

        PathParamNode(string uri) : RouterNode<T>(uri) {
            //NODE_TYPE TYPE = NODE_PATH_PARAM;
            END_WITH_SLASH = uri.back() == '/';
            setParamName(uri.substr(1, uri.length() - 3));
        }


        void setParamName(string pn);

        string getParamName() const;


    protected:

        bool END_WITH_SLASH;

        string paramName_;
        //string uri_;

        //vector<RouterNode<T> *> children;

        // This is where the work is done to match uri for this node, possibly extract router params and
        // return a result.
        // result may contain controller_id in which case the result is found
        // or it may append extracted route params to params, generate the "restString" and return
        // result with params and restString, in which case children will be searched for a match for the restString
        RouteResult <T> *getNodeResult(const string uri, paramsList *params = new paramsList()) const;

        string rest(const string s) const;



    };


    template class router_lib::PathParamNode<int>;
}


#endif //ROUTER_PATHPARAMNODE_H
