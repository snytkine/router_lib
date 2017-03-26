//
// Created by Snytkine, Dmitri (CORP) on 3/14/17.
//

#ifndef ROUTER_ROUTER_NODE_H
#define ROUTER_ROUTER_NODE_H


#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>
#include <utility>
#include "node_result.h"


namespace router_lib {

    static const std::string PATH_SEPARATOR = "/";
    static const std::string PLACEHOLDER_START = "{";
    static const std::string PLACEHOLDER_END = "}";
    static const std::string P_START = "(";
    static const std::string P_END = ")";

    std::string tail_(const std::string s);

    enum class NodeType {
        BasicNode, ParamNode, FuncNode, CatchAll
    };

    class RouterNode {

    public :

        RouterNode(std::string uri, void *ctrl, std::string name = "") : origUriPattern(uri),
                                                                         controller_name(name),
                                                                         controller(ctrl) {
            init(uri);
            //cout << "CREATED NODE for uri=[" << uri << "] origUriPattern=[" << origUriPattern << "]" << endl;
        }


        RouterNode() : origUriPattern("/"), controller_name("ROOT"), controller(), nodeType_(NodeType::BasicNode) {}

        RouterNode(std::string uri) : origUriPattern(uri), controller() {
            init(uri);
        }

        void *getController() const;

        void setController(void *ctrl);

        bool empty() const;

        RouterNode *addRoute(std::string uri, void *controller, const std::string ctrl_name = "");

        RouteResult *findRoute(const std::string uri, paramsList *params = new paramsList()) const;

        ~RouterNode() {
            if (children.size() > 0) {
                //cout << " RouterNode " << origUriPattern << " destructor called " << endl; // never called?
                children.clear();
            }
        }

    protected:

        NodeType nodeType_ = NodeType::BasicNode;

        void *controller;

        std::string controller_name;

        std::string origUriPattern;

        std::vector<RouterNode *> children;

        bool END_WITH_SLASH;

        std::string paramName_;

        std::string prefix;

        void init(std::string uri);

        size_t startPos;

        // This is where the work is done to match uri for this node, possibly extract router params and
        // return a result.
        // result may contain controller_id in which case the result is found
        // or it may append extracted route params to params, generate the "restString" and return
        // result with params and restString, in which case children will be searched for a match for the restString
        RouteResult *getNodeResult(const std::string uri, paramsList *params = new paramsList()) const;

        RouteResult *getParamNodeResult(const std::string uri, paramsList *params = new paramsList()) const;

        RouteResult *getFuncNodeResult(const std::string uri, paramsList *params = new paramsList()) const;

        static std::string tail_(const std::string s);
    };

}
#endif //ROUTER_ROUTER_NODE_H
