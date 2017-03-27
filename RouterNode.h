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
#include "http_methods.h"
#include "t_controller.h"


namespace router_lib {


    static const std::string PATH_SEPARATOR = "/";
    static const std::string PLACEHOLDER_START = "{";
    static const std::string PLACEHOLDER_END = "}";
    static const std::string P_START = "(";
    static const std::string P_END = ")";

    enum class NodeType {
        BasicNode, ParamNode, FuncNode, CatchAll
    };


    std::string tail_(const std::string s);

    template<class T>
    class RouterNode {

    public :

        RouterNode<T>(std::string uri, TController<T> ctrl, std::string name = "") :
                controllers{ctrl}, origUriPattern(uri) {
            init(uri);
            //cout << "CREATED NODE for uri=[" << uri << "] origUriPattern=[" << origUriPattern << "]" << endl;
        }


        RouterNode<T>() : nodeType_(NodeType::BasicNode), origUriPattern("/") {}

        RouterNode<T>(std::string uri) : origUriPattern(uri) {
            init(uri);
        }

        std::vector<TController<T>> *getControllers();

        bool empty() const;


        static void addContollerToNode(RouterNode<T> *node, TController<T> ctrl) {

            if (node->children.empty()) {
                node->controllers.push_back(ctrl);
            } else {
                for (TController<T> &i: node->controllers) {
                    if (i.httpMethod == ctrl.httpMethod) {
                        throw std::invalid_argument("Controller for method " + http_method_to_string(ctrl.httpMethod) +
                                                    " Already exists in node " + node->origUriPattern);
                    }
                }

                node->controllers.push_back(ctrl);
            }

        }


        void addRoute(std::string uri, T controller, std::string http_method, const std::string name) {

            // First strip leading slash from uri because we always start with root node
            // which is a node for a slash uri
            if (uri != "/" && uri[0] == '/') {
                uri = uri.substr(1, std::string::npos);
            }

            // todo check if origUri == uri and id is NOT empty
            // that would mean that trying to add route for uri that already exists
            // in which case must throw exception.



            RouterNode<T> *newNode;
            // Rest of the uri string after the first uri path section was stripped off
            std::string restUri;

            // uri of the new node that we going to add
            std::string nodeUri;

            // position of path separator in the uri
            size_t sepPos = uri.find(PATH_SEPARATOR);

            if (sepPos != std::string::npos) {
                nodeUri = uri.substr(0, sepPos + 1);
                restUri = tail_(uri);//uri.substr(sepPos + 1, string::npos);
            } else {
                nodeUri = uri;
            }

            try {
                // Adding new node Always works on children because we always start with root node
                for (auto &&i : children) {
                    // cout << " Checking child " << i->origUriPattern << " for router pattern " << uri << " EMPTY=" << i->empty() << " CTRL-NAME=" << i->controller_name << endl;
                    if (i->origUriPattern == nodeUri) {

                        // cout << "addRoute-CP1" << endl;
                        // restUri is empty means we are adding a controller
                        // to existing node that did not have controller before
                        if (restUri.empty()) {
                            // cout << "addRoute-CP2" << endl;

                            // new way - Just call addControllerToNode, it will add ctrl or throw
                            addContollerToNode(i, TController<T>{name, str_to_method(http_method), controller});

                            // end old way
                        } else {
                            // cout << "addRoute-CP6" << endl;
                            // First section of uri matched this child node
                            // but we have "restUri" of the uri
                            // in this case child node is not going to be used...
                            i->addRoute(restUri, controller, http_method, name);

                            return;
                        }
                    }

                } // end for each child
            } catch (std::invalid_argument e) {
                std::string reason = e.what();
                throw std::invalid_argument("Failed to add Route for uri=" + uri + " Error: " + reason);
            }


            // cout << "addRoute-CP7" << endl;
            // newNode uri did not match any of children origUriPattern
            // in this case add new Node to childred
            // cout << "Not matched in children of " << origUriPattern << " For uri: " << uri << endl;

            newNode = new RouterNode<T>(nodeUri);


            if (restUri.empty()) {
                addContollerToNode(newNode, TController<T>{name, str_to_method(http_method), controller});
                // cout << "       Created new NODE with EMPTY=" << newNode->empty() << " for id: " << id << " URI=" << nodeUri << " PN: " << newNode->getParamName() << endl;
            } else {
                newNode = new RouterNode<T>(nodeUri); //new RouterNode<T>(nodeUri);
                // cout << "       Created new NODE_NC for URI=" << nodeUri << endl;
                newNode->addRoute(restUri, controller, http_method, name);
            }


            // cout << "Added new child to " << origUriPattern << ":" << controller << " with uri: " << nodeUri << endl;
            children.push_back(newNode);
        }


