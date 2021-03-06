//
// Created by Snytkine, Dmitri (CORP) on 3/14/17.
//

#include "RouterNode.h"
#include "PathParamNode.h"
#include "factory.h"


namespace router_lib {

    //template<typename T>
    //string RouterNode<T>::rest(const string s) const {

        // todo check that len of s must be > len of origUriPattern? Do we need this check?
        // is it possible to pass shorter string here?

        // cout << "ENTERED RouterNode::rest with s=[" << s << "] origUriPattern=" << origUriPattern << endl;


        //string ret = s.substr(s.find(PATH_SEPARATOR) + 1, string::npos);

        // cout << "RouterNode::rest ret[" << ret << "] result for [" << s << "] in NODE  " << controller_name << endl;

        //return ret;
    //}

    template<class T>
    RouteResult<T> *RouterNode<T>::getNodeResult(const string s, paramsList *params) const {

        // cout << "Entered getNodeResult in node [" << origUriPattern << "] looking for " << s << endl;

        RouteResult<T> *res = new RouteResult<T>(params);

        if (s == origUriPattern) {
            // cout << "           getNodeResult MATCH [" << origUriPattern << "] matched " << s << endl;
            res->controller = controller;
            return res;

        } else if (origUriPattern == s.substr(0, s.find(PATH_SEPARATOR) + 1)) {
            // set the restString value and return
            // cout << "          getNodeResult startsWith [" << origUriPattern << "] search " << s << endl;
            res->restString = tail_(s);
            return res;
        } else {
            // Not exact match and no children or search uri is NOT substring of origUriPattern

            // cout << " RouterNode::getNodeResult returning empty result: " << endl;

            return new EmptyResult<T>();

        }
    }


    template<class T>
    RouteResult<T> *RouterNode<T>::findRoute(const string s, paramsList *params) const {

        // cout << " Entered  RouterNode::findRoute Node: " << origOrigPattern << " looking for: " << s << endl;
        RouteResult<T> *res = getNodeResult(s, params);
        // cout << " RouteResult controller_id " << res->controller_id << " restString: " << res->restString << endl;

        if (res->isEmpty() == true) {

            // cout << " RouterNode::findRoute Result isEmpty:" << res->isEmpty() << endl;

            return res;

        } else if (res->restString.length() == 0) {
            // cout << " RouterNode::findRoute Result found. controller_id:" << *res->controller << endl;
            return res;
        } else if (children.size() > 0) {
            for (auto &&i : children) {
                // cout << " Looking in Child [" << i->origUriPattern << "] for " << res->restString << endl;
                auto cres = i->findRoute(res->restString, params);
                if (!cres->isEmpty() && cres->restString.length() == 0) {
                    return cres;
                }
            }
            // cout << "NONE OF THE CHILDRED HAD A RESULT" << endl;
        } else {
            // cout << " RouterNode::findRoute Result NOT found and NODE does not have children" << endl;
        }

        // cout << "RETURNING DEFAULT EMPTY RESULT" << endl;


        return new EmptyResult<T>();
    }


    template<class T>
    RouterNode<T> *RouterNode<T>::createRouterNode(string nodeUri, T &id, string name) {
        // cout << " ENTERED RouterNode::createRouterNode()" << endl;
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
    RouterNode<T> *RouterNode<T>::createRouterNode(string nodeUri) {
        // cout << " ENTERED RouterNode::createRouterNode()" << endl;
        size_t psOpen = nodeUri.find(PLACEHOLDER_START);
        if (psOpen == 0 && psOpen < nodeUri.find(PLACEHOLDER_END)) {
            // cout << "TO create PathParamNode with nodeUri [" << nodeUri << "] NO ID " << endl;
            return new PathParamNode<T>(nodeUri);
        }

        return new RouterNode<T>(nodeUri);
    }

    template<class T>
    RouterNode<T> *RouterNode<T>::addRoute(string uri, T &id, string name) {


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
        string restUri;

        // uri of the new node that we going to add
        string nodeUri;

        // position of path separator in the uri
        size_t sepPos = uri.find(PATH_SEPARATOR);

        if (sepPos != string::npos) {
            nodeUri = uri.substr(0, sepPos + 1);
            restUri = tail_(uri);//uri.substr(sepPos + 1, string::npos);
        } else {
            nodeUri = uri;
        }


        // Now we know values of nodeUri, restUri and NODE_TYPE
        //
        // If this node's originalUriPattern matched
        // the nodeUri then... if rest is not empty
        // call addRoute on this node again, passing rest of uri
        //  if rest is empty then if this node type is controller node
        //  then this is an error - trying to add node with controller to uri
        // that already exists.
        //
        // Else




        // Adding new node Always works on children because we always start with root node
        for (auto &&i : children) {
            // cout << " Checking child " << i->origUriPattern << " for router pattern " << uri << " EMPTY=" << i->empty() << " CTRL-NAME=" << i->controller_name << endl;
            if (i->origUriPattern == nodeUri) {

                // cout << "addRoute-CP1" << endl;
                // restUri is empty means we are adding a controller
                // to existing node that did not have controller before
                if (restUri.empty()) {
                    // cout << "addRoute-CP2" << endl;
                    if (!i->empty()) {
                        // cout << "addRoute-CP3 empty=" << i->empty() << endl;

                        // An existing Node can be a controller node
                        // but we now adding another node to it

                        throw "Route already added for same uri: " + uri;
                    } else {
                        // cout << "addRoute-CP4" << endl;
                        i->controller_name = name;
                        i->setController(&id);
                        //i->controller = &id;
                        // cout << "addRoute-CP5" << endl;
                        return i;
                    }
                } else {
                    // cout << "addRoute-CP6" << endl;
                    // First section of uri matched this child node
                    // but we have "restUri" of the uri
                    // in this case child node is not going to be used...
                    return i->addRoute(restUri, id, name);
                }
            }

        }

        // cout << "addRoute-CP7" << endl;
        // newNode uri did not match any of children origUriPattern
        // in this case add new Node to childred
        // cout << "Not matched in children of " << origUriPattern << " For uri: " << uri << endl;

        if (restUri.empty()) {
            newNode = router_lib::createRouterNode<T>(nodeUri, id, name); //new RouterNode<T>(nodeUri, id, name);
            // cout << "       Created new NODE with EMPTY=" << newNode->empty() << " for id: " << id << " URI=" << nodeUri << " PN: " << newNode->getParamName() << endl;
        } else {
            newNode = router_lib::createRouterNode<T>(nodeUri); //new RouterNode<T>(nodeUri);
            // cout << "       Created new NODE_NC for URI=" << nodeUri << endl;
            newNode->addRoute(restUri, id, name);
        }


        // cout << "Added new child to " << origUriPattern << ":" << controller << " with uri: " << nodeUri << endl;
        children.push_back(newNode);

        return newNode;

    }

    template<typename T>
    string RouterNode<T>::getParamName() const {
        return std::string();
    }


}