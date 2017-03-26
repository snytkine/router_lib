//
// Created by Snytkine, Dmitri (CORP) on 3/14/17.
//

#include "RouterNode.h"
#include "strlib.h"


namespace router_lib {


    void RouterNode::init(std::string uri) {

        END_WITH_SLASH = uri.back() == '/';

        size_t parenStartPos = uri.find(P_START);
        size_t parenEndPos = uri.find(P_END);

        size_t placeholderStartPos = uri.find(PLACEHOLDER_START);
        size_t placeholderEndPos = uri.find(PLACEHOLDER_END);

        // Validate positions of placeholders and parens then determine the type of node
        if (placeholderStartPos != std::string::npos || placeholderEndPos != std::string::npos) {

            if (placeholderStartPos > placeholderEndPos) {
                throw std::invalid_argument("BAD PLACEHOLDER POS 001");
            }

            // if { at pos 0 then it's not FuncParamNode
            //  cannot contain P_START or P_END
            //  if NOT ENDS_WITH_SLASH then must end with PLACEHOLDER_END
            //  otherwise placeholderEndPos must be one less than uri length
            // else this must be FuncParamNode  validate for it.
            if (placeholderStartPos == 0) {
                if (!END_WITH_SLASH) {
                    if (placeholderEndPos + 1 != uri.length()) {
                        throw std::invalid_argument("BAD PLACEHOLDER POS 002 for uri: " + uri);
                    }
                } else {
                    if (placeholderEndPos + 2 != uri.length()) {
                        throw std::invalid_argument("BAD PLACEHOLDER POS 003 for uri: " + uri);
                    }
                }

                if (parenEndPos != std::string::npos || parenStartPos != std::string::npos) {
                    throw std::invalid_argument("PAREN INSIDE PLACEHOLDER for uri: " + uri);
                }

                // This now looks like a valid ParamNode type
                nodeType_ = NodeType::ParamNode;

            } else {
                // validate for FuncNodeType

                if (parenStartPos == std::string::npos || parenStartPos < 1) {
                    throw std::invalid_argument("BAD PAREN POS 004 for uri: " + uri);
                }

                if (parenEndPos == std::string::npos || parenEndPos < parenStartPos) {
                    throw std::invalid_argument("BAD PAREN POS 005 for uri: " + uri);
                }

                if (!END_WITH_SLASH) {
                    // parenEndPos must be just before slash
                    if (parenEndPos + 1 != uri.length()) {
                        throw std::invalid_argument("BAD PAREN END POS 006 for uri: " + uri);
                    }
                } else {
                    // ends with slash
                    // end pos must be
                    if (parenEndPos + 2 != uri.length()) {
                        throw std::invalid_argument("BAD PAREN END POS 007 for uri: " + uri);
                    }
                }

                if (parenStartPos + 1 != placeholderStartPos) {
                    throw std::invalid_argument("BAD PAREN START POST 008 for uri: " + uri);
                }

                if (parenEndPos - 1 != placeholderEndPos) {
                    throw std::invalid_argument("BAD PAREN END POS 009 for uri: " + uri);
                }

                // looks like valid FuncNode
                nodeType_ = NodeType::FuncNode;
                startPos = parenStartPos + 1;
                prefix = uri.substr(0, startPos);
                // std::cout << "~~~~~~~~~~ MADE FuncNode ~~~~~~~~~ for uri[" << uri << "]" << std::endl;
            }


            std::string pn = uri.substr(placeholderStartPos + 1, placeholderEndPos - placeholderStartPos - 1);

            if (pn.empty()) {
                throw std::invalid_argument("EMPTY PARAM NAME for uri: " + uri);
            }

            paramName_ = pn;


        } // no valid placeholders

        /*else {
            nodeType_ = NodeType::BasicNode;
        }*/

    }



    bool RouterNode::empty() const {
        return controller == nullptr;
    }

    void RouterNode::setController(void *ctrl) {
        controller = ctrl;
    }

    void *RouterNode::getController() const {
        return controller;
    }


