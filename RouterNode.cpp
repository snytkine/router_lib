//
// Created by Snytkine, Dmitri (CORP) on 3/14/17.
//

#include "RouterNode.h"
#include "strlib.h"


namespace router_lib {

    std::string tail_(const std::string s) {

        // todo check that len of s must be > len of origUriPattern? Do we need this check?
        // is it possible to pass shorter string here?

        // std::cout << "ENTERED RouterNode::rest with s=[" << s << "]" << std::endl;


        std::string ret = s.substr(s.find(PATH_SEPARATOR) + 1, std::string::npos);

        // std::cout << "RouterNode::rest ret[" << ret << "] result for [" << s << "] " << std::endl;

        return ret;
    }


/*    template<class T>
    void RouterNode<T>::init(std::string uri, T ctrl) {
        init(uri);
        controllers.push_back(ctrl);
    }*/

    template<class T>
    void RouterNode<T>::init(std::string uri) {

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
                // // std::cout << "~~~~~~~~~~ MADE FuncNode ~~~~~~~~~ for uri[" << uri << "]" << std::endl;
            }


            std::string pn = uri.substr(placeholderStartPos + 1, placeholderEndPos - placeholderStartPos - 1);

            if (pn.empty()) {
                throw std::invalid_argument("EMPTY PARAM NAME for uri: " + uri);
            }