        RouteResult<T> *findRoute(const std::string s, paramsList *params = new paramsList()) {

            // std::cout << " Entered  RouterNode::findRoute Node: " << origUriPattern << " looking for: " << s
             //         << std::endl;
            RouteResult<T> *res;

            switch (nodeType_) {

                case NodeType::ParamNode:
                    res = getParamNodeResult(s, params);
                    // std::cout << "GET res from getParamNodeResult 88463" << std::endl;
                    break;

                case NodeType::FuncNode:
                    res = getFuncNodeResult(s, params);
                    // std::cout << "GET res from getFuncNodeResult 98799" << std::endl;
                    break;

                case NodeType::BasicNode:
                default:
                    res = getNodeResult(s, params);
                    // std::cout << "GET res from getNodeResult 43842" << std::endl;
                    break;

            }

            if (res->isEmpty()) {

                // std::cout << " RouterNode::findRoute Result isEmpty:" << res->isEmpty() << std::endl;

                return res;

            } else if (res->restString.length() == 0) {
                // std::cout << " RouterNode::findRoute Result found. number of controllers:"
                 //         << std::to_string(res->controllers->size()) << std::endl;
                return res;
            } else if (children.size() > 0) {
                // std::cout
                //        << " NODE with originalUriPattern=[" + origUriPattern + "] has children. Will look in children"
                 //       << std::endl;
                for (auto &&i : children) {
                    // std::cout << " Looking in Child [" << i->origUriPattern << "] for " << res->restString << std::endl;
                    auto cres = i->findRoute(res->restString, params);
                    if (!cres->isEmpty() && cres->restString.length() == 0) {

                        return cres;
                    }
                }
                // std::cout << "NONE OF THE CHILDRED HAD A RESULT" << std::endl;
            } else {
                // std::cout << " RouterNode::findRoute Result NOT found and NODE does not have children" << std::endl;
            }

            // std::cout << "RETURNING DEFAULT EMPTY RESULT" << std::endl;


            return new EmptyResult<T>();
        }

        ~RouterNode<T>() {
            if (children.size() > 0) {
                //cout << " RouterNode " << origUriPattern << " destructor called " << endl; // never called?
                children.clear();
            }
        }

    protected:

        NodeType nodeType_ = NodeType::BasicNode;

        std::vector<TController<T>> controllers;

        //std::string controller_name;

        std::string origUriPattern;

        //bool empty_ = true;

        std::vector<RouterNode<T> *> children;

        bool END_WITH_SLASH;

        std::string paramName_;

        std::string prefix;

        void init(std::string uri);

        //void init(std::string uri, T ctrl);

        size_t startPos;

        // This is where the work is done to match uri for this node, possibly extract router params and
        // return a result.
        // result may contain controller_id in which case the result is found
        // or it may append extracted route params to params, generate the "restString" and return
        // result with params and restString, in which case children will be searched for a match for the restString
        RouteResult<T> *getNodeResult(const std::string uri, paramsList *params = new paramsList());

        RouteResult<T> *getParamNodeResult(const std::string uri, paramsList *params = new paramsList());

        RouteResult<T> *getFuncNodeResult(const std::string uri, paramsList *params = new paramsList());

    };

    template
    class RouterNode<int>;
}
#endif //ROUTER_ROUTER_NODE_H
