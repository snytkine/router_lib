//
// Created by Snytkine, Dmitri (CORP) on 3/18/17.
//

#include "RouterNode.h"
#include "PathParamNode.h"
#include "constants.h"

namespace router_lib {


    void PathParamNode::setParamName(string pn) {
        paramName_ = pn;
    }


    string PathParamNode::getParamName() const {
        return paramName_;
    }

    //template<class T>
    //string PathParamNode<T>::rest(const string s) const {
        // cout << "Entered PathParamNode::rest() with s=" << s << " IS_SLASH_PATH: " << END_WITH_SLASH << endl;

        // If this node is for NON_SLASH uri (as in /usr/{id} ) then this function will not be called because
        // the logic will return NULL
        // If this NODE is SLASH path but looking for non-slash url this function will also NOT be called
        // this is a case when this node is for {id}/ but looking for something like /usr/55
        // This means that this function will be called ONLY if this node END_WITH_SLASH and s has slash
        // need to get everything after the slash!
        //
        //string ret= s.substr(s.find(PATH_SEPARATOR) + 1, string::npos );
        // cout << "PathParamNode::rest ret[" << ret << "] result for [" << s << "]" << endl;

        //return ret;
    //}


    RouteResult *PathParamNode::getNodeResult(const string uri, paramsList *params) const {

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
            if (sepPos == string::npos) {
                // cout << "URI DOES NOT END WITH SLASH" << endl;

                return new EmptyResult();
            } else {
                // cout << "URI HAS SLASH" << endl;
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
                    // cout << "CP-5" << endl;
                    res->controller = RouterNode::getController();
                } else {
                    // cout << "CP-6" << " rest was: " << res->restString << endl;
                }
                // cout << "CP-7" << endl;
                return res;
            }
        } else {
            // cout << "NOT END_WITH_SLASH" << endl;
            if (sepPos != string::npos) {
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

}