    RouteResult *RouterNode::getFuncNodeResult(const std::string uri, paramsList *params) const {

        std::cout << "Entered getFuncNodeResult with URI=" << uri << std::endl;
        RouteResult *res = new RouteResult(params);
        size_t sepPos = uri.find(PATH_SEPARATOR);
        if (END_WITH_SLASH) {
            std::cout << "FuncNode END_WITH_SLASH originalUriPatterh=" << origUriPattern << std::endl;
            if (sepPos == std::string::npos) {
                std::cout << "URI DOES NOT END WITH SLASH" << std::endl;

                return new EmptyResult();
            } else {

                // HERE Our node ends with slash, the uri has slash but may not end with slash

                // LOGIC
                // uri must end with ")/"
                // uri must start with prefix
                // extract everything from prefix to ")"

                if (!::startsWith(uri, prefix)) {
                    std::cout << "FuncParamNode uri=[" << uri << "] does not start with prefix=[" << prefix << "]" << std::endl;

                    return new EmptyResult();
                }

                size_t myEndPos = uri.find(P_END + PATH_SEPARATOR);
                if(myEndPos == std::string::npos){
                    std::cout << " uri=" << uri << " Does not have " << (P_END + PATH_SEPARATOR) << " in node originalUriPattern=" << origUriPattern << std::endl;
                }

                if(myEndPos <= startPos + 1){
                    std::cout << "myEndPos=" << myEndPos << " startPos=" << startPos << " in originalUriPattern=" << origUriPattern << " uri=" << uri << std::endl;
                }

                // cout << "URI HAS SLASH" << endl;
                // extract param manually
                RouteParam *rp = new RouteParam(paramName_, uri.substr(startPos, myEndPos - startPos));
                // cout << "CP-1" << endl;
                params->push_back(rp);
                // cout << "CP-2" << endl;
                res->params = params;
                // cout << "CP-3" << endl;
                res->restString = tail_(uri);
                // cout << "CP-4" << endl;
                if (res->restString.empty()) {
                    // cout << "CP-5" << endl;
                    res->controller = getController();
                } else {
                    // cout << "CP-6" << " rest was: " << res->restString << endl;
                }
                // cout << "CP-7" << endl;
                return res;
            }
        } else {
            std::cout << "FuncNode DOES NOT END_WITH_SLASH=" << origUriPattern << std::endl;
            // cout << "NOT END_WITH_SLASH" << endl;
            if (sepPos != std::string::npos) {
                std::cout << "URI HAS SLASH=" << uri << std::endl;

                return new EmptyResult();
            } else {
                std::cout << "URI DOES NOT HAVE SLASH=" << uri << std::endl;
                // LOGIC:
                // uri must end with ")"
                // uri must start with prefix
                // extract everything from prefix to ")"

                // cout << "URI ALSO DOES NOT HAVE SLASH" << endl;

                size_t myEndPos = uri.find(P_END);
                if(myEndPos == std::string::npos){
                    std::cout << " uri=" << uri << " Does not have " << (P_END) << " in node originalUriPattern=" << origUriPattern << std::endl;
                }

                if(myEndPos <= startPos + 1){
                    std::cout << "FuncNode myEndPos=" << myEndPos << " startPos=" << startPos << " in originalUriPattern=" << origUriPattern << " uri=" << uri << std::endl;
                }

                RouteParam *rp = new RouteParam(paramName_, uri.substr(startPos, myEndPos - startPos));
                params->push_back(rp);
                res->params = params;
                //res->restString = tail_(uri);
                // in case like this there is no need to extract rest because since uri does not have slash the entire uri is a val.


                return res;
            }
        }

    }


    RouteResult *RouterNode::getParamNodeResult(const std::string uri, paramsList *params) const {

        // std::cout << "Entered getParamNodeResult NodeType=[" << (int) nodeType_ << "] looking for " << uri << std::endl;
        // cout << "Entered PathParamNode::getNodeResult looking for " << uri << endl;
        // If origUriPattern ends with slash
        //      then if uri does NOT have slash
        //           -> isEmpty
        //      else
        //          -> everything up to slash is extracted val
        //              get rest() and do same as with RouterNode...
        // else
        //      if uri has slash
        //          -> NOT FOUND
        //      else
        //          -> uri IS extracted val and we have result to return!
        //
        RouteResult *res = new RouteResult(params);
        size_t sepPos = uri.find(PATH_SEPARATOR);
        if (END_WITH_SLASH) {
            // cout << "END_WITH_SLASH" << endl;
            if (sepPos == std::string::npos) {
                // cout << "URI DOES NOT END WITH SLASH" << endl;

                return new EmptyResult();
            } else {
                // std::cout << "URI HAS SLASH " << uri << std::endl;
                // extract param manually
                RouteParam *rp = new RouteParam(paramName_, uri.substr(0, sepPos));
                // cout << "CP-1" << endl;
                params->push_back(rp);
                // cout << "CP-2" << endl;
                res->params = params;
                // cout << "CP-3" << endl;
                res->restString = tail_(uri);
                // cout << "CP-4" << endl;
                if (res->restString.empty()) {
                    // std::cout << "CP-5" << std::endl;
                    res->controller = getController();
                } else {
                    // cout << "CP-6" << " rest was: " << res->restString << endl;
                }
                // cout << "CP-7" << endl;
                return res;
            }
        } else {
            // cout << "NOT END_WITH_SLASH" << endl;
            if (sepPos != std::string::npos) {
                // cout << "URI HAS SLASH" << endl;

                return new EmptyResult();
            } else {
                // cout << "URI ALSO DOES NOT HAVE SLASH" << endl;
                RouteParam *rp = new RouteParam(paramName_, uri);
                params->push_back(rp);
                res->params = params;
                // in case like this there is no need to extract rest because since uri does not have slash the entire uri is a val.


                return res;
            }
        }

    }

