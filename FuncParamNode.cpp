//
// Created by Snytkine, Dmitri (CORP) on 3/22/17.
//

#include "node_result.h"
#include "RouterNode.h"
#include "constants.h"
#include "FuncParamNode.h"
#include "strlib.h"


namespace router_lib {

    using namespace std;

    template<class T>
    void FuncParamNode<T>::setParamName(string pn) {
        paramName_ = pn;
    }

    template<class T>
    string FuncParamNode<T>::getParamName() const {
        return paramName_;
    }


    template<class T>
    RouteResult<T> *FuncParamNode<T>::getNodeResult(const string uri, paramsList *params) const {

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
        RouteResult<T> *res = new RouteResult<T>(params);
        size_t sepPos = uri.find(PATH_SEPARATOR);
        if (END_WITH_SLASH) {
            // cout << "END_WITH_SLASH" << endl;
            if (sepPos == string::npos) {
                // cout << "URI DOES NOT END WITH SLASH" << endl;

                return new EmptyResult<T>();
            } else {

                // LOGIC
                // uri must end with ")/"
                // uri must start with prefix
                // extract everything from prefix to ")"

                if(!::startsWith(uri, prefix)){
                    //cout << "FuncParamNode uri=[" << uri << "] does not start with prefix=[" << prefix << "]" << endl;

                    return new EmptyResult<T>();
                }

                if(!::endsWith(uri, P_END + PATH_SEPARATOR)){
                    //cout << "FuncParamNode uri=[" << uri << "] does not start end with=[" << (P_END + PATH_SEPARATOR) << "]" << endl;

                    return new EmptyResult<T>();
                }

                // cout << "URI HAS SLASH" << endl;
                // extract param manually
                RouteParam *rp = new RouteParam(paramName_, uri.substr(startPos, uri.find(P_END) - startPos));
                // cout << "CP-1" << endl;
                params->push_back(rp);
                // cout << "CP-2" << endl;
                res->params = params;
                // cout << "CP-3" << endl;
                res->restString = tail_(uri);
                // cout << "CP-4" << endl;
                if (res->restString.empty()) {
                    // cout << "CP-5" << endl;
                    res->controller = RouterNode<T>::getController();
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

                return new EmptyResult<T>();
            } else {
                // LOGIC:
                // uri must end with ")"
                // uri must start with prefix
                // extract everything from prefix to ")"

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