            paramName_ = pn;


        } // no valid placeholders

    }

    template<class T>
    bool RouterNode<T>::empty() const {
        return controllers.empty();
    }

    template<class T>
    std::vector<TController<T>> *RouterNode<T>::getControllers() {
        return &controllers;
    }


    template<class T>
    void RouterNode<T>::totalNodes(int &counter) {

        int ts = children.size();

        if (ts > 0) {
            counter += ts;
            for (auto &&i: children) {
                i->totalNodes(counter);
            }
        }

    }

    //void totalControllers(int &counter)
    template<class T>
    void RouterNode<T>::totalControllers(int &counter) {

        counter+= controllers.size();
        int ts = children.size();

        if (ts > 0) {
            for (auto &&i: children) {
                i->totalControllers(counter);
            }
        }

    }

    template<class T>
    RouteResult<T> *RouterNode<T>::getFuncNodeResult(const std::string uri, paramsList *params) {

        // std::cout << "Entered getFuncNodeResult with URI=" << uri << std::endl;
        RouteResult<T> *res = new RouteResult<T>(params);
        size_t sepPos = uri.find(PATH_SEPARATOR);
        if (END_WITH_SLASH) {
            // std::cout << "FuncNode END_WITH_SLASH originalUriPatterh=" << origUriPattern << std::endl;
            if (sepPos == std::string::npos) {
                // std::cout << "URI DOES NOT END WITH SLASH" << std::endl;

                return new EmptyResult<T>();
            } else {

                // HERE Our node ends with slash, the uri has slash but may not end with slash

                // LOGIC
                // uri must end with ")/"
                // uri must start with prefix
                // extract everything from prefix to ")"

                if (!::startsWith(uri, prefix)) {
                    // std::cout << "FuncParamNode uri=[" << uri << "] does not start with prefix=[" << prefix << "]"
                    //          << std::endl;

                    return new EmptyResult<T>();
                }

                size_t myEndPos = uri.find(P_END + PATH_SEPARATOR);
                if (myEndPos == std::string::npos) {
                    // std::cout << " funcNode CP:231 uri=" << uri << " Does not have " << (P_END + PATH_SEPARATOR)
                    //         << " in node originalUriPattern=" << origUriPattern << std::endl;
                }

                if (myEndPos <= startPos + 1) {
                    // std::cout << "funcNode CP::232 myEndPos=" << myEndPos << " startPos=" << startPos << " in originalUriPattern="
                    //        << origUriPattern << " uri=" << uri << std::endl;
                }

                // std::cout << " funcNode CP:777 URI HAS SLASH" << std::endl;
                // extract param manually
                RouteParam *rp = new RouteParam(paramName_, uri.substr(startPos, myEndPos - startPos));
                // std::cout << "funcNode CP-1" << std::endl;
                params->push_back(rp);
                // std::cout << "funcNode CP-2" << std::endl;
                res->params = params;
                // std::cout << "funcNode CP-3" << std::endl;
                res->restString = tail_(uri);
                // std::cout << "funcNode CP-4" << std::endl;
                if (res->restString.empty()) {
                    // std::cout << "funcNode CP-5" << std::endl;
                    res->controllers = getControllers();
                } else {
                    // std::cout << "funcNode CP-6" << " rest was: " << res->restString << std::endl;
                }
                // std::cout << "funcNode CP-7" << std::endl;

                return res;
            }
        } else {
            // std::cout << "FuncNode DOES NOT END_WITH_SLASH=" << origUriPattern << std::endl;
            // cout << "NOT END_WITH_SLASH" << endl;
            if (sepPos != std::string::npos) {
                // std::cout << "URI HAS SLASH=" << uri << std::endl;

                return new EmptyResult<T>();
            } else {
                // std::cout << "URI DOES NOT HAVE SLASH=" << uri << std::endl;
                // LOGIC:
                // uri must end with ")"
                // uri must start with prefix
                // extract everything from prefix to ")"

                // cout << "URI ALSO DOES NOT HAVE SLASH" << endl;

                size_t myEndPos = uri.find(P_END);
                if (myEndPos == std::string::npos) {
                    // std::cout << " uri=" << uri << " Does not have " << (P_END) << " in node originalUriPattern="
                    //          << origUriPattern << std::endl;

                    return new EmptyResult<T>();
                }

                if (myEndPos <= startPos + 1) {
                    // std::cout << "FuncNode myEndPos=" << myEndPos << " startPos=" << startPos
                    //         << " in originalUriPattern=" << origUriPattern << " uri=" << uri << std::endl;

                    return new EmptyResult<T>();
                }

                RouteParam *rp = new RouteParam(paramName_, uri.substr(startPos, myEndPos - startPos));
                params->push_back(rp);
                res->params = params;
                res->controllers = getControllers();
                //res->restString = tail_(uri);
                // in case like this there is no need to extract rest because since uri does not have slash the entire uri is a val.


                return res;
            }
        }

    }

    template<class T>
    RouteResult<T> *RouterNode<T>::getParamNodeResult(const std::string uri, paramsList *params) {

        // std::cout << "Entered getParamNodeResult in Node with origUrlPatterh=[" << origUriPattern << "]" << std::endl;

        RouteResult<T> *res = new RouteResult<T>(params);
        size_t sepPos = uri.find(PATH_SEPARATOR);
        if (END_WITH_SLASH) {
            // std::cout << "getParamNodeResult CP:5932 END_WITH_SLASH" << std::endl;
            if (sepPos == std::string::npos) {
                // cout << "URI DOES NOT END WITH SLASH" << endl;

                return new EmptyResult<T>();
            } else {
                // // std::cout << "URI HAS SLASH " << uri << std::endl;
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
                    // // std::cout << "CP-5" << std::endl;
                    res->controllers = getControllers();
                } else {
                    // cout << "CP-6" << " rest was: " << res->restString << endl;
                }
                // cout << "CP-7" << endl;
                return res;
            }
        } else {
            // std::cout << "getParamNodeResult CP:4399 NOT END_WITH_SLASH" << std::endl;
            if (sepPos != std::string::npos) {
                // std::cout << "getParamNodeResult CP:4342  URI HAS SLASH" << std::endl;

                return new EmptyResult<T>();
            } else {
                // std::cout << "getParamNodeResult CP:54534 URI ALSO DOES NOT HAVE SLASH" << std::endl;
                RouteParam *rp = new RouteParam(paramName_, uri);
                // std::cout << "getParamNodeResult CP:54535 URI ALSO DOES NOT HAVE SLASH" << std::endl;
                params->push_back(rp);
                // std::cout << "getParamNodeResult CP:54536 URI ALSO DOES NOT HAVE SLASH" << std::endl;
                res->params = params;
                res->controllers = getControllers();
                // in case like this there is no need to extract rest because since uri does not have slash the entire uri is a val.
                // std::cout << "getParamNodeResult CP:54537 URI ALSO DOES NOT HAVE SLASH" << std::endl;

                return res;

            }
        }

    }

    template<class T>
    RouteResult<T> *RouterNode<T>::getNodeResult(const std::string s, paramsList *params) {

        // std::cout << "~~~~~~~~Entered getNodeResult NodeType=[" << (int) nodeType_ << "] looking for " << s << std::endl;
        // cout << "Entered getNodeResult in node [" << origUriPattern << "] looking for " << s << endl;

        RouteResult<T> *res = new RouteResult<T>(params);

        if (s == origUriPattern) {
            // std::cout << "           getNodeResult MATCH [" << origUriPattern << "] matched " << s << std::endl;
            res->controllers = &controllers;
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

}