    RouteResult *RouterNode::getNodeResult(const std::string s, paramsList *params) const {

        // std::cout << "Entered getNodeResult NodeType=[" << (int) nodeType_ << "] looking for " << s << std::endl;
        // cout << "Entered getNodeResult in node [" << origUriPattern << "] looking for " << s << endl;

        RouteResult *res = new RouteResult(params);

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

            return new EmptyResult();

        }
    }


    RouteResult *RouterNode::findRoute(const std::string s, paramsList *params) const {

        // cout << " Entered  RouterNode::findRoute Node: " << origOrigPattern << " looking for: " << s << endl;
        RouteResult *res;

        switch (nodeType_) {

            case NodeType::ParamNode:
                res = getParamNodeResult(s, params);
                break;

            case NodeType::FuncNode:
                res = getFuncNodeResult(s, params);
                break;

            case NodeType::BasicNode:
            default:
                res = getNodeResult(s, params);
                break;

        }
        //RouteResult *res = getNodeResult(s, params);
        // cout << " RouteResult controller_id " << res->controller_id << " restString: " << res->restString << endl;

        if (res->isEmpty()) {

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


        return new EmptyResult();
    }


    RouterNode *RouterNode::addRoute(std::string uri, void *pVoid, const std::string name) {


        // First strip leading slash from uri because we always start with root node
        // which is a node for a slash uri
        if (uri != "/" && uri[0] == '/') {
            uri = uri.substr(1, std::string::npos);
        }

        // todo check if origUri == uri and id is NOT empty
        // that would mean that trying to add route for uri that already exists
        // in which case must throw exception.



        RouterNode *newNode;
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
                        i->setController(pVoid);
                        //i->controller = &id;
                        // cout << "addRoute-CP5" << endl;
                        return i;
                    }
                } else {
                    // cout << "addRoute-CP6" << endl;
                    // First section of uri matched this child node
                    // but we have "restUri" of the uri
                    // in this case child node is not going to be used...
                    return i->addRoute(restUri, pVoid, name);
                }
            }

        }

        // cout << "addRoute-CP7" << endl;
        // newNode uri did not match any of children origUriPattern
        // in this case add new Node to childred
        // cout << "Not matched in children of " << origUriPattern << " For uri: " << uri << endl;

        if (restUri.empty()) {
            newNode = new RouterNode(nodeUri, pVoid, name); //new RouterNode<T>(nodeUri, id, name);
            // cout << "       Created new NODE with EMPTY=" << newNode->empty() << " for id: " << id << " URI=" << nodeUri << " PN: " << newNode->getParamName() << endl;
        } else {
            newNode = new RouterNode(nodeUri); //new RouterNode<T>(nodeUri);
            // cout << "       Created new NODE_NC for URI=" << nodeUri << endl;
            newNode->addRoute(restUri, pVoid, name);
        }


        // cout << "Added new child to " << origUriPattern << ":" << controller << " with uri: " << nodeUri << endl;
        children.push_back(newNode);

        return newNode;

    }


    std::string RouterNode::tail_(const std::string s) {

        // todo check that len of s must be > len of origUriPattern? Do we need this check?
        // is it possible to pass shorter string here?

        // cout << "ENTERED RouterNode::rest with s=[" << s << "] origUriPattern=" << origUriPattern << endl;


        std::string ret = s.substr(s.find(PATH_SEPARATOR) + 1, std::string::npos);

        // cout << "RouterNode::rest ret[" << ret << "] result for [" << s << "] in NODE  " << controller_name << endl;

        return ret;
    }


}