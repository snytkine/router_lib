//
// Created by Snytkine, Dmitri (CORP) on 3/14/17.
//

#include "RouterNode.h"
#include "strlib.h"

namespace router_lib {

    template<typename T>
    string RouterNode<T>::rest(const string s) {

        // todo check that len of s must be > len of uri_? Do we need this check?
        // is it possible to pass shorter string here?

        string ret = s.substr(uri_.length());
        cout << "RouterNode::rest in node[" << origUriPattern << "] result for [" << s << "] =" << ret << endl;

        return ret;
    }

    template<class T>
    RouteResult<T> *RouterNode<T>::getNodeResult(string s, paramsList *params) {

        cout << "Entered getNodeResult in node [" << origUriPattern << "] looking for " << s << endl;

        RouteResult<T> *res = new RouteResult<T>(params);

        if (s == uri_) {
            cout << "           getNodeResult MATCH [" << origUriPattern << "] matched " << s << endl;
            res->controller_id = controller;
            return res;
            //} else if (startsWith(s, uri_)) {
        } else if (uri_ == s.substr(0, s.find(PATH_SEPARATOR) + 1)) {
            // set the restString value and return
            cout << "          getNodeResult startsWith [" << origUriPattern << "] search " << s << endl;
            res->restString = rest(s);
            return res;
        } else {
            // Not exact match and no children or search uri is NOT substring of uri_
            res->isEmpty = true;

            std::cout << " RouterNode::getNodeResult result isEmpty: " << res->isEmpty << endl;
            return res;

        }
    }


    template<typename T>
    RouteParam *RouterNode<T>::extractParam() {
        return nullptr;
    }

    template<class T>
    RouteResult<T> *RouterNode<T>::findRoute(string s, paramsList *params) {

        //std::cout << " Entered  RouterNode::findRoute Node: " << uri_ << " looking for: " << s << endl;
        RouteResult<T> *res = getNodeResult(s, params);
        //std::cout << " RouteResult controller_id " << res->controller_id << " restString: " << res->restString << endl;

        if (res->isEmpty == true) {
            std::cout << " RouterNode::findRoute Result isEmpty:" << res->isEmpty << endl;
            return res;
        } else if (res->restString.length() == 0) {
            std::cout << " RouterNode::findRoute Result found. controller_id:" << res->controller_id << endl;
            return res;
        } else if (children.size() > 0) {
            for (auto &&i : children) {
                std::cout << " Looking in Child [" << i->origUriPattern << "] for " << res->restString << endl;
                auto cres = i->findRoute(res->restString, params);
                if (!cres->isEmpty && cres->restString.length() == 0) {
                    return cres;
                }
            }
        }


        return new RouteResult<T>(params);
    }

    template<class T>
    RouterNode<T> *RouterNode<T>::addChild(string uri, T id) {
        RouterNode<T> *child = new RouterNode<T>(uri, id, "OK");
        children.push_back(child);
        return child;
    }


    template<class T>
    RouterNode<T> *RouterNode<T>::addRoute(string uri) {


    }

    template<class T>
    RouterNode<T> *RouterNode<T>::addRoute(string uri, T id, string name) {


        // First strip leading slash from uri because we always start with root node
        // which is a node for a slash uri
        if (uri != "/" && uri[0] == '/') {
            uri = uri.substr(1, string::npos);
        }

        // todo check if origUri == uri and id is NOT empty
        // that would mean that trying to add route for uri that already exists
        // in which case must throw exception.



        RouterNode<T> *newNode;
        // Rest of the uri string after the first uri path section was stripped off
        string rest;

        // uri of the new node that we going to add
        string nodeUri;

        // Type of node we going to add - controller or non-controller node
        router_lib::NODE_TYPE NEW_NODE_TYPE = NODE_NC;

        // position of path separator in the uri
        size_t sepPos = uri.find(PATH_SEPARATOR);

        if (sepPos != string::npos) {
            nodeUri = uri.substr(0, sepPos + 1);
            rest = uri.substr(sepPos + 1, string::npos);
        } else {
            nodeUri = uri;
        }


        // Now we know values of nodeUri, rest and NODE_TYPE
        //
        // If this node's originalUriPattern matched
        // the nodeUri then... if rest is not empty
        // call addRoute on this node again, passing rest of uri
        //  if rest is empty then if this node type is controller node
        //  then this is an error - trying to add node with controller to uri
        // that already exists.
        //
        // Else
        if (sepPos == string::npos || (sepPos + 1) == uri.length()) {
            NEW_NODE_TYPE = NODE_CTRL;
        }



        // Adding new node Always works on children because we always start with root node
        for (auto &&i : children) {
            cout << " Checking child " << i->origUriPattern << " for router pattern " << uri << endl;
            if (i->origUriPattern == nodeUri) {

                // rest is empty means we are adding a controller
                // to existing node that did not have controller before
                if (rest.empty()) {
                    if (i->TYPE != NODE_NC) {
                        throw "Route already added for same uri: " + uri;
                    } else {
                        i->TYPE = NODE_CTRL;
                        i->controller_name = name;
                        i->controller = id;

                        return i;
                    }
                } else {
                    // First section of uri matched this child node
                    // but we have "rest" of the uri
                    // in this case child node is not going to be used...
                    return i->addRoute(rest, id, name);
                }
            }

        }

        // newNode uri did not match any of children origUriPattern
        // in this case add new Node to childred
        cout << "Not matched in children of " << origUriPattern << " For uri: " << uri << endl;

        if (rest.empty()) {
            newNode = new RouterNode<T>(nodeUri, id, name);
            cout << "       Created new NODE_CTRL for id: " << id << " URI=" << nodeUri << endl;
        } else {
            newNode = new RouterNode<T>(nodeUri);
            cout << "       Created new NODE_NC for URI=" << nodeUri << endl;
            newNode->addRoute(rest, id, name);
        }


        cout << "Added new child to " << origUriPattern << ":" << controller << " with uri: " << nodeUri << endl;
        children.push_back(newNode);

        return newNode;


    }

    /*template <typename T>
    RouterNode<T>* emptyNode(){
        RouterNode<T>* res = new RouterNode<T>("/");
    }*/

}